#include "rpn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int process(int first,int second,char operator){
	switch(operator){
					case '+': return (second + first); 	
					case '-': return (second - first);
					case '*': return (second * first);
					case '/': return(first)?(second / first):0;
					default:  return 0;
				}
};

Token* createToken(void* data,void* type){
	Token *created_token = calloc(sizeof(Token),1);
	created_token->data = data;
	return created_token;
};
