all:
	g++ src/main.c -o binaries/tetris -lglut -lGL -lGLU
	./binaries/tetris