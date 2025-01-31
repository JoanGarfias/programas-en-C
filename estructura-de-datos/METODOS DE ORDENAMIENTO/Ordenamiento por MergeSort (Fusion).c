#include <stdio.h>

#define TAM 6

void MergeSort(int ini, int fin, int [] );
void fusion(int ini, int mid,int fin, int []);

int main(){
	
	int arr[TAM] = {9,2,4,2,8,6};
	int i;
	for(i=0; i<TAM; i++){
		printf("%d ",arr[i]);
	}
	printf("\n\n\n");
	MergeSort(0, TAM, arr);
	for(i=0; i<TAM; i++){
		printf("%d ",arr[i]);
	}
}

void MergeSort(int ini, int fin, int arr[] ){
	int mid;
	if(ini < fin){
		mid = (ini+fin) / 2;
		MergeSort(ini,mid, arr);
		MergeSort(mid+1, fin, arr);
		fusion(ini, mid, fin, arr);
	}
}

void fusion(int ini, int mid, int fin, int arr[]) {
    int n1 = mid - ini + 1;
    int n2 = fin - mid;

    int L[n1], R[n2];

    for (int i = 0; i < n1; i++) {
        L[i] = arr[ini + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }

    int i = 0, j = 0, k = ini;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}