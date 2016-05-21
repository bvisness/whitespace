
whitespace: whitespace.tab.c whitespace.yy.c
	gcc -o whitespace.exe whitespace.tab.c whitespace.yy.c -g

whitespace.tab.c: whitespace.y
	bison -v -d whitespace.y

whitespace.yy.c: whitespace.l
	flex -owhitespace.yy.c whitespace.l
