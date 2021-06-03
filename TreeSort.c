# include <stdio.h>
# include <stdlib.h>
# include <time.h>

//node structure
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

//inserting nodes inside the tree
void insert (struct Node **newnd, int value)
{
    //if the provided node is empty, create a new one 
    if (*newnd == NULL)
    {   
        //assigning memory for the node
        *newnd = malloc(sizeof(struct Node));

        //assigning provided value to the new node and creating new empty childs 
        (*newnd) -> data = value;
        (*newnd) -> left = NULL;
        (*newnd) -> right = NULL;
    }
    else
    {
        /*
        else, if value is smaller than value inside the provided node,
        reccursively call insert and move it back 
        */
        if (value < (*newnd) -> data)
            //insert it to the left child
            insert (&((*newnd) -> left), value);
        else
            //insert it to the right child
            insert (&((*newnd) -> right), value);
    }
}

//tree sorting function 
void inorder (struct Node *newnd)
{   
    //if the provided node is not null, move it next 
    if (newnd != NULL)
    {
        inorder (newnd -> left);
        inorder (newnd -> right);
    }
}

int main(int argc, char *argv[]) {

    if (argc < 2)
    printf("You are supposed to input the file you are working with!\n");

    //starting the timer for the time consuming 
    clock_t begin = clock();
    for (int i =0; i <1000; i++){
    //initialize the original node 
    struct Node *sort ;
    sort = NULL ; 

    FILE* f = fopen (argv[1], "r");

    //where to store the length of the array 
    int length = 0;

    //reading the length of the array 
    fscanf (f, "%d", &length); 

    //creating array with the values and temporary array for copying 
    int values[length];
    int temp[length];

    //inserting values inside the arrays
    for(int i = 0; i < length; i++){
        fscanf(f, "%d", &values[i]);
        temp[i] = values[i];
    }

    //inserting values inside the tree
    for ( int j = 0 ; j < length ; j++ ){
        insert ( &sort, temp[j] ) ;
    }
    //sort function 
    inorder ( sort ) ;
    }
    //ending the timer for the time consuming 
    clock_t end = clock();

    //printing how much time spent 
    printf("\nSpent: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
 
}