CXXFLAGS ?= -std=c++17 -O2

all: lexer

lexer: main.cc lexer.hh
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -o lexer main.cc

clean:
	$(RM) lexer
