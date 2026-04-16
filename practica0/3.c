#include <stdio.h>

void set_int(int *var ){
  if (*var == 0) {
    *var = 1;
  }else{
    *var = 0;
  };
  
}

int main(void){
  int var;
  for (int i = -2;i< 3; i++) {
    var = i;
    set_int(&var);
    printf("%d\n", var);
  }

  return 0;
}
