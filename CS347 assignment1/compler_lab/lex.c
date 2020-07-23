#include "lex.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define maxsize 1024

char* yytext = ""; /* Lexeme (not '\0'
                     terminated)              */
int yyleng   = 0;  /* Lexeme length.           */
int yylineno = 0;  /* Input line number        */
int i;
int lex(void){
//fp=fopen("input_file","r"); 
   static char input_buffer[1024];
   char        *current;

   current = yytext + yyleng; /* Skip current
                                 lexeme        */

   while(1){       /* Get the next one         */
      while(!*current ){
         /* Get new lines, skipping any leading
         * white space on the line,
         * until a nonblank line is found.
         */

         current = input_buffer;
         if(!gets(input_buffer)){
            *current = '\0' ;

            return EOI;
         }
         ++yylineno;
         while(isspace(*current))
            ++current;
          
          if(input_buffer[0]=='\0')
            continue;

        if(yylineno>1)
        {
        	printf("]\n");printf("[ ");

        }
        else 
        {
        	printf("[ ");
        }
      }
      for(; *current; ++current){
         /* Get the next token */
         yytext = current;
         yyleng = 1;
         switch( *current ){
           case ';':
            return SEMI;
           case '+':
            return PLUS;
           case '-':
            return MINUS;
           case '*':
            return TIMES;
           case '/':
            return DIV;
           case '(':
            return LP;
           case ')':
            return RP;
            case '{':
            return LC;
           case '}':
            return RC;
           case '=':
             if(*(current+1)=='=')
           {
           	++current;
           	return EQL;
           }
           else
             return ASSIGN;
           case '<':
           	if(*(current+1)=='=')
           		{   ++current;
           			return LE;
           		}
           	else
           		return LT;
           	case '!':
           	if(*(current+1)=='=')
           	{
           		++current;
           		return NOT_EQL;
           	}
           	else
           		return -1;
           	case '>':
           	 if(*(current+1)=='=')
           	 {
           	 	++current;
           	 	return GE;
           	 }
           	 else
           	 return GT;
           case '\n':
           case '\t':
           case ' ' :
            break;
           default:
            if(!isalnum(*current))
               printf("Not alphanumeric <%c>\n", *current);
            else{
               while(isalnum(*current))
                  ++current;
               yyleng = current - yytext;
               i=0;
				if(yytext[0]<='9' && yytext[0]>='0')
				{

					for(i=1;i<yyleng;i++)
					{
						if(yytext[i]<='9' && yytext[i]>='0')
							continue;
						else
						{	
							break;
						}
					}
				  if(i==yyleng)
			      return NUM;
				}
				else
				{
					if(yyleng==2)
					{
					if(strncmp(yytext,"if",2)==0)
					return IF;
					if(strncmp(yytext,"do",2)==0) return DO;

					}
					else if(yyleng==3)
	               {
	                //   if(strncmp(yytext,"end",3)==0) return END;
	                   if(strncmp(yytext,"int",3)==0) return INT;
	               }
	               else if(yyleng==4)
	               {
	                   if(strncmp(yytext,"then",4)==0) return THEN;
	                       
	               }
	               else if(yyleng==5)
	               {
	                   if(strncmp(yytext, "while", 5)==0) return WHILE;
	                  // if(strncmp(yytext, "begin", 5)==0) return BEGIN;
	               }

					return ID;

				}
				
				return -1;  
            }
            break;
         }

      }
   }
}


static int Lookahead = -1; /* Lookahead token  */

int match(int token){
   /* Return true if "token" matches the
      current lookahead symbol.                */

   if(Lookahead == -1)
      Lookahead = lex();

   return token == Lookahead;
}

void advance(void){
/* Advance the lookahead to the next
   input symbol.                               */

    Lookahead = lex();
}
