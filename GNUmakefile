CXXFLAGS ?= -std=c++17 -O2

all: lexer

lexer: lexer.o spl_automata.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o lexer lexer.o spl_automata.o

lexer.o: lexer.cc lexer.hh spl_automata.hh
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o lexer.o lexer.cc

spl_automata.o: spl_automata.cc spl_automata.hh
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o spl_automata.o spl_automata.cc

clean:
	$(RM) lexer lexer.o spl_automata.o
