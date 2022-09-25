all: build clear


build:
	gcc -c *.c -g
	gcc -o run *.o 
	
clear:
	rm *.o

check:
	valgrind --leak-check=full ./run

run:
	./run

push:
	git add --all
	git commit -ms
	git push --all

