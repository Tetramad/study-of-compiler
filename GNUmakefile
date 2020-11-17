EXE = lexer
SRC = lexer.cc
OBJ = ${SRC:.cc=.o}

CXXFLAGS ?= -std=c++17

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(EXE) $(OBJ)

clean:
	$(RM) $(OBJ) $(EXE)
