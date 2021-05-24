#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

int partition(int array[], int first, int last);


int compare(int a, int b){
    if (a == b){
        return 0;
    } 
    if (a > b){
        return 1;
    }
	if (a < b){
		return -1;
	}
}

void quickSort(int array[], int first, int last) {

	if (last > first) {
		int pivotIndex = partition(array, first, last);

		quickSort(array, first, pivotIndex - 1);

		quickSort(array, pivotIndex + 1, last);
	}
}


int partition(int array[], int first, int last) {

	int pivot = array[first];

	int low = first + 1;

	int high = last;

	while (high > low) {

		while (low <= high && compare(array[low],pivot) <= 0){
			low++;
		}

		while (low <= high && compare(array[high],pivot) > 0){
			high--;
		}

		if (high > low) {

			int temp = array[high];

			array[high] = array[low];

			array[low] = temp;
		}
	}

	while (high > first && compare(array[high],pivot) >= 0){
		high--;
	}

	if (compare(pivot,array[high]) > 0) {

		array[first] = array[high];

		array[high] = pivot;

		return high;
	} else {

	return first;

	}
}

void sort(int array[],int length) {

	quickSort(array, 0, length-1);
	
}

int main(int argc, char *argv[]){

    //reading from a file
    FILE* f = fopen (argv[1], "r");

    //where to store the length of the array 
    int length = 0;
    //reading the length of the array 
    fscanf (f, "%d", &length); 

    //inputing values inside the array 
    int temp;
    int counter = 0;

    int values[length];

    while (!feof (f))
    {  
        fscanf (f, "%d", &temp);  
        values[counter] = temp;   
        counter++; 
    }

    fclose (f);

    clock_t begin = clock();

	for (int i = 0; i < 1000; i++){
	sort(values, length);
	}

    clock_t end = clock();

    printf("Spent: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
}