all:    #target name
	g++ main.c -o test -lglut -lGL -lGLU
	./test