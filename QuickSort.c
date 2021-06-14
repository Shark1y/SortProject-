#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

int partition(int array[], int first, int last);


/*
compare function, to compare the integers 
if the numbers are equal, function returns 0
if the number a is larger than number b, function returns 1 
if the number a is smaller than number b, function returns -1
*/
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

/*
"array" stands for the array we are working with 
"first" stands for the first element of the array 
"last" stands for the last element of the array 
pivotIndex stands for the array element, that stands in a correct position even before sorting 
*/
void quickSort(int array[], int first, int last) {

	//
	if (last > first) {
		int pivotIndex = partition(array, first, last);

		quickSort(array, first, pivotIndex - 1);

		quickSort(array, pivotIndex + 1, last);
	}
}

/* 
The function takes first element as pivot, change the pivot position to its correct position in sorted array, 
and places all smaller elements to left of pivot, and all greater elements to right of the pivot 
*/
int partition(int array[], int first, int last) {

	//start off with the pivot at the first element 
	int pivot = array[first];

	//variable for the forward search 
	int low = first + 1;

	//variable for the backward search 
	int high = last;

	while (high > low) {

		//search forward 
		while (low <= high && compare(array[low],pivot) <= 0){
			low++;
		}
		//search backward 
		while (low <= high && compare(array[high],pivot) > 0){
			high--;
		}

		//swap elements in the array 
		if (high > low) {

			int temp = array[high];

			array[high] = array[low];

			array[low] = temp;
		}
	}

	while (high > first && compare(array[high],pivot) >= 0){
		high--;
	}

	//swap pivot with the highest element 
	if (compare(pivot,array[high]) > 0) {

		array[first] = array[high];

		array[high] = pivot;

		return high;
	} else {

	return first;

	}
}

//function to initialize sorting 
void sort(int array[],int length) {

	quickSort(array, 0, length-1);
	
}

int main(int argc, char *argv[]){

	if (argc < 2)
    printf("You are supposed to input the file you are working with!\n");

     //starting the timer for the time consuming 
    clock_t begin = clock();

    for (int i =0; i <1000; i++){

        //reading from a file
        FILE* f = fopen (argv[1], "r");

        //where to store the length of the array 
        int length = 0;
        //reading the length of the array 
        fscanf (f, "%d", &length); 

        //inputing values inside the array 
        int temp;

        //counter is used to store the values one by one 
        int counter = 0;

        //initializing array for the values 
        int values[length];

        //input values untill we reach end of the file 
        while (!feof (f))
        {  
            fscanf (f, "%d", &temp);  
            values[counter] = temp;   
            counter++; 
        }

        //closing the file we are working with 
        fclose (f);

        //call for sort function 
        sort(values, length);
    }
    
    //closing the timer for the time consuming 
    clock_t end = clock();

	FILE* final = fopen ("final.txt", "a+");
    fprintf(final, "\nSpent: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
    fprintf(final, "Quick Sort _____ values.\n");
    fclose(final);

    printf("Spent: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
}