CXX      = gcc
CXXFLAGS = -Wall
EXE      = tetris
OBJS     = tetris.o game.o screen.o

$(EXE): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@ -lncurses
%.o: %.c
	$(CXX) -c $^

clean:
	$(RM) $(OBJS) $(EXE) *~ 
