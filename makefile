all: build clear


build:
	gcc -c *.c
	gcc -o run *.o 
	
clear:
	rm *.o

run:
	./run

push:
	git add --all
	git commit -ms
	git push --all