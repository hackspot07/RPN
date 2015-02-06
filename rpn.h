#include "../StackADT/stack.h"
#include <stdio.h>

typedef struct result Result;
typedef struct queue Queue;
typedef struct token Token;
typedef struct token* Token_ptr;

struct result {
  int error;
  int status;
};

struct queue {
	Node_ptr* front;
	Node_ptr* rear;
	LinkedList* list;
};

// struct token{
// 	void* data;
// 	Token_ptr next;
// 	void* functionPonter;
// };

// struct rpn_list{
// 	int count;
// 	Token_ptr head;
// 	Token_ptr tail;
// };



Queue createQueue(void);
int nQueue(Queue queue, void* data);
void* dQueue(Queue queue);


Result evaluate(char *expression);
char * infixToPostfix(char * expression);