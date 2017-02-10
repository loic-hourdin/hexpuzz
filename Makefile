TARGET_JEU   = hextris.exe
TARGET_TEST  = testunitaire.exe

CC       = gcc
CFLAGS   = -Wall -Wextra -ansi -I. -std=c99 -g
LINKER   = gcc -o
LFLAGS   = -lSDL -lSDL_mixer -lSDL_ttf -lSDL_image
SRCDIR   = src
OBJDIR   = build
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.c)
SOURCES_JEU  := $(filter-out $(SRCDIR)/testunitaire.c , $(SOURCES))
SOURCES_TEST  := $(filter-out $(SRCDIR)/main.c , $(SOURCES))
INCLUDES := $(wildcard $(SRCDIR)/*.h)
OBJECTS :=  $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTS_JEU  := $(SOURCES_JEU:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
OBJECTS_TEST  := $(SOURCES_TEST:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
rm       = rm -f
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir := $(notdir $(patsubst %/,%,$(dir $(mkfile_path))))

all: $(BINDIR)/$(TARGET_JEU) $(BINDIR)/$(TARGET_TEST) 

$(BINDIR)/$(TARGET_JEU): $(OBJECTS_JEU)
	@$(LINKER) $@ $(OBJECTS_JEU) $(LFLAGS)
	@echo "Linking complete! (jeu)"

$(BINDIR)/$(TARGET_TEST): $(OBJECTS_TEST)
	@$(LINKER) $@ $(OBJECTS_TEST) $(LFLAGS)
	@echo "Linking complete! (test unitaire)"


mac:
	gcc -o sdlApp.app *.c SDLMain.m -framework SDL -framework SDL_ttf -framework SDL_image -framework SDL_mixer -framework Cocoa -I /opt/SDL -g

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET_TEST)
	@$(rm) $(BINDIR)/$(TARGET_JEU)
	@echo "Executable removed!"

.PHONEY: uninstall
uninstall: remove
	@echo "Game 'Hextris' has been uninstalled"
	@rm -rf ../$(current_dir)
