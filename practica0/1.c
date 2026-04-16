#include <stdio.h>

int main(void)
{

  int arr[5];
  arr[0] = 1;
  arr[1] = 2;
  for (int i = 0;i < 5;i++) {
    printf("%p\n", &arr[i]);
  }  
  return 0; 
}
