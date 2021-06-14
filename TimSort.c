#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>

//RUN is max length of the blocks, which we are diving the array into 
const int RUN = 32;

int min(int a, int b)  
{  
    if(a < b)  
    return a;   
    else   
    return b;   
}  

/*
This function is sorting the array from the left until the index of the RUN 
*/
void insertionSort(int array[], int length){
    for (int i = 1; i < length; i++){
        int temp = array[i];
        int j = i - 1;
 
        //Compare key with each element on the left of it until an element smaller than it is found.
        while (temp < array[j] && j >= 0){
            array[j + 1]= array[j];
            --j;
        }
        //next element in the array is now same as the previous one 
        array[j + 1] = temp; 
    }
}

//dividing the array into smaller, sorted ones 
void merge(int array[], int first, int middle, int last){

    //stands for the last index of the number in the left part of the array 
    int number1 = middle - first + 1;

    //stands for the last index of the number in the right part of the array 
    int number2 = last - middle; 

    //we need temporary array to store the values 
    int leftPart[number1];
    int rightPart[number2];

    //copying left array values to the temporary array
    for (int f = 0; f < number1; f++)
        leftPart[f] = array[first + f];

    //copying right array values to the temporary array     
    for (int s = 0; s < number2; s++)
        rightPart[s] = array[middle + 1 + s];

    // starting index of the first array 
    int firstArray = 0;
    //starting index of the second array 
    int secondArray = 0;
    //starting index of the merged array 
    int mergedArray = first;

    /*  while loop: merging the temporary arrays into one
        while current index of the first array is smaller than the last number of the left part and 
        while current index of the second array is smaller than the number 2
        if current index of the left part is smaller than the current index of the right part, then 
        next number in the merged array is current number in the left part 
        increase the current index of the left part 
        else if not, next number of the merged array is the current number from the right part array
        after every while loop iteration, increase the current index of the merged array 
    */ 
    while (firstArray < number1 && secondArray < number2){
        if(leftPart[firstArray] <= rightPart[secondArray]){
            array[mergedArray] = leftPart[firstArray];
            firstArray++;
        } else {
            array[mergedArray] = rightPart[secondArray];
            secondArray++;
        }
        mergedArray++;
    }

    // if any element in either left or right array left, copy them to the merged array
    //left part 
    while (firstArray < number1){
        array[mergedArray] = leftPart[firstArray];
        firstArray++;
        mergedArray++;
    }

    //right part 
    while (secondArray < number2){
        array[mergedArray] = rightPart[secondArray];
        secondArray++;
        mergedArray++;
    }
}

void timSort(int array[], int length)
{
    // Sort arrays one by one
    for (int i = 0; i < length; i+=RUN)
        insertionSort(array, length);
 
    // start merging from size RUN (or 32). It will merge to form size 64, then 128, 256 and so on ....
    for (int size = RUN; size < length; size = 2*size)
    {
        // pick starting point of left sub array. We are going to merge arr[left..left+size-1] and arr[left+size, left+2*size-1]
        // After every merge, we increase left by 2*size
        for (int left = 0; left < length; left += 2*size)
        {
            // find ending point of left sub array
            // mid+1 is starting point of right sub array
            int mid = left + size - 1;
            int right = min((left + 2*size - 1), (length-1));
 
            // merge sub array arr[left.....mid] & arr[mid+1....right]
            merge(array, left, mid, right);
        }
    }
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
        timSort(values, length);

    }
    
    //closing the timer for the time consuming 
    clock_t end = clock();

    FILE* final = fopen ("final.txt", "a+");
    fprintf(final, "\nSpent: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
    fprintf(final, "Tim Sort ______ values.\n");
    fclose(final);

    printf("Spent: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
}