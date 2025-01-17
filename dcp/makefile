CXX = g++-11
INC_DIR = ../include/catch2 ../include/fmt ../include/nanobench

CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic -g
CXXFLAGS+=  $(addprefix -I, $(INC_DIR))

# TODO: could replace with -L to auto find the files in the lib directory
# TODO: the clangd server relies on the compile_commands.json file, which is generated via a bear call (not cmake)
# bear -- make trees test
# perhapsibily write a script that encapsualtes the bear call and the make call
LDFLAGS = ../lib/libCatch2Main.a ../lib/libCatch2.a
OBJECTS = ../lib/nanobench.o

TARGETS = dcp_1711.cpp
MY_INCS = ""
TARGETS_TEST = ""


dcp: 
	mkdir -p target
	$(CXX) $(CXXFLAGS) -I./ $(TARGETS)  -o target/dcp
