#include "../StackADT/stack.h"
#include <stdio.h>

typedef struct result Result;

struct result {
  int error;
  int status;
};

struct operand{
	int count;
	LinkedList* list;
};

Result evaluate(char *expression);