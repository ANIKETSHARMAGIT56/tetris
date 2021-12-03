all:    #target name
	g++ main.c -o tetris -lglut -lGL -lGLU
	./tetris