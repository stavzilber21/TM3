CFLAGS = -Wall -g

clean:
	rm -f *.o stringProg

all: stringProg

stringProg: matala3.o
	gcc $(CFLAGS) -o stringProg matala3.o
main.o: matala3.c
	gcc $(CFLAGS) -c matala3.c