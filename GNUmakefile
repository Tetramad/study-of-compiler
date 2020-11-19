CXXFLAGS ?= -std=c++17 -O2

all: lexer parser

lexer: lexer.o spl_automata.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o lexer lexer.o spl_automata.o

lexer.o: lexer.cc lexer.hh spl_automata.hh
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o lexer.o lexer.cc

spl_automata.o: spl_automata.cc spl_automata.hh
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o spl_automata.o spl_automata.cc

parser: lexer parser.o spl_recursive_descent.o
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o parser parser.o spl_automata.o spl_recursive_descent.o

parser.o: parser.cc parser.hh lexer.hh spl_automata.hh
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o parser.o parser.cc

spl_recursive_descent.o: spl_recursive_descent.cc spl_recursive_descent.hh spl_automata.hh
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o spl_recursive_descent.o spl_recursive_descent.cc

clean:
	$(RM) lexer lexer.o spl_automata.o parser parser.o spl_recursive_descent.o
