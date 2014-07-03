CXX=g++-4.9
CXXFLAGS=-std=c++11 -O3

tree: src/*.h main.cc
	$(CXX) $(CXXFLAGS) main.cc -o tree
