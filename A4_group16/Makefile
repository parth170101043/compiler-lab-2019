main:	mainLex.l mainBison.y list.c operations.c
		bison -d mainBison.y
		flex mainLex.l
		gcc -o $@ mainBison.tab.c lex.yy.c list.c operations.c -lfl -g
		
clean:	main mainBison.tab.c mainBison.tab.h lex.yy.c
		rm main mainBison.tab.c mainBison.tab.h lex.yy.c