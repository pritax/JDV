SHELL = /bin/sh

CC=gcc
Compil=-g -O0 -Wall
Lib=`sdl-config --cflags --libs` -lSDL_image -lSDL_ttf

EXEC=executable
Objets=obj/main.o obj/init.o obj/design.o obj/constantes.o obj/peche.o obj/conf.o obj/predation.o obj/satiete.o obj/reproduction.o obj/map.o obj/animal.o obj/ajout_animaux.o obj/deplacement.o

OBJDIR = obj
SRCDIR = src

all:$(EXEC)

$(EXEC):$(Objets)
	-$(CC) $(Objets) -o $(EXEC) $(Lib)
	@echo "Executable crée : tapez ./executable pour lancer le jeu !"

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	-$(CC) -o $@ -c $^ $(Compil)
	@echo "Compilation de "$^" reussie !"

clean:
	rm -rvf obj/*.o
	@echo ".o supprimés !"
run:
	make clean && make && ./$(EXEC)
debug:
	make clean && make && gdb ./$(EXEC)

