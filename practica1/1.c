#include <stdio.h>

void bubble_sort(float arreglo[], int longitud){
  for (int iter = 0; iter < longitud - 1; iter++) {
    for (int i = 0; i < longitud - iter -1; i++) {
      if (arreglo[i] > arreglo[i + 1]){
        float aux = arreglo[i];
        arreglo[i] = arreglo[i + 1];
        arreglo[i + 1] = aux;
      }
    }
  }
}

float mediana (float *arreglo, int longitud){
  bubble_sort(arreglo, longitud);
  if (longitud % 2)
    return arreglo[longitud / 2];
  else
    return (arreglo[longitud / 2] + arreglo[longitud / 2 - 1]) / 2;
}


int main(void)
{
  float a[] = {-1.0, 2.2, 3.1, 2.9, 3.5};
  float b[] = {-1.0, 2.2, 3.1, 2.9};
  
  printf("a = %f\n", mediana(a, 5));
  printf("b = %f\n", mediana(b, 4));
  
  for(int i = 0; i < 5; i++) printf("%f ", a[i]);
  return 0;
}

