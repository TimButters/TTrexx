CXX=g++
CXXFLAGS=-std=c++11 -O3

rtree: RTree/*.h example/RTree/main.cc
	$(CXX) $(CXXFLAGS) -I./RTree example/RTree/main.cc -o rtree
