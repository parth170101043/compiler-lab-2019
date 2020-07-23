part2:
		bison -d part2.y
		lex part2.l
		gcc part2.tab.c lex.yy.c -lfl -o codes
		./codes
		
clean:	part2 part2.tab.c part2.tab.h lex.yy.c
		rm part2 part2.tab.c part2.tab.h lex.yy.c