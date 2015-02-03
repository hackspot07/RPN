#include "../StackADT/stack.h"
#include <stdio.h>

typedef struct result Result;

struct result {
  int error;
  int status;
};

int evaluate(char *expression);