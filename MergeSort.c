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

//dividing the array into smaller, sorted ones 
void merge(int array[], int first, int middle, int last){

    int f;
    int s;
    int m;

    //stands for the last index of the number in the left part of the array 
    int number1 = middle - first + 1;

    //stands for the last index of the number in the right part of the array 
    int number2 = last - middle; 

    //we need temporary array to store the values 
    int leftPart[number1];
    int rightPart[number2];

    //copying left array values to the temporary array
    for (f = 0; f < number1; f++)
        leftPart[f] = array[first + f];

    //copying right array values to the temporary array     
    for (s = 0; s < number2; s++)
        rightPart[s] = array[middle + 1 + s];

    // starting index of the first array 
    int fa = 0;
    //starting index of the second array 
    int sa = 0;
    //starting index of the merged array 
    int ma = first;

    /*  while loop: merging the temporary arrays into one
        while current index of the first array is smaller than the last number of the left part and 
        while current index of the second array is smaller than the number 2

        if current index of the left part is smaller than the current index of the right part, then 
        next number in the merged array is current number in the left part 
        increase the current index of the left part 

        else if not, next number of the merged array is the current number from the right part array
        after every while loop iteration, increase the current index of the merged array 
    */ 
    while (fa < number1 && sa < number2){
        if(leftPart[fa] <= rightPart[sa]){
            array[ma] = leftPart[fa];
            fa++;
        } else {
            array[ma] = rightPart[sa];
            sa++;
        }
        ma++;
    }

    // if any element in either left or right array left, copy them to the merged array
    //left part 
    while (fa < number1){
        array[ma] = leftPart[fa];
        fa++;
        ma++;
    }

    //right part 
    while (sa < number2){
        array[ma] = rightPart[sa];
        sa++;
        ma++;
    }
}

/*"array" stands for the array we are working with 
    "first" stands for the first element of the array 
    "last" stands for the last element of the array 
*/
void MergeSort(int array[], int first, int last){
    if (first < last){
        int middle = first + (last-first) /2;

        MergeSort(values, first, middle);
        MergeSort(values, middle + 1, last);

        merge(values, first, middle, last);
    }
}

//printing the provided array 
void printing(int array[]){
    int counter = 1;
    for ( int i = 0; i < length; i++){
        printf("Element %d: %d\n", counter, values[i]);
        counter++;
    }
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
        MergeSort(values, 0, length -1);
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    
    printf("Spent: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
    
    
}