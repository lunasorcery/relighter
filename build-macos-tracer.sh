echo "building tracer"
BIN_DIR=bin/macos
mkdir -p $BIN_DIR
clang \
	src/tracer/*.cpp \
	src/io/*.cpp \
	src/core/*.cpp \
	src/math/*.cpp \
	-o $BIN_DIR/tracer \
	-Wall \
	-Isrc/ \
	-std=c++11 \
	-lstdc++ \
	-O3 \
	;
