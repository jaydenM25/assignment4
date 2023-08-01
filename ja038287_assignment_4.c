#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int extraMemoryAllocated;

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int min(int x, int y) {
    if (x > y)
        return x;
    else
        return y;
}

void merge(int pData[], int l, int mid, int r) {
    int q1 = mid - l + 1;
    int q2 = r - mid;

    int* Left = (int*) malloc(sizeof(int)*q1);
    int* Right = (int*) malloc(sizeof(int)*q2);
    extraMemoryAllocated = (sizeof(int)*q1) + (sizeof(int)*q2);

    for(int i = 0; i < q1; i++)
        Left[i] = pData[l + i];

    for(int i = 0; i < q2; i++) 
        Right[i] = pData[mid + 1 + i];

    int Lpoint = 0;
    int Rpoint = 0;
    int k = l;

    while(Lpoint < q1 && Rpoint < q2) {
        if(Left[Lpoint] <= Right[Rpoint]) {
            pData[k] = Left[Lpoint];
            Lpoint++;
        }
        else {
            pData[k] = Right[Rpoint];
            Rpoint++;
        }
        k++;
    }

    while(Lpoint < q1) {
        pData[k] = Left[Lpoint];
        Lpoint++;
        k++;
    }

    while(Rpoint < q2) {
        pData[k] = Right[Rpoint];
        Rpoint++;
        k++;
    }

    free(Left);
    free(Right);
}

// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated
void mergeSort(int pData[], int l, int r) {
    if (l < r) {
    int mid = (l+r)/2;
    mergeSort(pData, l, mid);
    mergeSort(pData, mid+1, r);

    merge(pData, l, mid, r);
    }
}

// implement insertion sort
// extraMemoryAllocated counts bytes of memory allocated
void insertionSort(int* pData, int n)
{
	int item, j; 

    for(int i = 1; i < n; i++) {
        item = pData[i];
        for(j = i-1; j >= 0; j--) {
            if(pData[j] > item)
                pData[j+1] = pData[j];
            else
                break;
        }
        pData[j+1] = item;
    }
}

// implement bubble sort
// extraMemoryAllocated counts bytes of extra memory allocated
void bubbleSort(int* pData, int n) {
    int temp;
	for (int i = 0; i < n-1; i++) {
	    for(int j = 0; j < n-i-1; j++) {
	        if (pData[j] > pData[j+1]) {
	            temp = pData[j];
	            pData[j] = pData[j+1];
	            pData[j+1] = temp;
	        }
	    }
	}
}

// implement selection sort
// extraMemoryAllocated counts bytes of extra memory allocated
void selectionSort(int* pData, int n) {
    int min, temp;
	for(int i = 0; i < n-1; i++) {
	    min = i;
	    for(int j = i+1; j < n; j++) {
	        if (pData[j] < pData[min])
	            min = j;
	        temp = pData[i];
	        pData[i] = pData[min];
	        pData[min] = temp;
	    }
	}
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{
	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");
	
	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

int main(void)
{
	clock_t start, end;
	int i;
    double cpu_time_used;
	char* fileNames[] = {"input1.txt", "input2.txt", "input3.txt"};
	
	for (i=0;i<3;++i)
	{
		int *pDataSrc, *pDataCopy;
		int dataSz = parseData(fileNames[i], &pDataSrc);
		
		if (dataSz <= 0)
			continue;
		
		pDataCopy = (int *)malloc(sizeof(int)*dataSz);
	
		printf("---------------------------\n");
		printf("Dataset Size : %d\n",dataSz);
		printf("---------------------------\n");
		
		printf("Selection Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		selectionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Insertion Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		insertionSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);

		printf("Bubble Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		bubbleSort(pDataCopy, dataSz);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		printf("Merge Sort:\n");
		memcpy(pDataCopy, pDataSrc, dataSz*sizeof(int));
		extraMemoryAllocated = 0;
		start = clock();
		mergeSort(pDataCopy, 0, dataSz - 1);
		end = clock();
		cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
		printf("\truntime\t\t\t: %.1lf\n",cpu_time_used);
		printf("\textra memory allocated\t: %d\n",extraMemoryAllocated);
		printArray(pDataCopy, dataSz);
		
		free(pDataCopy);
		free(pDataSrc);
	}
	
}