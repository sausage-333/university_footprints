#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <assert.h>
#include "stack.h"

/* data types */
enum {LEFT_PARENS,
	  RIGHT_PARENS,
	  PLUS,
	  MINUS,
	  TIMES,
	  DIVISION,
	  POWER,
	  INTEGER,
	  DOUBLE
};

struct StackItem {
	int type;                /* data type - one of the above enum values */
	union {
		long   int_val;      /* integer value */
		double double_val;   /* double value */
	};
} ;

/*----------------------------------------------------------*/
static int
GetOperatorType(char x)
{
	switch (x) {
	case '+': return PLUS;
	case '-': return MINUS;
	case '*': return TIMES;
	case '/': return DIVISION;
	case '(': return LEFT_PARENS;
	case ')': return RIGHT_PARENS;
	case '^': return POWER;
	default:
		fprintf(stderr, "error x = %c\n", x);
		exit(-1);
	}
	return 0;
}
/*----------------------------------------------------------*/
static int
GetOperatorPrec(int type)
{
	return (type == PLUS) ? MINUS : ((type == TIMES) ? DIVISION : type);
}
/*----------------------------------------------------------*/
static int
HasPrecendence(int type1, int type2)
{
	return GetOperatorPrec(type1) >= GetOperatorPrec(type2);
}
/*----------------------------------------------------------*/
static StackItem_T
AllocateStackItem(int type) 
{
	StackItem_T p = malloc(sizeof(struct StackItem));
	
	if (p == NULL) {
		fprintf(stderr, "malloc() failed in allocating a stack item\n");
		exit(-1);
	}
	p->type = type;
	return p;
}
/*----------------------------------------------------------*/
static int
DoOperation(StackItem_T x, StackItem_T y, StackItem_T op)
{
	/* do the operation. return FALSE if over/underflow happens
	   otherwise return TRUE */
	switch (op->type) {
	case PLUS:
		x->int_val = x->int_val + y->int_val;
		break;
	case MINUS:
		x->int_val = x->int_val - y->int_val;
		break;
	case TIMES:
		x->int_val = x->int_val * y->int_val;
		break;
	case DIVISION:
		if (y->int_val == 0) {
			fprintf(stderr, "Error: Divide by 0\n");
			exit(-1);
		}
		x->int_val = x->int_val / y->int_val;
		break;
	case POWER: 
		{
			int unit = x->int_val;
			int i;
			
			for (i = 1; i < y->int_val; i++)
				x->int_val *= unit;
		}
		break;
	default:
		fprintf(stderr, 
				"Invalid operator type: %d\n", op->type);
		exit(-1);
	}
}
/*----------------------------------------------------------*/
static void
PrintOperator(StackItem_T op)
{
	switch (op->type) {
	case PLUS:     printf("+ "); break;
	case MINUS:    printf("- "); break;
	case TIMES:    printf("* "); break;
	case DIVISION: printf("/ "); break;
	case POWER:    printf("^ "); break;
	default:
		fprintf(stderr, 
				"Error: Invalid operator type in PrintOperator()\n");
		exit(-1);
	}
}

/*----------------------------------------------------------*/
void
Calculate(void)
{
	char buf[1024];
	int i, j, k; 
	StackItem_T p, q, r, s; // used parameter name instead of op 
	Stack_T op_st, main_st;  /* operator stack, main stack */
	int left_parens = 0, right_parens = 0;  /* store the number of left and right parenthesis */ 


	printf(">> ");

	/* read the expression from stdin */
	if (fgets(buf, sizeof(buf), stdin) == NULL) {
		fprintf(stderr, "error in reading from stdin\n");
		exit(-1);
	}
	
	/* initialize the stack */
	op_st = Stack_Init();
	if (op_st == NULL) {
		fprintf(stderr, "allocating the operator stack failed\n");
		exit(-1);
	}
	main_st = Stack_Init();
	if (main_st == NULL) {
		fprintf(stderr, "allocating the main stack failed\n");
		Stack_Release(op_st);
		exit(-1);
	}
	
	for (i = 0; buf[i]; i++) {
		
		/* ignore space */
		if (isspace(buf[i]))
			continue;
		
		switch (buf[i]) {
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
			if (!buf[i+1] || buf[i+1] == '+' || buf[i+1] == '-' || buf[i+1] == '*'
			 || buf[i+1] == '/' || buf[i+1] == '^' || buf[i+1] == ')'){
			 	fprintf(stderr, "Syntax error\n");
			 	exit(-1);
			 }
			
			p = AllocateStackItem(GetOperatorType(buf[i]));
			q = Stack_Top(op_st);
			if (Stack_IsEmpty(op_st)) {
				Stack_Push(op_st, p);
			}
			else {
				while (HasPrecendence(q->type, p->type)) {
					q = Stack_Pop(op_st);
					r = Stack_Pop(main_st);
					s = Stack_Pop(main_st);
					DoOperation(s, r, q);
					Stack_Push(main_st, s);
					q = Stack_Top(op_st);
					if (q == NULL) {
						break;
					}
				}
				Stack_Push(op_st, p);
			}
			break;
			
			// -------------------------------------------------------
			//	Your code here!
			//		- Do calculation if current operator "p" has lower 
			//		  precendence than the top of the operator stack "op_st"
			//		- Print errors if the expression is wrong
			//		- Hint : Use the function "HasPrecendence"
			// -------------------------------------------------------
			
		case '(':
			if (!buf[i+1] || buf[i+1] == '+' || buf[i+1] == '-' || buf[i+1] == '*'
			 || buf[i+1] == '/' || buf[i+1] == '^' || buf[i+1] == ')' || isdigit(buf[i-1])){
			 	fprintf(stderr, "Syntax error\n");
			 	exit(-1);
			 }
			  
			if (left_parens < right_parens){
				fprintf(stderr, "Syntax error\n");
				exit(-1);
			} 
			
			left_parens++;	
			p = AllocateStackItem(LEFT_PARENS);
			Stack_Push(op_st, p);
			break;
			
			// -------------------------------------------------------
			//	Your code here!
			//		- Do action when the input is (
			//		- Print errors if the expression is wrong
			// -------------------------------------------------------
			
		case ')':
			if (isdigit(buf[i+1]) || buf[i+1] == '('){
				fprintf(stderr, "Error: wrong expression\n");
				exit(-1);
			}
			if(left_parens <= right_parens){
				fprintf(stderr, "Syntax error\n");
				exit(-1);
			}
			
			right_parens++;
			k=Stack_Top(op_st)->type;
			while (k != 0){
				q = Stack_Pop(op_st);
				r = Stack_Pop(main_st);
				s = Stack_Pop(main_st);
				DoOperation(s, r, q);
				Stack_Push(main_st, s);
				k=Stack_Top(op_st)->type;
			}
			Stack_Pop(op_st);
			break;
			
			// -------------------------------------------------------
			//	Your code here!
			//		- Do calculation the expression in ( )
			//		- Print errors if the expression is wrong
			// -------------------------------------------------------
			
		default:
			if (!isdigit(buf[i])) {
				fprintf(stderr, "Error: wrong expression\n");
				exit(-1);
			}
			
			char temp[128];
			
			temp[0] = buf[i];
			for (j = 1; j < sizeof(temp); j++) {
				if (!buf[i+1] || !isdigit(buf[i+1])) {
					temp[j] = 0;
					break;
				}
				i++;
				temp[j] = buf[i];
			}
			p = AllocateStackItem(INTEGER);
			p->int_val = atoi(temp);
			Stack_Push(main_st, p);			
		}
	}
	
	if (left_parens != right_parens){
		fprintf(stderr, "Error: wrong expression\n");
		exit(-1);
		}
	
	while (!Stack_IsEmpty(op_st)){
		q = Stack_Pop(op_st);
		r = Stack_Pop(main_st);
		s = Stack_Pop(main_st);
		DoOperation(s, r, q);
		Stack_Push(main_st, s);					
	}
	
	// -------------------------------------------------------
	//	Your code here!
	//		- Do remaining calculations
	//		- Print errors if the expression is wrong
	// -------------------------------------------------------
	
	p = Stack_Pop(main_st);
	if (p == NULL || !Stack_IsEmpty(main_st)) {
		fprintf(stderr, "Error: wrong expression\n");
		exit(-1);
	}
	
	/* print the final result */
	printf("= %d\n", p->int_val);
	free(p);
}

/* comment out the following line on Linux */
//extern init();

/*----------------------------------------------------------*/
int main(void)
{
	//init(); /* comment out this line on Linux */

	while (1) 
		Calculate();

	return 0;
}
