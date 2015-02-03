#include "../StackADT/stack.h"
#include <stdio.h>

typedef struct Operators ExpOperator;


struct Operators {
	int* symbol;
};

int evaluate(char *expression);