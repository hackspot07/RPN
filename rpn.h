#include "../StackADT/stack.h"
#include <stdio.h>

typedef struct result Result;
typedef struct token Token;
typedef struct token* Token_ptr;

struct result {
  int error;
  int status;
};

struct token{
	void* data;
	Token_ptr next;
	void* functionPonter;
};

struct rpn_list{
	int count;
	Token_ptr head;
	Token_ptr tail;
};

Result evaluate(char *expression);