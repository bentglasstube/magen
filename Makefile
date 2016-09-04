SOURCES=$(wildcard *.cc) $(wildcard framework/*.cc)
OBJECTS=$(SOURCES:.cc=.o)
DEPS=$(SOURCES:.cc=.d)
BIN=magen

CXXFLAGS=-O2 --std=c++11 -Wall -Wextra -Werror -pedantic `sdl2-config --cflags`
LDFLAGS=-static-libstdc++ -static-libgcc
LDLIBS=`sdl2-config --libs` -lSDL2_mixer -lpthread

all: $(BIN)

$(BIN): $(OBJECTS)
	$(CXX) $(LDFLAGS) -o $@ $(OBJECTS) $(LDLIBS)

run: $(BIN)
	./$(BIN)

clean:
	$(RM) $(OBJECTS) $(DEPS) $(BIN)

.PHONY: all clean run

-include $(DEPS)
