#include "rpn.h"
#include "expr_assert.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void test_evaluate_expression_will_give_5(){
	char *expression = "2 3 +";
	Result result = evaluate(expression);

	assertEqual(result.error,1);
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
	char *expression = "2 2 2 * 2 - 3 + +";
	Result result = evaluate(expression);

	assertEqual(result.status,7);
}

void test_evaluate_expression_will_give_true_return_true(){
	char *expression = "2 2 2 2 2 * * 2 + + 2 - *";
	Result result = evaluate(expression);

	assertEqual(result.status,20);
}

void test_evaluate_expression_will_give_true_also_return_true(){
	char *expression = "2 2 - 2 2 2 * 2 - - - -";
	Result result = evaluate(expression);

	assertEqual(result.status,0);
}

void test_RPN_calculator_that_can_evaluate_as_false(){
	char* expression = "5 1 2 + + + 4 * 5 5 55 5 5 5 + 3 - - / / / /  / / /  / / / ";
	Result result;
	result = evaluate(expression);
	assertEqual(result.error,0);
	assertEqual(result.status,0);
};


///////////////////version 4.0///////////////////////////

void test_createQueue_return_the_frtont_rear_0(){
	Queue queue = createQueue();

	assertEqual(*(int*)(queue.front),0);
	assertEqual(*(int*)(queue.rear),0);
	assertEqual((int)queue.list->count,0);
};

void test_nQueue_add_23_into_queue_and_return_1(){
	Queue queue = createQueue();
	int count,front,rear,data1 = 23,data2=25;
	count = nQueue(queue,&data1);
	count = nQueue(queue,&data2);

	assertEqual(count,2);
	assertEqual(*(int*)(*queue.front)->data,23);
	assertEqual(*(int*)(*queue.rear)->data,25);
};

void test_dQueue_delete_23_and_return_it(){
	Queue queue = createQueue();
	int* deleted,front,rear,data1 = 23,data2=25;
	nQueue(queue,&data1);
	nQueue(queue,&data2);
	deleted = dQueue(queue);

	assertEqual(*(int*)deleted, 23);
	assertEqual(*(int*)(*queue.front)->data,25);
	assertEqual(*(int*)(*queue.rear)->data,25);

};

void test_it_return_infix_topostFix(){
	char* infix = "2 + 3 * 4";
	char* postFix = "2 3 4 * +";
	char* result = infixToPostfix(infix);

	assertEqual(strcmp(result,postFix),0);
};