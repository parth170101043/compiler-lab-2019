/* simplest version of calculator */
%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE *yyin;
void yyerror(char* s);
%}

/* declare tokens */
%token SELECT PROJECT CARTESIAN_PRODUCT EQUI_JOIN
%token LP RP LA RA EQUAL NOT_EQUAL LE GE DOT COMMA AND OR NOT RE
%token INT QUOTED_STRING ID
%token NEWLINE

%%
stmt_list: stmt NEWLINE stmt_list
    | stmt
    | error NEWLINE {printf("\nInvalid syntax\n");} stmt_list    
;

    

stmt: SELECT LA condition RA LP table_name RP       {printf("\nValid Syntax\n");}
    | PROJECT LA attr_list RA LP table_name RP      {printf("\nValid Syntax\n");}
    | LP table_name RP CARTESIAN_PRODUCT LP table_name RP       {printf("\nValid Syntax\n");}
    | LP table_name RP EQUI_JOIN LA condition RA LP table_name RP       {printf("\nValid Syntax\n");}
    | %empty
;

attr_list: attr COMMA attr_list
    | attr
   
;

condition: cond2 OR condition 
    | cond2
   
;

cond2: expr AND cond2
    | expr
   
;

expr: col op col
    | col op INT
    | INT op col
    | col op QUOTED_STRING
    | QUOTED_STRING op col
    | LP condition RP
    | NOT LP condition RP
   
;

col: table_name DOT column_name
    | column_name
   
;

op: LA
    | RA
    | LE
    | GE
    | EQUAL
    | NOT_EQUAL
   
;

table_name: ID
;

column_name: ID  
;

attr: ID

%%
int main(int argc, char **argv)
{
    FILE *fp; 
	char filename[50]; 
	printf("Enter the filename: \n"); 
	scanf("%s",filename); 
	fp = fopen(filename,"r"); 
	yyin = fp;
  yyparse();
}

void yyerror(char *s)
{   
}