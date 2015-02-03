#include "rpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int operate(int first,int second,char operator){
	switch(operator){
					case '+': return (second + first); break;
					case '-': return (second - first); break;
					case '*': return (second * first); break;
					case '/': return (second / first); break;
					default:  printf("Wrong Notation Plz Give Right Notation"); break;
				}
	return -1;
};



int evaluate(char* expression){
	int i = 0,result,count,data,j=0;
	int* first,*second,length = strlen(expression)+1;
	char str[256];
	Stack stack = createStack();
	strcpy(str,expression);

	while(i<length){
		if(str[i]>='0' && str[i] <='9'){ 
			if(str[i+1]==32){ 
				data = atoi(&str[j]);
				push(stack,(void*)data);
				j = i+1;
			}
		}else if(str[i]>=42 && str[i] <=47){
			first = pop(stack);
			second = pop(stack);
			result = operate((int)first, (int)second, str[i]);
			push(stack,(void*)result);
		}
		i++;
	}

	return (int)(*stack.top)->data;
};
