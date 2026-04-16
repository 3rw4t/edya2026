#include <stdio.h>
#include <stdlib.h>
char *get_new_line(void){
  char *buff = malloc(sizeof(char)* 100);
  int i = 0;
  do {
    buff[i] = getchar();
    i++;
  } while ((i < 100) && !(buff[i - 1] == '\n'));
  return buff;
}

int main(void)
{
  char *line = get_new_line();
  printf("get_new_line = %s\n", line);
  return 0;
}
