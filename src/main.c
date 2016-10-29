#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/main.h"
#include "../include/menu.h"

int main() {
  menu();
  return 0;
}

void emptyBuffer() {
  int c = 0;
  while (c != '\n' && c != EOF) {
    c = getchar();
  }
}

int getInput(char *str, int length) {
  char *positionEntree = NULL;

  if (fgets(str, length, stdin) != NULL) {
    positionEntree = strchr(str, '\n');
    if (positionEntree != NULL) {
      *positionEntree = '\0';
    }
    else {
      emptyBuffer();
    }
    return 1;
  }
  else {
    emptyBuffer();
    return 0;
  }
}
