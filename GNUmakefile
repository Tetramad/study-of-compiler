EXE = lexer
SRC = ${wildcard *.cc}
OBJ = ${SRC:.cc=.o}

CXXFLAGS ?= -std=c++17 -O2

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o $(EXE) $(OBJ)

clean:
	$(RM) $(OBJ) $(EXE)
