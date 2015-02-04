#include "rpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int operate(int first,int second,char operator){
	switch(operator){
					case '+': return (second + first); 	
					case '-': return (second - first);
					case '*': return (second * first);
					case '/': return(first)?(second / first):0;
					default:  return 0;
				}
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

int isOperator(char* str,int index){
	return (str[index]=='-' || str[index] =='*' || str[index] =='/' || str[index] =='+')?1:0;
};

int isOperand(char* str,int i){
	return (str[i]>='0' && str[i] <='9')?1:0;
};

Result evaluate(char* expression){
	Result getResult;
	int index = 0,result,count,j=-1,last,operand=0,operator=0,status,length = strlen(expression);
	char* str = malloc(sizeof(char)*length);
	Stack stack = createStack();
	strcpy(str,expression);

	for(index=0; index<length; index++){
		if(isOperand(str,index)){
			(str[index+1]!=' ' && j == -1)?(j = index) : j;
			if(str[index+1]==' '){ 
				operand++;
				handleOperand(stack,str,j,index);
				j =-1;
			}
		}
		if(isOperator(str,index)){
			operator++;
			handleOperator(stack,str[index]);
		}
	}
	if(operand != operator+1){
		Result getResult = {0,0};
		free(str);
		return getResult;
	}
	getResult.error = 1;
	getResult.status = (int)(*stack.top)->data;
	free(str);
	return getResult;
};