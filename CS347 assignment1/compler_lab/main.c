#include "lex.h"
#include<stdio.h>
#include<ctype.h>
#include "lex.c"


int main ()
{
	//statements ();
	int aa;
	

	while(1)
	{	
		aa=lex();
		if(aa==0)
			break;
		else if(aa==-1)
			printf("None\n");
	
		else if(aa==1)
			printf("< seperator, ; >  ");
		else if(aa==2)
			printf("< operator, + >  ");
		else if(aa==3)
			printf("< operator, * >  ");
		else if(aa==4)
			printf("< seperator, ( >  ");
		else if(aa==5)
			printf("< seperator, ) >  ");
		else if(aa==6)
			printf("< literal >  ");
		else if(aa==7)
			printf("< keyword,char)  ,");
		else if(aa==8)
			printf("< operator, = >  ");
		else if(aa==9)
			printf("< keyword, else >  ");
		else if(aa==10)
			printf("< keyword, float >  ");
		else if(aa==11)
			printf("< keyword, if >  ");
		else if(aa==12)
			printf("< keyword, int >  ");
		else if(aa==13)
			printf("< keyword, while >  ");
		else if(aa==14)
			printf("< identifier >  ");
		else if(aa==15)
			printf("< keyword, do >  ");
		else if(aa==16)
			printf("< keyword, then >  ");
		else if(aa==17)
			printf("< operator, - >  ");
		else if(aa==18)
			printf("< operator, / >  ");
		else if(aa==19)
			printf("< LE, >= >  ");
		else if(aa==20)
			printf("< LT, < >  ");
		else if(aa==21)
			printf("< EQL, == >  ");
		else if(aa==22)
			printf("< NOT_EQL, != >  ");
		else if(aa==23)
			printf("< operator, >= >  ");
		else if(aa==24)
			printf("< operator, > >  ");
		else if(aa==25)
			printf("< seperator, { >  ");
		else if(aa==26)
			printf("< seperator, } >  ");



	}
	printf("]\n");
}
