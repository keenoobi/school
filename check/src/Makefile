CC = gcc
CFLAGS = -Wall -Werror -Wextra
BUILD = ../build/

all: graph

graph: display.o evaluation.o infix_to_postfix.o verifications.o graph.o
	$(CC) $(CFLAGS) display.o evaluation.o infix_to_postfix.o verifications.o graph.o -o $(BUILD)graph

evaluation.o: evaluation.c
	$(CC) $(CFLAGS) evaluation.c -c 

infix_to_postfix.o: infix_to_postfix.c
	$(CC) $(CFLAGS) infix_to_postfix.c -c 

display.o: display.c
	$(CC) $(CFLAGS) display.c -c 

verifications.o: verifications.c
	$(CC) $(CFLAGS) verifications.c -c 

graph.o: graph.c
	$(CC) $(CFLAGS) graph.c -c 

clean:
	rm -rf *.o $(BUILD)graph

rebuild:
	make clean && make