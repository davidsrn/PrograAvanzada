#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void swap(int *a, int *b){
  int aux;
  aux = *a;
  *a = *b;
  *b = aux;
}

int mayor(int a, int b){
  return (a>b);
}

int menor(int a, int b){
  return (a<b);
}

void bsort(int *arr, int n, int (*fn) (int, int)){
  int i, j;

  for (i = n -1; i > 0; i--){
    for (j = 0; j < i; j++){
      if (fn(arr[j], arr[j+1])){
        swap((arr + j), (arr + j + 1));
      }
    }
  }
}

void display(int *arr, int n){
  int i;
  for(i=0;i<n;i++){
    printf("%i ", arr[i]);
  }
  printf("\n\n");
}

int main(int argc, char* argv[]){
  int a[10] = {10, 9 , 8 , 7 , 6 , 5 , 4 , 3 , 2 , 1};

  display(a, 10);
  bsort(a, 10, mayor);
  display(a, 10);

  bsort(a, 10, menor);
  display(a, 10);


  return 0;
}
