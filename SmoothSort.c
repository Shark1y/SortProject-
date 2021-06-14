#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef int node;
typedef long ulong;

typedef struct {
  long current;
  long previous;
} pair;

/*
equations for the Leonardo numbers work like this: 
L(0) = 1                                           
L(1) = 1                                            
L(n) = L(n-1) + L(n-2) + 1                 
*/

//stretch the tree up 
void up(pair *L){
  node tmp = L->current;
  L->current = L->current + L->previous + 1; 
  L->previous = tmp;
}

//strectch the tree down 
void down(pair *L){
  node tmp = L->previous;
  L->previous = L->current - L->previous - 1;
  L->current = tmp;
}

void normalize(ulong *p, pair *L){
  while ((*p & 1) == 0)
    up(L), *p >>= 1;
}

//swap the elements
void swap(node *x, node *y)
{
  node tmp = *x;
  *x = *y;
  *y = tmp;
}

/*
Sift the root of the stretch.
The low values are sifted up (towards index 0) from root.
*/
void sift(node *top, pair L){
//while current element is not 0
  while (L.current > 1) {
    
    node *child = top - (L.current - L.previous);
    down(&L);
    if (*child < *(top - 1)) {
      child = top - 1;
      down(&L);
    }
    if (*child <= *top)
      break;
    swap(top, child);
    top = child;
  }
}

//Trinkle the roots of the given stretches
void trinkle(node *top, ulong p, pair L){

  while (p > 0) {
    normalize(&p, &L);
    node *ntop = top - L.current;
    if (p == 1 || *ntop < *top) {
      sift(top, L);
      break;
    }
    --p;
    if (L.current == 1) {
      swap(ntop, top);
      top = ntop;
    }
    else {
      node *child = ntop + L.previous;
      pair Lc = L;
      down(&Lc);
      if (*child < *(top - 1)) {
        child = top - 1;
        down(&Lc);
      }
      if (*ntop > *child) {
        swap(ntop, top);
        top = ntop;
      }
      else {
        swap(child, top);
        sift(child, Lc);
        break;
      }
    }
  }
}

//Trinkles the stretches when the adjacent stretches are already trusty.
void semitrinkle(node *top, ulong p, pair L){
  node *ntop = top - L.current;
  if (p > 1 && *ntop > *top) {
    swap(ntop, top);
    trinkle(ntop, p - 1, L);
  }
}

//sorting algorithm for the arrays 
void smoothsort(node *m, long n){
  long i;
  ulong p = 1;
  pair L;
  L.current = 1;
  L.previous = 1;
  for (i = 1; i < n; ++i) { 
    if ((p & 3) == 3) {
      sift(m + i - 1, L);
      p = (p >> 2) + 1;
      up(&L), up(&L);
    }
    else {
      if (i + L.previous < n)
        sift(m + i - 1, L);
      else
        trinkle(m + i - 1, p, L);
      down(&L), p <<= 1;
      while (L.current > 1)
        down(&L), p <<= 1;
      ++p;
    }
  }
  trinkle(m + n - 1, p, L);
  while (i > 1) {
    --i;
    if (L.current == 1) {
      --p;
      normalize(&p, &L);
    }
    else {
      --p;
      down(&L), p = (p << 1) + 1;
      semitrinkle(m + (i - L.previous) - 1, p, L);
      down(&L), p = (p << 1) + 1;
      semitrinkle(m + i - 1, p, L);
    }
  }
}

int main(int argc, char *argv[]) {
    if (argc < 2)
    printf("You are supposed to input the file you are working with!\n");

    //starting the timer for the time consuming 
    clock_t begin = clock();

    for (int i =0; i <1000; i++){

        FILE* f = fopen (argv[1], "r");

        //where to store the length of the array 
        int length = 0;

        //reading the length of the array 
        fscanf (f, "%d", &length); 


        int values[length];
        int temp[length];

        //inserting values inside the arrays
        for(int i = 0; i < length; i++){
            fscanf(f, "%d", &values[i]);
            temp[i] = values[i];
        }
        fclose(f);

        smoothsort(values, length);
    }
    //ending the timer for the time consuming 
    clock_t end = clock();

    //printing how much time spent
    FILE* final = fopen ("final.txt", "a+");
    fprintf(final, "\nSpent: %f seconds\n", (double)(end - begin) / CLOCKS_PER_SEC);
    fprintf(final, "Smooth ______ values.\n");
    fclose(final);
    return 0;
}