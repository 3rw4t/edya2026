#include <stdio.h>

void swap(int *num1, int *num2){
  int buff = *num1;
  *num1 = *num2;
  *num2 = buff;
}

int main(void)
{
  int a = 1, b=2;
  printf("a = %d\n", a);
  printf("b = %d\n", b);

  swap (&a, &b);

  printf("a = %d\n", a);
  printf("b = %d\n", b);
  return 0;
}
