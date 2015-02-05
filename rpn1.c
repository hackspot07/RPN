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


Scan the Infix string from left to right.
Initialise an empty stack.
If the scannned character is an operand, add it to the Postfix string. 
If the scanned character is an operator and if the stack is empty Push the character to stack.
If the scanned character is an Operand and the stack is not empty, compare the precedence of the character with the element on top of the stack (topStack). 
If topStack has higher precedence over the scanned character Pop the stack else Push the scanned character to stack. 
Repeat this step as long as stack is not empty and topStack has precedence over the character.
Repeat this step till all the characters are scanned.
(After all characters are scanned, we have to add any character that the stack may have to the Postfix string.) 
If stack is not empty add topStack to Postfix string and Pop the stack. Repeat this step as long as stack is not empty.
Return the Postfix string.