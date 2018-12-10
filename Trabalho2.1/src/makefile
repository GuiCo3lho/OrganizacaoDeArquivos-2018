CC=gcc
CFLAGS = -Wall -I $(IDIR)

ODIR = ./obj
IDIR = ../include
SDIR = .

_DEPS = trabalho2.h
DEPS = $(patsubst %, $(IDIR)/%, $(_DEPS))
_OBJ = trabalho2.o t2funcoes.o btree.o
OBJ = $(patsubst %, $(ODIR)/%, $(_OBJ))

../trabalho2: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core
