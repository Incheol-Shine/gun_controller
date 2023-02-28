#include <stdio.h>
#include <stdlib.h>

int main() {
  char s[8];
  float num = -10.542f;


  sprintf(s, "%6.2f", num);

  printf("%s", s);
  return 0;
}
