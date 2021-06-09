
#include<stdlib.h>
#include<stdio.h>
#include <time.h>

/*
	array param is the array we are going to sort
	length is length of the array we are going to sort  
*/
int* patienceSort(int* array,int length){


	int decks[length][length];


	int *count = (int*)calloc(sizeof(int),length);

	/*
	this is array we are going to return,
	and giving it exact amount of memory it needs  
	*/
	int *sortedArr = (int*)malloc(length*sizeof(int));


	for(int i = 0; i < length; i++){

		for(int j = 0; j < length; j++){
			
			if(count[j] == 0 || ( count[j] > 0 && decks[j][count[j] - 1] >= array[i] )){

				decks[j][count[j]] = array[i];
				count[j]++;
				break;
			}
		}
	}

	int min = decks[0][count[0]-1];
	int pickedRow = 0;

	for(int i = 0; i < length; i++){

		for(int j = 0; j < length; j++){

			if(count[j] > 0 && decks[j][count[j] - 1] < min){
				min = decks[j][count[j] - 1];
				pickedRow = j;
			}
		}
		sortedArr[i] = min;
		count[pickedRow]--;

		for(int j = 0; j < length; j++)

			if(count[j] > 0){
				min = decks[j][count[j] - 1];
				pickedRow = j;
				break;
			}
	}
	//freeing up the memory
	free(count);
	
	//returning already sorted array 
	return sortedArr;
}

int main(int argc,char* argv[])
{

	//array to store the values from the file 
	int *values;

	//temp array to store the sorted array 
	int *sortedArr;

	//if no arguments are provided, show the message for the user
	if (argc < 2){
    	printf("You are supposed to input the file you are working with!\n");
	} 

	//starting the timer for the time consuming 
    clock_t begin = clock();

	//repeating the sort method for the 1000 times 
	for (int i = 0; i < 1000; i++){

        FILE* f = fopen (argv[1], "r");

        //where to store the length of the array 
        int length = 0;

        //reading the length of the array 
        fscanf (f, "%d", &length);

		//assigning memory for length * 4(1 int length) bites for the array
		values = (int*)malloc((length)*sizeof(int));

		//inputing values inside the array 
		int temp;

		//counter is used to store the values one by one
		int counter = 0;

		//input values untill we reach end of the file 
		while (!feof (f))
        {  
            fscanf (f, "%d", &temp);  
            values[counter] = temp;   
            counter++; 
        }


		//closing the file we are working with 
        fclose (f);

		//calling sort function 
		sortedArr = patienceSort(values,length);
	}

	//closing the timer for the time consuming 
    clock_t end = clock();

	//freeing up the memory
	free(values);
	free(sortedArr);

    printf("Spent: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);

}