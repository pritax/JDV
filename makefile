SHELL = /bin/sh

CC=clang
Compil=-g -O0 -Wall
Lib=`sdl-config --cflags --libs` -lSDL_image -lSDL_ttf

EXEC=executable
OBJDIR = obj
SRCDIR = src

Objets = obj/ajout_animaux.o obj/animal.o obj/constantes.o obj/deplacement.o obj/design.o obj/init.o obj/main.o obj/map.o obj/peche.o obj/predation.o obj/reproduction.o obj/satiete.o

all:$(EXEC)

$(EXEC):$(Objets)
				-$(CC) $(Objets) -o $(EXEC) $(Lib)
				@echo "Executable crée !"
				@./lancer_jeu.sh

$(OBJDIR)/%.o:$(SRCDIR)/%.c
				-$(CC) -o $@ -c $^ $(Compil)
				@echo "Compilation de "$^" reussie !"

do:
	./do.sh
clean:
	srm -Rvf obj
	@echo "obj et .o supprimés !"
	mkdir obj
	@echo "obj recrée !"
run:
	make clean && make && ./$(EXEC)
debug:
	make clean && make && gdb ./$(EXEC)
debugmm:
	make clean && make && valgrind ./$(EXEC)
