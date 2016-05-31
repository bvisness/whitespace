
whitespace: whitespace.tab.c whitespace.yy.c parsetree.h parsetree.c stack.h stack.c heap.h heap.c linkedlist.h linkedlist.c
	gcc -o whitespace whitespace.tab.c whitespace.yy.c parsetree.c stack.c heap.c linkedlist.c -g

whitespace.tab.c: whitespace.y
	bison -v -d whitespace.y

whitespace.yy.c: whitespace.l
	flex -owhitespace.yy.c whitespace.l

stacktest: stack.h stack.c tests/stacktest.c
	gcc -o stacktest tests/stacktest.c stack.c linkedlist.c -g

heaptest: heap.h heap.c tests/heaptest.c
	gcc -o heaptest tests/heaptest.c heap.c linkedlist.c -g

linkedlisttest: linkedlist.h linkedlist.c tests/linkedlisttest.c
	gcc -o linkedlisttest tests/linkedlisttest.c linkedlist.c -g
