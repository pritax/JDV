SHELL = /bin/sh

CC=clang
Compil=-g -O -Wall -D_REENTRANT
Lib=-lpthread


EXEC=executable
Objets=serveur.o envoi.o socket.o threads.o

all:$(EXEC)

$(EXEC):$(Objets)
	@$(CC) $^ -o $@ $(Lib)
	@echo "Linkage de l'executable "$@" reussi !"

%.o : %.c
	@$(CC) -o $@ -c $^ $(Compil)
	@echo "Compilation de "$^" reussie !"
	

clean:
	rm -rvf $(EXEC) *.o
	@echo "Executable et .o supprimés !"
run:
	make clean && make && ./$(EXEC)
debug:
	make clean && make && gdb ./$(EXEC)
memDebug:
	make clean && make && valgrind ./$(EXEC)

