#include <conio.h>
#include <stdio.h>

int main() {
  while (!kbhit())
    printf("Press a key\n");

  return 0;
}
