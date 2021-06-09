
#include<stdlib.h>
#include<stdio.h>
#include <limits.h>

int* patienceSort(int* arr,int size){
	int decks[size][size],i,j,min,pickedRow;

	int *count = (int*)calloc(sizeof(int),size),*sortedArr = (int*)malloc(size*sizeof(int));

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(count[j]==0 || (count[j]>0 && decks[j][count[j]-1]>=arr[i])){
				decks[j][count[j]] = arr[i];
				count[j]++;
				break;
			}
		}
	}

	min = decks[0][count[0]-1];
	pickedRow = 0;

	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			if(count[j]>0 && decks[j][count[j]-1]<min){
				min = decks[j][count[j]-1];
				pickedRow = j;
			}
		}
		sortedArr[i] = min;
		count[pickedRow]--;

		for(j=0;j<size;j++)
			if(count[j]>0){
				min = decks[j][count[j]-1];
				pickedRow = j;
				break;
			}
	}

	free(count);
	
	return sortedArr;
}

int main(int argc,char* argv[])
{
	int *arr, *sortedArr, i;

	if (argc < 2){
    printf("You are supposed to input the file you are working with!\n");
	} else {

        FILE* f = fopen (argv[1], "r");

        //where to store the length of the array 
        int length = 0;

        //reading the length of the array 
        fscanf (f, "%d", &length);

		printf("%d\n", length);

		arr = (int*)malloc((length)*sizeof(int));

		printf("we came here 1(works)\n\n");

		int temp;
		int counter = 0;

		while (!feof (f))
        {  
            fscanf (f, "%d", &temp);  
            arr[counter] = temp;   
            counter++; 
        }
		printf("we came here 2(works)\n\n");

		sortedArr = patienceSort(arr,length);
		printf("we came here 3(works)\n\n");

		for(i=0;i<length;i++)
			printf("%d ",sortedArr[i]);

		printf("we came here 4\n\n");
	}

	return 0;
}