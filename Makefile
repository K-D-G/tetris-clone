GPP:=g++
GPPPARAMS=-Iinclude -I/usr/local/Cellar/sfml/2.5.1_1/include
OBJECTS:=obj/tetris/utils.o \
				 obj/tetris/piece.o \
				 obj/tetris/game.o


obj/%.o: src/%.cpp
		mkdir -p $(@D)
		$(GPP) $(DEBUG) $(GPPPARAMS) -o $@ -c $<

tetris:$(OBJECTS)
	g++ $(OBJECTS) $(DEBUG) $(GPPPARAMS) -L/usr/local/Cellar/sfml/2.5.1_1/lib src/tetris/main.cpp -o tetris.out -lsfml-graphics -lsfml-window -lsfml-system

run:
	clear
	make clean
	make tetris
	./tetris.out

debug:
	clear
	make clean
	make tetris DEBUG='-g'
	lldb --file tetris.out

.PHONY: clean
clean:
	rm -rf obj tetris
