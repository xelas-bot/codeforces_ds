CXX = g++
INC_DIR = ../include/catch2 ../include/fmt

CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic -g
CXXFLAGS+=  $(addprefix -I, $(INC_DIR))

LDFLAGS = ../lib/libCatch2Main.a ../lib/libCatch2.a

TARGETS = base_tree.cpp
MY_INCS = base_av_tree.hpp utils.hpp

TARGETS_TEST = tests/test.cpp


trees: 
	mkdir -p target
	$(CXX) $(CXXFLAGS) $(TARGETS) $(MY_INCS) -o target/rbtree

test:
	g++ -I../include tests/test.cpp $(LDFLAGS) -o target/test
