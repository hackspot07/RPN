#include <stdio.h>
typedef void TestFn(void);
typedef struct{
	char* name; 
	TestFn* fn;
} Test;

//code to be updated starts
TestFn setup,teardown,fixtureSetup,fixtureTearDown,test_evaluate_expression_will_give_5,test_evaluate_expression_will_give_1,test_evaluate_expression_will_give_6,test_evaluate_expression_will_give_0,test_evaluate_expression_will_give_5_after_evaluate,test_evaluate_expression_will_give_120_after_evaluate,test_evaluate_expression_will_give_35,test_evaluate_expression_will_give_402,test_evaluate_expression_will_give_1002,test_evaluate_expression_will_give_and_0;
Test test[] = {"test_evaluate_expression_will_give_5",test_evaluate_expression_will_give_5,"test_evaluate_expression_will_give_1",test_evaluate_expression_will_give_1,"test_evaluate_expression_will_give_6",test_evaluate_expression_will_give_6,"test_evaluate_expression_will_give_0",test_evaluate_expression_will_give_0,"test_evaluate_expression_will_give_5_after_evaluate",test_evaluate_expression_will_give_5_after_evaluate,"test_evaluate_expression_will_give_120_after_evaluate",test_evaluate_expression_will_give_120_after_evaluate,"test_evaluate_expression_will_give_35",test_evaluate_expression_will_give_35,"test_evaluate_expression_will_give_402",test_evaluate_expression_will_give_402,"test_evaluate_expression_will_give_1002",test_evaluate_expression_will_give_1002,"test_evaluate_expression_will_give_and_0",test_evaluate_expression_will_give_and_0};
char testFileName[] = {"rpnTest.c"};
void _setup(){/*CALL_SETUP*/}
void _teardown(){/*CALL_TEARDOWN*/}
void fixtureSetup(){}
void fixtureTearDown(){}
//code to be updated ends

int testCount;
int passCount;
int currentTestFailed;

int assert_expr(int expr, const char* fileName, int lineNumber, const char* expression){
	if(expr) return 0;
	currentTestFailed = 1;
	printf("\t %s : failed at %s:%d\n",expression, fileName,lineNumber);
	return 1;
}
int assert_equal(int val1, int val2, const char* fileName, int lineNumber,const char* expr1,const char* expr2){
	if(val1 == val2) return 0;
	currentTestFailed = 1;
	printf("\t %d == %d: failed in assertEqual(%s,%s) at %s:%d\n",val1,val2,expr1,expr2, fileName,lineNumber);
	return 1;
}

void runTest(char* name, TestFn test){
	testCount++,currentTestFailed=0;
	printf("**  %s\n",name);
	_setup();
		test();
	_teardown();
	if(!currentTestFailed) passCount++;	
}
int main(int argc, char const *argv[]){		
	int i,total = sizeof(test)/sizeof(Test);	
	fixtureSetup();
	testCount=0,passCount=0;
	printf("**------ %s ------\n",testFileName);
	for (i = 0; i < total; ++i)
		runTest(test[i].name,test[i].fn);	
	printf("** Ran %d tests passed %d failed %d\n",testCount,passCount,testCount-passCount);
	fixtureTearDown();	
	return 0;
}