# NATIVE
_NATIVE_DIR := ./src/native
_SRC_DIRS := $(_NATIVE_DIR)/src
SRC_FILES := $(foreach dir, $(_SRC_DIRS), $(wildcard $(dir)/*.cpp))

_LOCAL_INC_DIRS := $(_NATIVE_DIR)/inc
_GLOBAL_INC_DIRS := ${JAVA_HOME}/include ${JAVA_HOME}/include/win32 ${MINGW64_HOME}/include
INC_DIRS := $(foreach dir, $(_LOCAL_INC_DIRS), -I$(dir)) $(foreach dir, $(_GLOBAL_INC_DIRS), -I$(dir))

TARGET_NAME := native
TARGET_EXTENSION := dll
TARGET_DIRECTORY := $(_NATIVE_DIR)/out

CC := g++
ARGS := -shared

#JAVA
_JAVA_SRC_DIRS := ./src/Ssuper ./src/Ssuper/test
JAVA_SRC_FILES := $(foreach dir, $(_JAVA_SRC_DIRS), $(wildcard $(dir)/*.java))

JAVA_OUT_DIR :=  ./out

JAVAC_ARGS := -h $(_NATIVE_DIR)/inc

all:
	make Ssuper
	make native

native:
	$(CC) $(ARGS) $(INC_DIRS) $(SRC_FILES) -o $(TARGET_DIRECTORY)/$(TARGET_NAME).$(TARGET_EXTENSION)

Ssuper:
	javac  $(JAVA_SRC_FILES) -d $(JAVA_OUT_DIR) $(JAVAC_ARGS)