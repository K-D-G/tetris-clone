GPP:=g++
GPPPARAMS:=-Iinclude -I/usr/local/Cellar/sfml/2.5.1_1/include
OBJECTS:=obj/tetris/utils.o

obj/%.o: src/%.cpp
		mkdir -p $(@D)
		$(GPP) $(GPPPARAMS) -o $@ -c $<

tetris:$(OBJECTS)
	g++ $(OBJECTS) $(GPPPARAMS) -L/usr/local/Cellar/sfml/2.5.1_1/lib src/tetris/main.cpp -o tetris -lsfml-graphics -lsfml-window -lsfml-system

run:
	clear
	make clean
	make tetris
	./tetris

.PHONY: clean
clean:
	rm -rf obj tetris
