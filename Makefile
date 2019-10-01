build: 2048

2048: 2048.c
	gcc 2048.c -o 2048 -lmenu -lncurses
run: 
	./2048
clean: 
	rm 2048
