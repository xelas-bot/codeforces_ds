CXX = g++-11
INC_DIR = ../include/catch2 ../include/fmt

CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic -g
CXXFLAGS+=  $(addprefix -I, $(INC_DIR))

# TODO: could replace with -L to auto find the files in the lib directory
# TODO: the clangd server relies on the compile_commands.json file, which is generated via a bear call (not cmake)
# bear -- make trees test
# perhapsibily write a script that encapsualtes the bear call and the make call
LDFLAGS = ../lib/libCatch2Main.a ../lib/libCatch2.a

TARGETS = base_tree.cpp
MY_INCS = base_av_tree.hpp utils.hpp

TARGETS_TEST = tests/test.cpp


trees: 
	mkdir -p target
	$(CXX) $(CXXFLAGS) $(TARGETS) $(MY_INCS) -o target/rbtree

test:
	g++ -I../include tests/test.cpp $(LDFLAGS) -o target/test

trees_test:
	make trees
	make test
