CXX      = g++
CXXFLAGS = -Wall -std=c++17 -Isrc
RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib 2>/dev/null)
RAYLIB_LIBS   := $(shell pkg-config --libs raylib 2>/dev/null)

ifeq ($(strip $(RAYLIB_LIBS)),)
	RAYLIB_LIBS = -lraylib
endif

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	RAYLIB_LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
endif

SRC = $(wildcard src/*.cpp src/data_structures/*.cpp)

ifeq ($(OS),Windows_NT)
	OUT = build/program.exe
else
	OUT = build/program
endif

ifeq ($(MSYSTEM),UCRT64)
	MINGW_PACKAGE_PREFIX = mingw-w64-ucrt-x86_64
else ifeq ($(MSYSTEM),MINGW64)
	MINGW_PACKAGE_PREFIX = mingw-w64-x86_64
else ifeq ($(MSYSTEM),CLANG64)
	MINGW_PACKAGE_PREFIX = mingw-w64-clang-x86_64
endif

.PHONY: all clean run install-raylib

all: $(OUT)

$(OUT): $(SRC)
	mkdir -p build
	$(CXX) $(CXXFLAGS) $(RAYLIB_CFLAGS) -o $(OUT) $(SRC) $(RAYLIB_LIBS)

clean:
	rm -f $(OUT)

run: all
	$(OUT)

install-raylib:
ifndef MINGW_PACKAGE_PREFIX
	$(error Run this target from the MSYS2 UCRT64, MINGW64, or CLANG64 terminal)
endif
	pacman -S --needed base-devel $(MINGW_PACKAGE_PREFIX)-gcc $(MINGW_PACKAGE_PREFIX)-raylib $(MINGW_PACKAGE_PREFIX)-pkgconf
