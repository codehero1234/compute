mat:
	gcc -g -Wall -o mat mat.c error.c

mat_test:
	gcc -g -Wall -o mat_test mat_test.c error.c mat.c

clean:
	rm -rf mat
	rm -rf mat_test