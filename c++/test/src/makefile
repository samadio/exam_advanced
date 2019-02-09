CXX = g++
CXXFLAGS = -O0 -ggdb -Wall -Wextra -std=c++11 -I$(IDIR)
EXE = test.x 

IDIR = ../include
ODIR = obj

_DEPS = BST.h															# $(patsubst pattern,replacement,text)
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))		# here pattern=%, which acts as a wildcard

_OBJ = test.o BST.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


all: $(EXE)

$(ODIR)/%.o: %.cc $(DEPS) 
	$(CXX) -c -o $@ $< $(CXXFLAGS)

$(ODIR)/%.o: %.hpp $(DEPS)
	$(CXX) -c -x c++ -o $@ $< $(CXXFLAGS)

$(EXE): $(OBJ) 
	$(CXX) -o $@ $^ $(CXXFLAGS)


clean:
	rm -f $(ODIR)/*.o *.x *~


.PHONY: clean all

test.o: BST.h
BST.o: BST.h
