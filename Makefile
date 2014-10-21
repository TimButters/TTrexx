CXX=g++
CXXFLAGS=-std=c++11 -O3

tree: src/*.h main.cc
	$(CXX) $(CXXFLAGS) main.cc -o tree
