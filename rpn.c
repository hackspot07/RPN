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

	return (int)queue.list->count;
};

void* dQueue(Queue queue){
	return deleteElementAt(queue.list,0);
};

int isRearSpace(Queue queueForOperand){
	char space = ' ',rear; 
	if((int)queueForOperand.list->count > 0)
		rear = (char)(*queueForOperand.rear)->data;
	return (rear==' ')?1:0;
};

int handleOperandForInfix(Queue queueForOperand,char operand){
	if(operand==' ') 
		return (!isRearSpace(queueForOperand))?nQueue(queueForOperand,((void*)operand)):0;
	else
		return 	nQueue(queueForOperand,((void*)operand));
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

int fillSpace(Queue queueForOperand,void* space){
	return (!isRearSpace(queueForOperand))?nQueue(queueForOperand,space):0;
};

int popAndFillInQueue(Stack stackForOperators,Queue queueForOperand){
	int *poped_value;
	char space = ' '; 
	poped_value = pop(stackForOperators);
	fillSpace(queueForOperand,(void*)space);
	return nQueue(queueForOperand,((void*)poped_value));
};

int handlePrecedence(Stack stackForOperators,Queue queueForOperand, char operator){
	int count = (int)stackForOperators.list->count;
	int pcforOperator = checkPrecendence(operator);
	int pcforTop = checkPrecendence((int)(*stackForOperators.top)->data);

	if(pcforOperator <= pcforTop){ 
		while((pcforOperator <= pcforTop) && count>0){  
			popAndFillInQueue(stackForOperators,queueForOperand);
			count--;
		}
	}
	return push(stackForOperators,(void*)operator);
};

int isOpenParanthesis(char operator){
	return (operator == '(')?1:0;
};

int isCloseParanthesis(char operator){
	return (operator == ')')?1:0;
};

char* invalidExpression(){
	return "invalidExpression";
};

int performBasedOnOperator(Stack stackForOperators,Queue queueForOperand,char operator){
	int count = (int)stackForOperators.list->count;
	return (count==0)?push(stackForOperators,(void*)operator):handlePrecedence(stackForOperators,queueForOperand,operator);
};

void fillRemainsInQueue(Stack stackForOperators,Queue queueForOperand){
	int i,stackLength = (int)stackForOperators.list->count;
	for(i=0;i<stackLength;i++)
		popAndFillInQueue(stackForOperators,queueForOperand);
};


int handleStringToken(char* str,Queue queueForOperand,Stack stackForOperators,int i){
	if(isOperand(str[i]) || str[i]==' ')
		return handleOperandForInfix(queueForOperand,str[i]);
	if(isOperator(str[i]))
		return performBasedOnOperator(stackForOperators,queueForOperand,str[i]);
	return 0;
};

char* changeIntoString(Queue queueForOperand){
	int i,queLength = (int)queueForOperand.list->count;
	char* postfix = malloc(sizeof(char)*queLength);
	for(i=0;i<queLength;i++)
		postfix[i] = (char)dQueue(queueForOperand);	
	return postfix;
};

int handleParanthesis(char* str,Queue queueForOperand,Stack stackForOperators,int i){
	for( ;str[i]!=')';i++)
		handleStringToken(str,queueForOperand,stackForOperators,i);
	fillRemainsInQueue(stackForOperators,queueForOperand);
	return i;
};

char * infixToPostfix(char * expression){
	int i,length = strlen(expression);
	Queue queueForOperand = createQueue();
	Stack stackForOperators = createStack();
	char* str = malloc(sizeof(char)*length);
	strcpy(str,expression);

	for(i=0; i<length; i++){
		handleStringToken(str,queueForOperand,stackForOperators,i);
		if(str[i]=='(')
			i =	handleParanthesis(str,queueForOperand,stackForOperators,i);
	}
	fillRemainsInQueue(stackForOperators,queueForOperand);
	return changeIntoString(queueForOperand);
};