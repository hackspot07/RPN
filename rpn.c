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
					default:  return 0;
				};
};


void handleOperator(Stack stack,char operator){
	int* first,*second,result;
	first = pop(stack);
	second = pop(stack);
	result = operate((int)first, (int)second, operator);
	push(stack,(void*)result);
};

void handleOperand(Stack stack,char* str,int j,int index){
	int data;
	data = (j<0)? atoi(&str[index]) : atoi(&str[j]);
	push(stack,(void*)data);
};

int isOperator(operator){
	char operators[] = {'-','+','*','/','^','%','\0'};
	int i;
	for(i=0;operators[i]!='\0';i++){ 
		if(operator == operators[i])
			return 1;
	}
	return 0;
};

int isOperand(char* str,int index){
	return (str[index]>='0' && str[index] <='9')?1:0;
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
	int index = 0,j=-1,length = strlen(expression)+1;
	char* str = malloc(sizeof(char)*length);
	Stack stack = createStack();
	strcpy(str,expression);

	for(index=0; index<length; index++){
		if(isOperand(str,index)){
			(str[index+1]!=' ' && j == -1)?(j = index) : j;
			if(str[index+1]==' '){ 
				handleOperand(stack,str,j,index);
				j =-1;
			}
		}
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
		if(isOperand(str,i)){
			(str[i+1]!=' ' && j == -1)?(j = i) : j;
			if(str[i]!=' '){ 
				handleOperandForInfix(queueForOperand,str,j,i);
				j =-1;
			}
		}	
		if(isOperator(str[i]))
			performBasedOnOperator(stackForOperators,str[i]);
	}
	queLength = (int)queueForOperand.list->count;
	stackLength = (int)stackForOperators.list->count;
	for(i=0;i<queLength;i++){
		operator= dQueue(queueForOperand);
		printf("%d>>>\n",(int)operator);
	}
	for(i=0;i<stackLength;i++){
		operand = pop(stackForOperators);
		printf("%d>>>\n",*(char*)operand);
		*(char*)operand =' ';
	}
	return postfix;
};