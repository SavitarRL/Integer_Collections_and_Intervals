CXX?=/usr/bin/g++

.PHONY: test

test: main_intervals
	./main_intervals

main_intervals: main_intervals.cxx intervals.cxx tests.cxx test.h 
	$(CXX) -std=c++14 -I. -o $@ $<