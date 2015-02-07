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

void handleOperandForInfix(Queue queueForOperand,char operand){
	nQueue(queueForOperand,((void*)operand));
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

void handlePrecedence(Stack stackForOperators,Queue queueForOperand, char operator){
	int *poped_value,pcforOperator,pcforTop;
	int count = (int)stackForOperators.list->count;
	pcforOperator = checkPrecendence(operator);
	pcforTop =checkPrecendence((int)(*stackForOperators.top)->data);
	if(pcforOperator <= pcforTop){
		while(count>0 && (pcforOperator <= pcforTop)){  
			poped_value = pop(stackForOperators);
			nQueue(queueForOperand,poped_value);
			count--;
		}
	}
	push(stackForOperators,(void*)operator);
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

void performBasedOnOperator(Stack stackForOperators,Queue queueForOperand,char operator){
	int count = (int)stackForOperators.list->count;
	(count==0)?push(stackForOperators,(void*)operator):handlePrecedence(stackForOperators,queueForOperand,operator);
};

void fillRemainsInQueue(Stack stackForOperators,Queue queueForOperand){
	int* poped;
	int i,stackLength = (int)stackForOperators.list->count;
	for(i=0;i<stackLength;i++){
		poped = pop(stackForOperators);
		nQueue(queueForOperand,poped);
	}
};

char* changeIntoString(Queue queueForOperand){
	int i,queLength;
	char* postfix = malloc(sizeof(char)*queLength);
	queLength = (int)queueForOperand.list->count;
	for(i=0;i<queLength;i++)
		postfix[i] = (char)dQueue(queueForOperand);	
	return postfix;
};

void handleStringToken(char* str,Queue queueForOperand,Stack stackForOperators,int i){
	if(isOperand(str[i]))
		handleOperandForInfix(queueForOperand,str[i]);
	if(isOperator(str[i]))
		performBasedOnOperator(stackForOperators,queueForOperand,str[i]);
};

char * infixToPostfix(char * expression){
	int i,length = strlen(expression)+1;
	Queue queueForOperand = createQueue();
	Stack stackForOperators = createStack();
	char* str = malloc(sizeof(char)*length);
	strcpy(str,expression);

	for(i=0; i<length;i++){
		handleStringToken(str,queueForOperand,stackForOperators,i);
		if(str[i]=='('){
			for( ;str[i]!=')';i++)
				handleStringToken(str,queueForOperand,stackForOperators,i);
			fillRemainsInQueue(stackForOperators,queueForOperand);
		}
	}
	fillRemainsInQueue(stackForOperators,queueForOperand);
	return changeIntoString(queueForOperand);
};