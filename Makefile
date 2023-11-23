.default: all

all: qwirkle

clean:
	rm -rf qwirkle *.o *.dSYM

qwirkle: Game.o Board.o Node.o Player.o Tile.o Node.o LinkedList.o qwirkle.o PlayerHand.o Menu.o TileBag.o 
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
