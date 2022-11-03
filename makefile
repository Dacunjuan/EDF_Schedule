all: main.c rm.h
	cc main.c
test1: main.c rm.h file1
	cc main.c && ./a.out < file1
test2: main.c rm.h file1
	cc main.c && ./a.out < file2
test3: main.c rm.h file3
	cc main.c && ./a.out < file3
test4: main.c rm.h file4
	cc main.c && ./a.out < file4
clean: a.out
	rm a.out