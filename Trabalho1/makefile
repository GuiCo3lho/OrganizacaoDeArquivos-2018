CC=gcc
CFLAGS = -I.

trabalho: trabalho.o tfuncoes.o
	$(CC) -g -o trabalho trabalho.o tfuncoes.o $(CFLAGS)

trabalho.o: trabalho.c
	$(CC) -g -c trabalho.c $(CFLAGS)

tfuncoes.o: tfuncoes.c
	$(CC) -g -c tfuncoes.c $(CFLAGS)

.PHONY: clean
clean:
	rm -r *.o
	rm trabalho