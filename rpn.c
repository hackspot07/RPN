#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rpn.h"



int operate(int first,int second,char operator){
	switch(operator){
					case '+': return (second + first); 	
					case '-': return (second - first);
					case '*': return (second * first);
					case '/': return(first)?(second / first):0;
					default :  return 0;
				}
};


void handleOperator(Stack stack,char operator){
	int* first_val,*second_val;
	int result;
	first_val = pop(stack);
	second_val = pop(stack);
	result = operate((int)first_val, (int)second_val, operator);
	push(stack,(void*)result);
};

int handleOperand(Stack stack,char* str,int index){
	int data;
	data = atoi(&str[index]);
	push(stack,(void*)data);
	return 1;
};

int isOperator(char operator){
	char operators[] = {'-','+','*','/','^','%','\0'};
	int i;
	for(i=0;operators[i]!='\0';i++){ 
		if(operator == operators[i])
			return 1;
	}
	return 0;
};

int isOperand(char operand){
	return (operand>='0' && operand <='9')?1:0;
};

Result isValidExpression(char* str){
	Result getResult = {0,0};
	free(str);
	return getResult;
};

Result getFinalResult(char* str,Stack stack){
	Result getResult;
	getResult.error = 1;
	getResult.status = (int)(*stack.top)->data;
	free(str);
	return getResult;
};

Result evaluate(char* expression){
	int index,length = strlen(expression)+1;
	char* str = malloc(sizeof(char)*length);
	Stack stack = createStack();
	strcpy(str,expression);

	for(index=0; index<length; index++){
		if(isOperand(str[index]))
			((str[index-1]==' ' && index!=0) || index==0) ? handleOperand(stack,str,index) : 0;
		if(isOperator(str[index])){ 
			if((int)stack.list->count<2)
				return isValidExpression(str);
			handleOperator(stack,str[index]);
		}
	}
	return getFinalResult(str,stack);
};



////////////////////////////////version 4.0/////////////////////


Queue createQueue(void){
	Queue createdQueue;
	LinkedList* list = calloc(sizeof(LinkedList),1);
	createdQueue.list = list;
	createdQueue.front = &(list->head);
	createdQueue.rear = &(list->tail);
	return createdQueue;
};


int nQueue(Queue queue, void* data){
	Node_ptr newNode = create_node(data);
	int yes = add_to_list(queue.list,newNode);
	return (yes)?queue.list->count:-1;

	return (int)queue.list->count;
};

void* dQueue(Queue queue){
	return deleteElementAt(queue.list,0);
};

void handleOperandForInfix(Queue queueForOperand,char* str,int j,int index){
	int data;
	data = (j<0)? atoi(&str[index]) : atoi(&str[j]);
	nQueue(queueForOperand,((void*)data));
};

int checkPrecendence(char operator){
	switch(operator){
		case '(': return 1;
		case ')': return 1;
		case '-': return 2;
		case '+': return 2;
		case '*': return 4;
		case '/': return 4;
		case '^': return 6;
		default : return 0;
	}
};

void performBasedOnOperator(Stack stackForOperators,char operator){
	Stack temp = createStack();
	int count = (int)stackForOperators.list->count;
	int *poped,*pushedAgain;
	if((int)stackForOperators.list->count==0){
		push(stackForOperators,&operator);
	}
	if((int)stackForOperators.list->count>0){ 
		while(checkPrecendence(operator) < checkPrecendence((char)(*stackForOperators.top)->data)){ 
			poped = pop(stackForOperators);
			push(temp,(void*)poped);
		}
		push(stackForOperators,&operator);
		if((int)temp.list->count > 0){
			while((int)temp.list->count){ 
				pushedAgain = pop(temp);
				push(stackForOperators,pushedAgain);
			}
		}
	}	
};

char * infixToPostfix(char * expression){
	int i,j=-1,length = strlen(expression)+1,queLength,stackLength;
	int* operand;char* operator;
	Queue queueForOperand = createQueue();
	Stack stackForOperators = createStack();
	char* postfix = calloc(sizeof(char),length);
	char* str = malloc(sizeof(char)*length);
	strcpy(str,expression);

	for(i=0; i<=length; i++){
		if(isOperand(str[i]))
			if((str[i-1]==' ' && i!=0) || i==0)
				handleOperandForInfix(queueForOperand,str,j,i);	
		if(isOperator(str[i]))
			performBasedOnOperator(stackForOperators,str[i]);
	}
	queLength = (int)queueForOperand.list->count;
	stackLength = (int)stackForOperators.list->count;
	return postfix;
};