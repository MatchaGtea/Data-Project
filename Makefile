CXX      = g++
CXXFLAGS = -Wall -std=c++17 -Isrc
SRC = $(wildcard src/*.cpp src/data_structures/*.cpp)

ifeq ($(OS),Windows_NT)
	ifneq ($(wildcard tools/w64devkit/bin/g++.exe),)
		export PATH := $(CURDIR)/tools/w64devkit/bin;$(PATH)
		CXX = g++
		OUT = build/program.exe
		MKDIR = mkdir -p build
		COPY_RUNTIME = cp -r assets data build/
		RM = rm -f $(OUT)
		RUN = ./$(OUT)
	else
		OUT = build\program.exe
		MKDIR = if not exist build mkdir build
		COPY_RUNTIME = xcopy assets build\assets /E /I /Y >NUL && xcopy data build\data /E /I /Y >NUL
		RM = if exist $(OUT) del /Q $(OUT)
		RUN = .\$(OUT)
	endif
	RAYLIB_DIR = tools/raylib-6.0_win64_mingw-w64
	ifneq ($(wildcard $(RAYLIB_DIR)/include/raylib.h),)
		RAYLIB_CFLAGS = -I "$(RAYLIB_DIR)/include"
		RAYLIB_LIBS = -L "$(RAYLIB_DIR)/lib" -lraylib -lopengl32 -lgdi32 -lwinmm
	else
		RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib 2>NUL)
		RAYLIB_LIBS   := $(shell pkg-config --libs raylib 2>NUL)
		ifeq ($(strip $(RAYLIB_LIBS)),)
			RAYLIB_LIBS = -lraylib -lopengl32 -lgdi32 -lwinmm
		endif
	endif
else
	RAYLIB_CFLAGS := $(shell pkg-config --cflags raylib 2>/dev/null)
	RAYLIB_LIBS   := $(shell pkg-config --libs raylib 2>/dev/null)
	OUT = build/program
	MKDIR = mkdir -p build
	COPY_RUNTIME =
	RM = rm -f $(OUT)
	RUN = ./$(OUT)

	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Darwin)
		RAYLIB_LIBS += -framework OpenGL -framework Cocoa -framework IOKit -framework CoreVideo
	endif
	ifeq ($(strip $(RAYLIB_LIBS)),)
		RAYLIB_LIBS = -lraylib
	endif
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
	$(MKDIR)
	$(CXX) $(CXXFLAGS) $(RAYLIB_CFLAGS) -o $(OUT) $(SRC) $(RAYLIB_LIBS)
	$(COPY_RUNTIME)

clean:
	$(RM)

run: all
	$(RUN)

install-raylib:
ifndef MINGW_PACKAGE_PREFIX
	$(error Run this target from the MSYS2 UCRT64, MINGW64, or CLANG64 terminal)
endif
	pacman -S --needed base-devel $(MINGW_PACKAGE_PREFIX)-gcc $(MINGW_PACKAGE_PREFIX)-raylib $(MINGW_PACKAGE_PREFIX)-pkgconf
