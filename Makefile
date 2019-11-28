all: minix.c 
	gcc -g -Wall -o minix minix.c

  clean: 
	$(RM) minix