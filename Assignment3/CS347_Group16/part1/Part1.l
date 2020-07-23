%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

  int Statements=0;                   
    int Comments=0;
    int Blank_Lines=0;
    int Macro_def=0;
    int Variables=0;
    int Fun_Def=0;
    int Fun_Dec=0;
    int semicount=0; 
    bool Fun_Dec_possibility=0;
    bool Fun_Def_possibility=0;
    bool var_possibility=0;
    bool newline=1;
   
void check()
{
  if(newline==0)
  {newline=1;}
  else
  {
    Blank_Lines++;
  
  }
}

%}
TYPE int|char|bool|float|double
DIGIT [0-9]
CH [A-Za-z]
ID  [A-Za-z][A-Za-z0-9]*
SPACEONLY [ \t]
ARRAYOPT \[{DIGIT}*\]
STR   \"(\\.|[^"\\])*\"
ARRAY [{][^}]*[}]
CHARACTERS [;\*\,&\[\]]
%x v0
%x v1 
%x v2
%x v3
%x v4
%x v5
%x comment
%%

"#"("include"|"define")([^\/\n]*) {Macro_def++;newline=0;}
"for"{SPACEONLY}*[\n]?{SPACEONLY}*[(]{SPACEONLY}*[^;]*[;][^;]*[;][^)]*[)] {newline=0;}
[\n] {
  check();}
 "*"  {newline=0;}
 [;]{SPACEONLY}*[\/]  {newline=0;}
 [;]  {Statements++;newline=0;}

{SPACEONLY}* {}
{TYPE}("*"|{SPACEONLY}) {var_possibility=1;
newline=0;BEGIN(v0);}
{TYPE}[\n]  {
  check();
  var_possibility=1;
  BEGIN(v0);
  
}
{STR} {newline=0;}
[\/][\/][^\n]*  {Comments++;Statements++;newline=0;}
[\/]"*" {BEGIN(comment);}
<comment>[^*\n]* {newline=0;}
<comment>"*"+[^*/\n]* {newline=0;}
<comment>\n {check();Statements++;}
<comment>"*"[\/] {newline=0;Comments++;Statements++ ;BEGIN(INITIAL);}
 [a-zA-Z0-9\!\"#\^\\\|&@*\(\)\{\}\[\]\%\?\.\-\+=\,<>]  {newline=0;}

"void"{SPACEONLY}  {  Fun_Dec_possibility=1;Fun_Def_possibility=1;newline=0;BEGIN(v0);}
"void"[\n]  { Blank_Lines++; Fun_Dec_possibility=1;Fun_Def_possibility=1;check();BEGIN(v0);}
("*")* {newline=0;}
<v0>("*"|{SPACEONLY})*{ID}  {newline=0;BEGIN(v1);}
<v0>\n  {check();}
<v0>{SPACEONLY}* {}
<v1>{ARRAYOPT}  {Fun_Def_possibility=0;Fun_Dec_possibility=0;newline=0;}
<v1>\n  {check();}
<v1>{SPACEONLY}*  {}
<v1>[=;(,] {newline=0;
  if(yytext[0]=='=')
  {
   BEGIN(v2);
  }
  else if(yytext[0]==';')
  {Statements++;
    Variables++;
    Fun_Def_possibility=0;
    Fun_Dec_possibility=0;
    BEGIN(INITIAL);
  }
 
 if(yytext[0]=='(')
  {
    var_possibility=0;
  
    BEGIN(v3);
  }
  if(yytext[0]==',')
  {
    Variables++;
    BEGIN(v5);
  }
}


<v2>\n   {check();}
<v2>{SPACEONLY}* {}
<v2>("'"{CH}"'"|{DIGIT}*|{STR}|{ARRAY}){SPACEONLY}* {newline=0;
BEGIN(v5);}   


<v3>\n  {check();}
<v3>{SPACEONLY}*  {}
<v3>({TYPE}|{ID}|{CHARACTERS})  {newline=0;}
<v3>[)]{SPACEONLY}*  { newline=0;
  BEGIN(v4);}



<v4>\n  {check();}
<v4>{SPACEONLY}* {}
<v4>[;{] {
  newline=0;
  if(yytext[0]==';')
  {
    Fun_Dec++;
    Statements++;
  }
  else
  {
    Fun_Def++;
    Statements++;
  }
  
  Fun_Dec_possibility=0;
  Fun_Def_possibility=0;
  BEGIN(INITIAL);
}

<v5>\n  {check();}
<v5>{SPACEONLY}* {}
<v5>{STR} {newline=0;}
<v5>[^;\,\n]  {newline=0;}

<v5>"\,"  {Variables++;newline=0;
}
<v5>[;] {
  Statements++;
  Variables++;
  newline=0;
BEGIN(INITIAL);}
%%
int yywrap(){}

int main()
{
	
	FILE *fp; 
	char name[30]; 
	printf("Enter your input file: \n"); 
	scanf("%s",name); 
	fp = fopen(name,"r"); 
	yyin = fp;
	yylex();
  Statements=Statements+Macro_def;

  printf("\nStatements %d \n",Statements);
    printf("Variables %d \n",Variables);
    printf("Function dec %d \n",Fun_Dec);
    printf("Macro_def %d \n",Macro_def);
    printf("Fun_Def %d \n",Fun_Def);
    printf("Blank_Lines %d \n",Blank_Lines);
    printf("Comments %d \n",Comments);
	
	return 0;
	
}
