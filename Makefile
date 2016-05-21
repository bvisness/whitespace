
whitespace: whitespace.tab.c whitespace.yy.c parsetree.h parsetree.c
	gcc -o whitespace.exe whitespace.tab.c whitespace.yy.c parsetree.c -g

whitespace.tab.c: whitespace.y
	bison -v -d whitespace.y

whitespace.yy.c: whitespace.l
	flex -owhitespace.yy.c whitespace.l
