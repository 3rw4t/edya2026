#include <stdio.h>

void set_first(int arr[]){

  arr[0] = 0;

}; 


int main(void)
{
  int arr[5];
  for (int i = 0;i < 5;i++) {
    arr[i] = i+1;
  }
  
  set_first(arr);

  for (int i = 0;i < 5;i++) {
    printf("%d\n", arr[i]);
  }

  return 0;
}
