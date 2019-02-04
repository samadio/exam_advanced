IDIR=../include
CC=g++
CFLAGS=-O0 -ggdb -Wall -Wextra -std=c++11 -I$(IDIR)

ODIR=obj

_DEPS = BST.h
# $(patsubst pattern,replacement,text)
# here pattern=%, which acts as a wildcard
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o BST.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cc $(DEPS) BST.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: %.hpp $(DEPS)
	$(CC) -c -x c++ -o $@ $< $(CFLAGS)

main.x: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
