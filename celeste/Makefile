CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iraylib/src -D_DEFAULT_SOURCE
LDFLAGS  = -Lraylib/src -lraylib -lm -ldl -lpthread -lrt -lX11

SRC_DIR  = .
OBJ_DIR  = obj
RAYLIB_DIR = raylib

SRC      = src/main.cpp \
		   src/animation.cpp \
           src/player.cpp \
		   src/map.cpp \
		   src/handle.cpp \
		   src/camera.cpp

OBJ      = $(SRC:%.cpp=$(OBJ_DIR)/%.o)

TARGET   = Celeste

all: raylib $(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	@echo "🔨 Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(TARGET): $(OBJ)
	@echo "🎮 Linking $(TARGET)..."
	@$(CXX) $(OBJ) -o $(TARGET) raylib/src/libraylib.a -lm -ldl -lpthread -lrt -lX11
	@echo "✅ Build complete!"

raylib:
	@if [ ! -d "$(RAYLIB_DIR)" ]; then \
		echo "📦 Cloning Raylib..."; \
		git clone --depth 1 https://github.com/raysan5/raylib.git $(RAYLIB_DIR) > /dev/null 2>&1; \
	fi
	@if [ ! -f "$(RAYLIB_DIR)/src/libraylib.a" ]; then \
		echo "🔨 Building Raylib (silent mode)..."; \
		$(MAKE) -C $(RAYLIB_DIR)/src PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=STATIC RAYLIB_RELEASE_FLAG=-DSUPPORT_LOG_LEVEL=LOG_NONE -s > /dev/null 2>&1; \
		echo "✅ Raylib built successfully!"; \
	else \
		echo "✅ Raylib already built"; \
	fi

clean:
	@echo "🧹 Cleaning build files..."
	@rm -rf $(OBJ_DIR)
	@rm -f $(TARGET)

fclean: clean
	@echo "🧹 Removing Raylib..."
	@rm -rf $(RAYLIB_DIR)

re: clean all

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