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
	char* operators = "+-*/%^" ;
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
			((str[index-1] ==' ' && index!=0) || index==0) ? handleOperand(stack,str,index) : 0;
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
};

void* dQueue(Queue queue){
	return deleteElementAt(queue.list,0);
};

int isRearSpace(Queue tokenQueue){
	char space = ' ',rear; 
	if((int)tokenQueue.list->count > 0)
		rear = (char)(*tokenQueue.rear)->data;
	return (rear==' ')?1:0;
};

void stackToQueueShift(Stack stack,Queue queue){
	int i,stackLength = (int)stack.list->count;
	for(i=0;i<stackLength;i++)
		shiftOneElementFromStackToQueue(stack,queue);
};

int handleOperandInPostFix(Queue tokenQueue,char operand){
	if(operand==' ') 
		return (!isRearSpace(tokenQueue))?nQueue(tokenQueue,((void*)operand)):0;
	else
		return 	nQueue(tokenQueue,((void*)operand));
};

int checkPrecendence(char operator){
	switch(operator){
		case '-': return 2;
		case '+': return 2;
		case '*': return 4;
		case '/': return 4;
		case '^': return 6;
		default : return 0;
	}
};

int fillSpace(Queue tokenQueue,void* space){
	return (!isRearSpace(tokenQueue))?nQueue(tokenQueue,space):0;
};

int shiftOneElementFromStackToQueue(Stack stackForOperators,Queue tokenQueue){
	char *poped_value;
	char space = ' '; 
	poped_value = pop(stackForOperators);
	fillSpace(tokenQueue,(void*)space);
	return nQueue(tokenQueue,((void*)poped_value));
};

int handlePrecedence(Stack stackForOperators,Queue tokenQueue, char operator){
	int count = (int)stackForOperators.list->count;
	int pcforOperator = checkPrecendence(operator);
	int pcforTop = checkPrecendence((char)(*stackForOperators.top)->data);
	if(pcforOperator <= pcforTop)
		while((pcforOperator <= pcforTop) && count>0){ 
			shiftOneElementFromStackToQueue(stackForOperators,tokenQueue);
			if(count>1)
				pcforTop = checkPrecendence((char)(*stackForOperators.top)->data);
			count--;
		}
	return push(stackForOperators,(void*)operator);
};

int handleOperators(Stack stackForOperators,Queue tokenQueue,char operator){
	int count = (int)stackForOperators.list->count;
	return (count==0)?push(stackForOperators,(void*)operator):handlePrecedence(stackForOperators,tokenQueue,operator);
};


int handleToken(char* str,Queue tokenQueue,Stack stackForOperators,int i){
	if(isOperand(str[i]) || str[i]==' ')
		return handleOperandInPostFix(tokenQueue,str[i]);
	if(isOperator(str[i]))
		return handleOperators(stackForOperators,tokenQueue,str[i]);
	return 0;
};

char* changeIntoString(Queue tokenQueue){
	int i,queLength = (int)tokenQueue.list->count;
	char* postfix = malloc(sizeof(char)*queLength);
	for(i=0;i<queLength;i++)
		postfix[i] = (char)dQueue(tokenQueue);	
	return postfix;
};

int handleParanthesis(char* str,Queue tokenQueue,Stack stackForOperators,int index){
	Stack stackTemp = createStack();
	for( ;str[index]!=')';index++) 
		handleToken(str,tokenQueue,stackTemp,index);
	stackToQueueShift(stackTemp,tokenQueue);
	return index;
};

int handleMinusDigits(char* str,Queue tokenQueue,int i){
	if(str[i]=='-' || str[i]=='+')
		if(isOperand(str[i+1])){ 
			(str[i]=='+')?handleOperandInPostFix(tokenQueue,str[i+1]):
			(handleOperandInPostFix(tokenQueue,str[i]) && handleOperandInPostFix(tokenQueue,str[i+1]));
			i = i+2;
		}
	return i;
};

char * infixToPostfix(char * expression){
	int i,length = strlen(expression)+1;
	Queue tokenQueue = createQueue();
	Stack stackForOperators = createStack();
	char* str = malloc(sizeof(char)*length);
	strcpy(str,expression);

	for(i=0; i<length; i++){
		i = handleMinusDigits(str,tokenQueue,i);
		handleToken(str,tokenQueue,stackForOperators,i);
		if(str[i]=='(')
			i =	handleParanthesis(str,tokenQueue,stackForOperators,i);
	}
	stackToQueueShift(stackForOperators,tokenQueue);
	return changeIntoString(tokenQueue);
};