
all:
	gcc -o r_char r_char.c
	gcc -o w_char w_char.c
clean:
	rm -rf r_char w_char *.o *.so *.a
lib:
	gcc -c r_char.c -o r_char.o
	ar rcs r_char.a r_char.o
	gcc -shared -fPIC -o libw_char.so w_char.c
