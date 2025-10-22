# Nom de l'exécutable
TARGET = sdl_test

# Fichiers source
SRC = main.cpp

# Compilateur
CXX = g++

# Options de compilation
CXXFLAGS = -Wall -O2 $(shell sdl2-config --cflags)

# Librairies à l'édition de liens
LDFLAGS = $(shell sdl2-config --libs)

# Règle par défaut
all: $(TARGET)

# Règle de compilation
$(TARGET): $(SRC)
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(LDFLAGS)

# Nettoyage des fichiers objets (même s'il n'y en a pas ici)
clean:
	@echo "Nothing to clean"

# Nettoyage complet
fclean:
	rm -f $(TARGET)

# Recompilation complète
re: fclean all

.PHONY: all clean fclean re