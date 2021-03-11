flags = -Werror -Wall -Wextra -Wpedantic
all: main

main: obj/ obj/bmp.o obj/main.o
	gcc obj/bmp.o obj/main.o -o main
obj/bmp.o:
	gcc -c $(flags) src/bmp.c -o obj/bmp.o -I include/
obj/main.o:
	gcc -c $(flags) src/main.c -o obj/main.o -I include/
obj/:
	mkdir obj
clean:
	rm obj/*.o hw_01 -rf obj/
