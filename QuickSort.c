#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

int values[];
int length;

int compare(int a, int b){
    if (a = b){
        return 1;
    } 
    if (a != b){
        return 0;
    }
}

int partition(int array[], int first, int last){
    
	int pivot = array[first];

	int low = first + 1;

	int high = last;

	while (high > low) {

        while (low <= high && compare(array[low], pivot) <= 0)
			low++;

		while (low <= high && compare(array[high], pivot) > 0)
			high--;

		if (high > low) {

			int temp = array[high];

			array[high] = array[low];

			array[low] = temp;
		}
	}

	while (high > first && compare(array[high], pivot) >= 0)
		high--;

	if (compare(pivot,array[high]) > 0) {

		array[first] = array[high];

		array[high] = pivot;

		return high;
    
    } else {
		return first;
    }
}

void quickSort(int array[], int first, int last) {

	if (last > first) {
            
		int pivotIndex = partition(array,first,last);

		quickSort(array, first, pivotIndex - 1);

		quickSort(array, pivotIndex + 1, last);
	}
}



void sort(int array[]) {
		quickSort(array, 0, length - 1);
}

int main(){
// //filling the array with the values from 1 to 1024 
// for (int i = 0; i < 1024; i++){
// values[i] = i+1;
// length++;
// }

//filling the array with the random values from 1 to 1024 
for (int i = 0; i < 1024; i++){
    values[i] = rand() % 1024-1;
    length++;
}

// //filling the array with the values from 1024 to 1 
// int filling1024 = 1024;
// for (int i = 0; i < 1024; i++){
//     values[i] = filling1024;
//     filling1024--;
//     length++;
// }

clock_t begin = clock();
for(int r=0; r < 1000; r++){ 
    quickSort(values, 0, length-1);
}
clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    
printf("Spent: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
}