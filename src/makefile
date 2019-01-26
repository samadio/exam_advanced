IDIR=../include
CC=g++
CFLAGS=-O0 -ggdb -Wall -Wextra -I$(IDIR)

ODIR=obj

_DEPS = BST.h
# $(patsubst pattern,replacement,text)
# here pattern=%, which acts as a wildcard
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o BST.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.cc $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/%.o: BST.hpp $(DEPS)
	$(CC) -c -x c++ -o $@ $< $(CFLAGS)

main.x: $(OBJ) 
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~
