CC=clang
CFLAGS=-Wall

date_test: date.o date_test.c
	$(CC) $(CFLAGS) date_test.c date.o -o date_test
	./date_test

date.o: date.c date.h
	$(CC) $(CFLAGS) -c date.c -o date.o