echo "building lighter"
BIN_DIR=bin/macos
mkdir -p $BIN_DIR
clang \
	src/lighter/*.cpp \
	src/io/*.cpp \
	src/core/*.cpp \
	src/math/*.cpp \
	-o $BIN_DIR/lighter \
	-Wall \
	-Isrc/ \
	-std=c++11 \
	-lstdc++ \
	-O3 \
	;
