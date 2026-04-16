#include <stdio.h>

int main(void)
{
  int var = 1;
  char var2 = 'a';
  
  printf("%p\n%p\n", &var, &var2);
  return 0;
}
