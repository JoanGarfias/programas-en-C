#include <stdio.h>

int main() {
    char buffer[128];
    FILE *fp = fopen("SETBUF.txt", "w");
    setbuf(fp, buffer);
    fprintf(fp, "Hola mundo");
    fclose(fp);

    return 0;
}