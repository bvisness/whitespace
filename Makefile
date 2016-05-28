
whitespace: whitespace.tab.c whitespace.yy.c parsetree.h parsetree.c stack.h stack.c heap.h heap.c
	gcc -o whitespace whitespace.tab.c whitespace.yy.c parsetree.c stack.c heap.c -g

whitespace.tab.c: whitespace.y
	bison -v -d whitespace.y

whitespace.yy.c: whitespace.l
	flex -owhitespace.yy.c whitespace.l

stacktest:
	gcc -o stacktest.exe tests\stacktest.c stack.c

linkedlisttest:
	gcc -o linkedlisttest tests\linkedlisttest.c linkedlist.c
