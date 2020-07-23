#define EOI		0	/* End of input			*/
#define SEMI		1	/* ; 				*/
#define PLUS 		2	/* + 				*/
#define TIMES		3	/* * 				*/
#define LP		4	/* (				*/
#define RP		5	/* )				*/
#define NUM	6	/* Decimal Number or Identifier */
#define CHAR     7
#define ASSIGN 8
#define ELSE    9
#define FLOAT    10
#define IF      11
#define INT       12
#define WHILE     13
#define ID    14
#define DO 15
#define THEN 16/* Decimal Number or Identifier */
#define MINUS 17
#define DIV 18
#define LE 19
#define LT 20
#define EQL 21
#define NOT_EQL 22
#define GE 23
#define GT 24
#define LC	25	/* (				*/
#define RC	26	/* )				*/



extern char *yytext;		/* in lex.c			*/
extern int yyleng;
extern int yylineno;
