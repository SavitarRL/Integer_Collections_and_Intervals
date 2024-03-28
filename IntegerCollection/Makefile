CXX?=/usr/bin/g++

.PHONY: test

test: main_collection
	./main_collection

main_collection: main_collection.cxx tests.cxx collection.cxx test.h
	$(CXX) -std=c++14 -I. -o $@ $<