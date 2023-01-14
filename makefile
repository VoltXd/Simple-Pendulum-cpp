all:
	g++ ./src/*.cpp -o ./bin/simple-pendulum.exe -Wall -I ./include/SDL2 -I ./include/Simple-Pendulum -L ./lib -lmingw32 -lSDL2main -lSDL2 