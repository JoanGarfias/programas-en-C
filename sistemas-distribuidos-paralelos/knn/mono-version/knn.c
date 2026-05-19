/*
    * KNN Algorithm - MNIST (CSV) streaming, sequential
    * Compile: gcc -O2 -lm knn.c -o knn
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <omp.h>

#define PIXELS 783
#define DEFAULT_K 7
#define LINE_BUFFER_SIZE 8192
#define MAX_LABEL 10

typedef struct {
    int label;
    int pixels[PIXELS];
} Sample;

typedef struct {
    int label;
    double distance;
} Neighbor;

static int parse_next_int(const char **cursor, int *outValue) {
    char *end = NULL;
    long value;

    while (**cursor == ' ' || **cursor == '\t' || **cursor == ',') {
        (*cursor)++;
    }

    value = strtol(*cursor, &end, 10);
    if (end == *cursor) {
        return 0;
    }

    *outValue = (int)value;
    *cursor = end;
    return 1;
}

static int parse_csv_line(char *line, int *outLabel, int *outPixels) {
    const char *cursor = line;
    int i;

    if (!parse_next_int(&cursor, outLabel)) {
        return 0;
    }

    for (i = 0; i < PIXELS; i++) {
        if (!parse_next_int(&cursor, &outPixels[i])) {
            return 0;
        }
    }

    return 1;
}

static double squared_distance(const int *a, const int *b) {
    double sum = 0.0;
    int i;

    for (i = 0; i < PIXELS; i++) {
        double diff = (double)(a[i] - b[i]);
        sum += diff * diff;
    }

    return sum;
}

static void update_neighbors(Neighbor *neighbors, size_t *count, size_t k, double distance, int label) {
    size_t i;
    size_t maxIndex = 0;
    double maxDistance = -1.0;

    if (*count < k) {
        neighbors[*count].label = label;
        neighbors[*count].distance = distance;
        (*count)++;
        return;
    }

    for (i = 0; i < k; i++) {
        if (neighbors[i].distance > maxDistance) {
            maxDistance = neighbors[i].distance;
            maxIndex = i;
        }
    }

    if (distance < maxDistance) {
        neighbors[maxIndex].label = label;
        neighbors[maxIndex].distance = distance;
    }
}

static int predict_label(const Neighbor *neighbors, size_t count) {
    int counts[MAX_LABEL] = {0};
    double distSums[MAX_LABEL] = {0.0};
    int bestLabel = 0;
    int bestCount = -1;
    double bestDistSum = 0.0;
    size_t i;

    for (i = 0; i < count; i++) {
        int label = neighbors[i].label;
        if (label < 0 || label >= MAX_LABEL) {
            continue;
        }
        counts[label]++;
        distSums[label] += neighbors[i].distance;
    }

    for (i = 0; i < MAX_LABEL; i++) {
        if (counts[i] > bestCount) {
            bestCount = counts[i];
            bestLabel = (int)i;
            bestDistSum = distSums[i];
        } else if (counts[i] == bestCount && counts[i] > 0) {
            if (distSums[i] < bestDistSum) {
                bestLabel = (int)i;
                bestDistSum = distSums[i];
            }
        }
    }

    return bestLabel;
}

static void render_ascii_image(const int *pixels) {
    const char *levels = " .:-=+*#%@";
    const int levelCount = 10;
    int width = 28;
    int height = PIXELS / width;
    int remainder = PIXELS % width;
    int r;
    int c;
    int idx = 0;

    if (height == 0) {
        width = PIXELS;
        height = 1;
        remainder = 0;
    }

    for (r = 0; r < height; r++) {
        for (c = 0; c < width; c++) {
            int value = pixels[idx++];
            int level = (value * (levelCount - 1)) / 255;
            char ch = levels[level];
            putchar(ch);
            putchar(ch);
        }
        putchar('\n');
    }

    if (remainder > 0) {
        for (c = 0; c < remainder; c++) {
            int value = pixels[idx++];
            int level = (value * (levelCount - 1)) / 255;
            char ch = levels[level];
            putchar(ch);
            putchar(ch);
        }
        putchar('\n');
    }
}

int main(int argc, char *argv[]) {
    const char *datasetPath = "train.csv";
    size_t k = DEFAULT_K;
    FILE *file = NULL;
    char line[LINE_BUFFER_SIZE];
    size_t sampleIndex = 0;
    size_t referenceIndex = 0;
    Sample referenceSample;
    clock_t startTime;
    double elapsedSeconds;
    Neighbor *neighbors = NULL;
    size_t neighborCount = 0;
    int predictedLabel;

    if (argc >= 2) {
        datasetPath = argv[1];
    }
    if (argc >= 3) {
        int parsedK = atoi(argv[2]);
        if (parsedK > 0) {
            k = (size_t)parsedK;
        }
    }

    printf("KNN Algorithm - MNIST streaming (CSV)\n");
    printf("Dataset: %s\n", datasetPath);
    printf("K: %zu\n", k);

    srand((unsigned int)time(NULL));

    file = fopen(datasetPath, "r");
    if (!file) {
        perror("Unable to open dataset");
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), file)) {
        int label;
        int pixels[PIXELS];

        if (!parse_csv_line(line, &label, pixels)) {
            continue;
        }

        sampleIndex++;
        if ((size_t)(rand() % sampleIndex) == 0) {
            referenceSample.label = label;
            memcpy(referenceSample.pixels, pixels, sizeof(pixels));
            referenceIndex = sampleIndex;
        }
    }

    fclose(file);

    if (sampleIndex == 0) {
        fprintf(stderr, "No valid samples found in dataset.\n");
        return EXIT_FAILURE;
    }

    neighbors = (Neighbor *)calloc(k, sizeof(Neighbor));
    if (!neighbors) {
        fprintf(stderr, "Unable to allocate memory for neighbors.\n");
        return EXIT_FAILURE;
    }

    file = fopen(datasetPath, "r");
    if (!file) {
        perror("Unable to reopen dataset");
        free(neighbors);
        return EXIT_FAILURE;
    }

    sampleIndex = 0;
    startTime = omp_get_wtime();

    while (fgets(line, sizeof(line), file)) {
        int label;
        int pixels[PIXELS];
        double distance;

        if (!parse_csv_line(line, &label, pixels)) {
            continue;
        }

        sampleIndex++;
        if (sampleIndex == referenceIndex) {
            continue;
        }

        distance = squared_distance(referenceSample.pixels, pixels);
        update_neighbors(neighbors, &neighborCount, k, distance, label);
    }

    fclose(file);

    predictedLabel = predict_label(neighbors, neighborCount);
    elapsedSeconds = omp_get_wtime() - startTime;

    printf("Selected sample label: %d\n", referenceSample.label);
    printf("Predicted label: %d\n", predictedLabel);
    printf("Execution time: %.6f seconds\n", elapsedSeconds);
    printf("\nSelected image (ASCII):\n");
    render_ascii_image(referenceSample.pixels);

    free(neighbors);
    return 0;
}