CXX = g++
CXXFLAGS = -O0 -ggdb -Wall -Wextra -std=c++11 -I$(IDIR)
D_FLAG = BENCHMARK
EXE = test.x 
BENCHMARK = benchmark.x

IDIR = ../include
ODIR = obj

# $(patsubst pattern,replacement,text)
# here pattern=%, which acts as a wildcard
_DEPS = BST.h															
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))		

_OBJ = BST.o test.o benchmark.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


all: $(EXE)

benchmark: $(BENCHMARK)

$(EXE): D_FLAG = VERBOSE

$(ODIR)/%.o: %.cc $(DEPS) 
	$(CXX) -c -o $@ $< $(CXXFLAGS) -D$(D_FLAG)

$(ODIR)/%.o: %.hpp $(DEPS)
	$(CXX) -c -x c++ -o $@ $< $(CXXFLAGS) -D$(D_FLAG)

$(EXE): $(ODIR)/BST.o $(ODIR)/test.o 
	$(CXX) -o $@ $^ $(CXXFLAGS)

$(BENCHMARK): $(ODIR)/BST.o $(ODIR)/benchmark.o
	$(CXX) -o $@ $^ $(CXXFLAGS)


clean:
	rm -f $(ODIR)/*.o *.x *~


.PHONY: clean all benchmark

benchmark.o: BST.h
test.o: BST.h
BST.o: BST.h
