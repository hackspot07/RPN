#include "rpn.h"
#include "expr_assert.h"
#include <stdio.h>
#include <stdlib.h>


void test_evaluate_expression_will_give_5(){
	char *expression = "2 3 +";
	Result result = evaluate(expression);

	assertEqual(result.status,5);
}

void test_evaluate_expression_will_give_1(){
	char *expression = "2 3 -";
	Result result = evaluate(expression);

	assertEqual(result.status,-1);
}

void test_evaluate_expression_will_give_6(){
	char *expression = "2 3 *";
	Result result = evaluate(expression);

	assertEqual(result.status,6);
}


void test_evaluate_expression_will_give_0(){
	char *expression = "2 3 /";
	Result result = evaluate(expression);

	assertEqual(result.status,0);
} 

void test_evaluate_expression_will_give_5_after_evaluate(){
	char *expression = "2 3 4 + -";
	Result result = evaluate(expression);

	assertEqual(result.status,-5);
}

void test_evaluate_expression_will_give_120_after_evaluate(){
	char *expression = "1 2 3 4 5 * * * *";
	Result result = evaluate(expression);

	assertEqual(result.status,120);
}


void test_evaluate_expression_will_give_35(){
	char *expression = "14 7 3 * +";
	Result result = evaluate(expression);

	assertEqual(result.status,35);
}

void test_evaluate_expression_will_give_402(){
	char *expression = "2 1000 600 - +";
	Result result = evaluate(expression);

	assertEqual(result.status,402);
}

void test_evaluate_expression_will_give_1002(){
	char *expression = "1000 200 100 / +";
	Result result = evaluate(expression);

	assertEqual(result.status,1002);
}

void test_evaluate_expression_will_give_and_1000(){
	Result result;
	char *expression = malloc(sizeof(char*));
	expression = "100000    10   1 1 / / /";
	result =  evaluate(expression);

	assertEqual(result.status,10000);
}


void test_evaluate_expression_will_give_and_0(){
	Result result;
	char *expression = malloc(sizeof(char*));
	expression = "2.5    2.5   1  1 / / /";
	result =  evaluate(expression);

	assertEqual(result.status,1);
}

void test_RPN_calculator_that_can_evaluate_parentessis_with_multiOperator(){
	char* expression = "5 1 2 + 4 * + 3 -";
	Result result;
	result = evaluate(expression);
	assertEqual(result.status,14);
};

void test_RPN_calculator_that_can_evaluate_parentessis_return_7(){
	Result result;
	char* expression = malloc(sizeof(char*));
	expression = "2 2 2 * 2 - 3 + + ";
	result = evaluate(expression);
	assertEqual(result.status,7);
};

void test_evaluate_expression_will_give_true_return_1(){
	char *expression = "2 2 2 * 2 - 3 + +  == 7  ";
	Result result = evaluate(expression);

	assertEqual(result.status,1);
}

void test_evaluate_expression_will_give_true_return_true(){
	char *expression = "2 2 2 2 2 * * 2 + + 2 - * == 20";
	Result result = evaluate(expression);

	assertEqual(result.status,1);
}

void test_evaluate_expression_will_give_true_also_return_true(){
	char *expression = "2 2 - 2 2 2 * 2 - - - ==  0";
	Result result = evaluate(expression);

	assertEqual(result.status,1);
}