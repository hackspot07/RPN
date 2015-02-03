#include "rpn.h"
#include "expr_assert.h"
#include <stdio.h>
#include <stdlib.h>


void test_evaluate_expression_will_give_5(){
	char *expression = "2 3 +";
	int result = evaluate(expression);

	assertEqual(result,5);
}

void test_evaluate_expression_will_give_1(){
	char *expression = "2 3 -";
	int result = evaluate(expression);

	assertEqual(result,-1);
}

void test_evaluate_expression_will_give_6(){
	char *expression = "2 3 *";
	int result = evaluate(expression);

	assertEqual(result,6);
}


void test_evaluate_expression_will_give_0(){
	char *expression = "2 3 /";
	int result = evaluate(expression);

	assertEqual(result,0);
} 

void test_evaluate_expression_will_give_5_after_evaluate(){
	char *expression = "2 3 4 + -";
	int result = evaluate(expression);

	assertEqual(result,-5);
}

void test_evaluate_expression_will_give_120_after_evaluate(){
	char *expression = "1 2 3 4 5 * * * *";
	int result = evaluate(expression);

	assertEqual(result,120);
}


void test_evaluate_expression_will_give_35(){
	char *expression = "14 7 3 * +";
	int result = evaluate(expression);

	assertEqual(result,35);
}

void test_evaluate_expression_will_give_402(){
	char *expression = "2 1000 600 - +";
	int result = evaluate(expression);

	assertEqual(result,402);
}

void test_evaluate_expression_will_give_1002(){
	char *expression = "1000 200 100 / +";
	int result = evaluate(expression);

	assertEqual(result,1002);
}

void test_evaluate_expression_will_give_and_1000(){
	int result;
	char *expression = malloc(sizeof(char*));
	expression = "100000    10   1 1 / / /";
	result =  evaluate(expression);

	assertEqual(result,10000);
}


void test_evaluate_expression_will_give_and_0(){
	int result;
	char *expression = malloc(sizeof(char*));
	expression = "2.5    2.5   1  1 / / /";
	result =  evaluate(expression);

	assertEqual(result,1);
}