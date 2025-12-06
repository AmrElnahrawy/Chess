directories:
	mkdir -p obj
	mkdir -p bin

main.o: directories
	gcc -c src/main.c       -o obj/main.o
Menus.o: directories	
	gcc -c src/Menus.c      -o obj/Menus.o
GameState.o: directories	
	gcc -c src/GameState.c  -o obj/GameState.o
Pieces.o: directories	
	gcc -c src/Pieces.c     -o obj/Pieces.o
SaveLoad.o:	directories
	gcc -c src/SaveLoad.c   -o obj/SaveLoad.o
Utilities.o:
	gcc -c src/Utilities.c   -o obj/Utilities.o

main: main.o Menus.o GameState.o Pieces.o SaveLoad.o Utilities.o
	gcc obj/*.o -o bin/main

clean:
	rm -rf obj bin

run: main
	bin/main