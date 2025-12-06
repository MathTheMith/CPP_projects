# Configuration
TARGET = Pong
SRC = main.cpp
CXX = g++
CXXFLAGS = -Wall -O2 -std=c++17

# Répertoires
SDL_DIR = SDL2
SDL_BUILD = $(SDL_DIR)/build
SDL_INSTALL = $(SDL_DIR)/install

# Chemins SDL2
SDL_INCLUDE = $(SDL_INSTALL)/include/SDL2
SDL_LIB = $(SDL_INSTALL)/lib

# Flags de compilation avec SDL2 local
INCLUDES = -I$(SDL_INCLUDE)
LDFLAGS = -L$(SDL_LIB) -lSDL2 -Wl,-rpath,$(SDL_LIB)

# Détection de l'OS
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
    LDFLAGS += -ldl -lpthread -lm
endif
ifeq ($(UNAME_S),Darwin)
    LDFLAGS += -framework CoreAudio -framework AudioToolbox -framework CoreFoundation -framework CoreGraphics -framework CoreVideo -framework ForceFeedback -framework IOKit -framework Carbon -framework AppKit -framework Metal
endif

# Règle par défaut
all: sdl $(TARGET)

# Clone et compile SDL2
sdl:
	@if [ ! -d "$(SDL_DIR)" ]; then \
		echo "📦 Cloning SDL2..."; \
		git clone --depth 1 --branch release-2.28.5 https://github.com/libsdl-org/SDL.git $(SDL_DIR); \
	fi
	@if [ ! -f "$(SDL_LIB)/libSDL2.so" ] && [ ! -f "$(SDL_LIB)/libSDL2.dylib" ] && [ ! -f "$(SDL_LIB)/libSDL2.a" ]; then \
		echo "🔨 Building SDL2..."; \
		mkdir -p $(SDL_BUILD) $(SDL_INSTALL); \
		cd $(SDL_BUILD) && \
		cmake .. -DCMAKE_INSTALL_PREFIX=../install -DCMAKE_BUILD_TYPE=Release && \
		make -j$$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4) && \
		make install; \
		echo "✅ SDL2 built successfully!"; \
	else \
		echo "✅ SDL2 already built"; \
	fi

# Compilation du jeu
$(TARGET): $(SRC)
	@echo "🎮 Compiling game..."
	$(CXX) $(SRC) -o $(TARGET) $(CXXFLAGS) $(INCLUDES) $(LDFLAGS)
	@echo "✅ Game compiled successfully!"

# Nettoyage du projet (garde SDL2)
clean:
	rm -f $(TARGET)
	@echo "🧹 Project cleaned"

# Nettoyage complet (supprime SDL2)
fclean: clean
	rm -rf $(SDL_DIR)
	@echo "🧹 Full clean (SDL2 removed)"

# Recompilation
re: clean all

# Aide
help:
	@echo "Makefile pour Pong avec SDL2 embarqué"
	@echo ""
	@echo "Commandes disponibles:"
	@echo "  make          - Clone SDL2, compile SDL2 et compile le jeu"
	@echo "  make sdl      - Clone et compile uniquement SDL2"
	@echo "  make clean    - Nettoie le jeu (garde SDL2)"
	@echo "  make fclean   - Nettoie tout (supprime SDL2)"
	@echo "  make re       - Recompile le jeu"
	@echo "  make help     - Affiche cette aide"

.PHONY: all sdl clean fclean re help