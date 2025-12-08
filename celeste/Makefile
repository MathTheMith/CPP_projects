# -----------------------------
# Makefile pour Celeste + Raylib
# -----------------------------

CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iraylib/src -D_DEFAULT_SOURCE
LDFLAGS  = -lm -ldl -lpthread -lrt -lX11

SRC_DIR  = .
OBJ_DIR  = obj
RAYLIB_DIR = raylib
RAYLIB_BUILD_DIR = $(RAYLIB_DIR)/build

SRC      = src/main.cpp \
           src/animation.cpp \
           src/player.cpp \
           src/map.cpp \
           src/handle.cpp \
           src/camera.cpp

OBJ      = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

TARGET   = Celeste

# -----------------------------
# Commande principale
# -----------------------------
all: raylib $(TARGET)

# -----------------------------
# Compilation des objets
# -----------------------------
$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "🔨 Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# -----------------------------
# Linking
# -----------------------------
$(TARGET): $(OBJ)
	@echo "🎮 Linking $(TARGET)..."
	@$(CXX) $(OBJ) -o $(TARGET) -L$(RAYLIB_BUILD_DIR)/src -lraylib $(LDFLAGS)
	@echo "✅ Build complete!"

# -----------------------------
# Cloner et compiler Raylib
# -----------------------------
raylib:
	@if [ ! -d "$(RAYLIB_DIR)" ]; then \
		echo "📦 Cloning Raylib..."; \
		git clone --depth 1 https://github.com/raysan5/raylib.git $(RAYLIB_DIR); \
	fi
	@if [ ! -f "$(RAYLIB_BUILD_DIR)/src/libraylib.a" ]; then \
		echo "🔨 Building Raylib (CMake, static)..."; \
		mkdir -p $(RAYLIB_BUILD_DIR); \
		cd $(RAYLIB_BUILD_DIR); \
		cmake -DBUILD_SHARED_LIBS=OFF -DCMAKE_BUILD_TYPE=Release ..; \
		make; \
		echo "✅ Raylib built successfully!"; \
	else \
		echo "✅ Raylib already built"; \
	fi

# -----------------------------
# Nettoyage
# -----------------------------
clean:
	@echo "🧹 Cleaning build files..."
	@rm -rf $(OBJ_DIR)
	@rm -f $(TARGET)

fclean: clean
	@echo "🧹 Removing Raylib..."
	@rm -rf $(RAYLIB_DIR)

re: fclean all

help:
	@echo "Makefile for Celeste with embedded Raylib (C++)"
	@echo ""
	@echo "Available commands:"
	@echo "  make          - Build Raylib (if needed) and compile the game"
	@echo "  make clean    - Remove build files (keeps Raylib)"
	@echo "  make fclean   - Remove everything including Raylib"
	@echo "  make re       - Full rebuild"
	@echo "  make help     - Show this help"

.PHONY: all clean fclean re raylib help
