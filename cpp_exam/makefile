CXX = c++
CXXFLAGS = -Wall -Wextra -g -std=c++14

SRC = trials/trials.cc \
      benchmarks/benchmark.cc

#prova.cc -> prova.x
EXE = $(SRC:.cc=.x)

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cc .x

all: $(EXE)

.PHONY: all

documentation: Doxygen/doxy.in
	doxygen $^

.PHONY: documentation

%.x: %.cc 
	$(CXX) $< -o $@ $(CXXFLAGS)

.PHONY: format

clean:
	rm -f $(EXE) *~

.PHONY: clean
