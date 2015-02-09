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

void test_fillspace_return_one_if_value_filled(){
	Queue queue = createQueue();
	char space = ' ';
	assertEqual(fillSpace(queue,(void*)space),1);	
};

void test_checkPrecedence_return_2_for_plus(){
	char operators[] = {'+','-','*','/','\0'};
	assertEqual(checkPrecendence(operators[0]),2);
	assertEqual(checkPrecendence(operators[1]),2);
	assertEqual(checkPrecendence(operators[3]),4);

};

void test_isRearSpace_return_1_if_rear_have_space(){
	Queue queue = createQueue();
	char space = ' ';
	nQueue(queue, (void*)space);
	assertEqual(isRearSpace(queue),1);
};

void test_isRearSpace_return_0_if_rear_have_novalue(){
	Queue queue = createQueue();
	char nospace = '1';
	nQueue(queue, (void*)nospace);
	assertEqual(isRearSpace(queue),0);
};

void test_handleOperandInPostFix_rteurn_1_if_there_is_no_space_rear(){
	Queue queue = createQueue();
	char operand = '1';
	assertEqual(handleOperandInPostFix(queue,operand),1);
};

void test_handleOperandForInfix_rteurn_0_if_there_is_space_rear(){
	Queue queue = createQueue();
	char space = ' ';
	nQueue(queue, (void*)space);
	assertEqual(handleOperandInPostFix(queue,space),0);
};

void test_handleOperandInPostFix_rteurn_2_if_there_is_two_diff_values(){
	Queue queue = createQueue();
	char space = ' ',operand ='1';
	nQueue(queue, (void*)operand);
	assertEqual(handleOperandInPostFix(queue,space),2);
};

void test_shiftOneElementFromStackToQueue_pop_the_value_from_stack_and_fill_into_queue(){
	Stack stack = createStack();
	Queue queue = createQueue();
	char data = '2';
	push(stack,(void*)data);
	assertEqual(shiftOneElementFromStackToQueue(stack,queue),2); 
};

void test_isRearSpace_return_0_if_rear_have_null(){
	Queue queue = createQueue();
	assertEqual(isRearSpace(queue),0);
};

void test_it_return_infix_topostFix(){
	char* infix = "2 + 3 * 4";
	char* postFix = "2 3 4 * +";
	char* result = calloc(strlen(postFix)+1,sizeof(char));
	result = infixToPostfix(infix);
	
	assertEqual(strcmp(result,postFix),0);
	free(result);
};

void test_it_return_infix_postFix_with_paranthesis(){
	char* infix = "(2 + 3) * 4";
	char* postFix = "2 3 + 4 *";
	char* result = calloc(strlen(postFix)+1,sizeof(char));
	result = infixToPostfix(infix);

	assertEqual(strcmp(result,postFix),0);
	free(result);
};

void test_it_return_infix_postFix_with_paranthesis_evaluate(){
	char* infix = "(2 + 3 + 5) * 4";
	char* postFix = "2 3 + 5 + 4 *";
	char* result = calloc(strlen(postFix)+1,sizeof(char));
	result = infixToPostfix(infix);
	
	assertEqual(strcmp(result,postFix),0);
	free(result);
};

void test_it_return_postFix_with_paranthesis_evaluate(){
	char* infix = "5 + 7 * 4 - 1";
	char* postFix = "5 7 4 * + 1 -";
	char* result = calloc(strlen(postFix)+1,sizeof(char));
	result = infixToPostfix(infix);

	assertEqual(strcmp(result,postFix),0);
	free(result);
};

void test_it_return_postFix_with_paranthesis_evaluate_with_following(){
	char* infix = "(5 + (7 * 4)) - 1";
	char* postFix = "5 7 4 * + 1 -";
	char* result = calloc(strlen(postFix)+1,sizeof(char));
	result = infixToPostfix(infix);
	
	assertEqual(strcmp(result,postFix),0);
	free(result);
};
void test_it_return_postFix_with_paranthesis_evaluate_with_following_post(){
	char* infix = "(5 + 7) * (4 - 1)";
	char* postFix = "5 7 + 4 1 - *";
	char* result = calloc(strlen(postFix)+1,sizeof(char));
	result = infixToPostfix(infix);
	
	assertEqual(strcmp(result,postFix),0);
	free(result);
};

void test_it_return_postFix_with_paranthesis_evaluate_with_following_post_result_will_be_12(){
	char* infix = "(5 + 7) * (4 - 1) / (9 / 3)";
	char* postFix = "5 7 + 4 1 - * 9 3 / /";
	char* result = calloc(strlen(postFix)+1,sizeof(char));
	result = infixToPostfix(infix);
	
	assertEqual(strcmp(result,postFix),0);
	free(result);
};

void test_it_return_postFix_with_paranthesis_evaluate_with_following_post_result_will_be_0(){
	char* infix = "[((5 + 7)] * (4 - 1)) / (3 / 9 * 6)";
	char* postFix = "5 7 + 4 1 - * 3 9 / 6 * /";
	char* result = calloc(strlen(postFix)+1,sizeof(char));
	result = infixToPostfix(infix);
	
	assertEqual(strcmp(result,postFix),0);
	free(result);
};

void test_49_convert_it_to_an_equivalent_valid_Postfix_expression(){
	char *result;
	char *expression = "3 + [4 *2 / ((1 - 5))] ^ 2";
	char *expected="3 4 2 * 1 5 - 2 ^ / +";
	result = infixToPostfix(expression);

	assertEqual(strcmp(result,expected),0);
}