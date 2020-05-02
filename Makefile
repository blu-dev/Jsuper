# JAVA_HOME is set to C:\Java\jdk-14.0.1 for me and MINGW64_HOME is set to C:\MinGW\mingw64 for me
# Also, I'm doing this in Makefile because my IDE's aren't very fond of doing native C++ implementation (understandably)
# NATIVE
PLATFORM := win

_NATIVE_DIR := ./src/native
_SRC_DIRS := $(_NATIVE_DIR)/src/$(PLATFORM) $(_NATIVE_DIR)/src/$(PLATFORM)/jimpl
SRC_FILES := $(foreach dir, $(_SRC_DIRS), $(wildcard $(dir)/*.cpp))

_LOCAL_INC_DIRS := $(_NATIVE_DIR)/inc
_GLOBAL_INC_DIRS := ${JAVA_HOME}/include ${JAVA_HOME}/include/win32 ${MINGW64_HOME}/include
INC_DIRS := $(foreach dir, $(_LOCAL_INC_DIRS), -I$(dir)) $(foreach dir, $(_GLOBAL_INC_DIRS), -I$(dir))

TARGET_NAME := native
TARGET_EXTENSION := dll
TARGET_DIRECTORY := ./out/native

CC := g++
ARGS := -shared

#JAVA
_JAVA_SRC_DIRS := ./src/Jsuper ./src/Jsuper/utils ./src/Jsuper/utils/actions
JAVA_SRC_FILES := $(foreach dir, $(_JAVA_SRC_DIRS), $(wildcard $(dir)/*.java))

JAVA_OUT_DIR :=  ./out/Jsuper
_JAVA_CLS_DIRS := $(JAVA_OUT_DIR) $(JAVA_OUT_DIR)/jsuper $(JAVA_OUT_DIR)/jsuper/utils $(JAVA_OUT_DIR)/jsuper/utils/actions
_JAVA_CLS_FILES := $(foreach dir, $(_JAVA_CLS_DIRS), $(wildcard $(dir)/*.class))
JAVA_CLS_FILES := $(patsubst $(JAVA_OUT_DIR)%, .%, $(_JAVA_CLS_FILES))

JAR_DIR := bin
JAR_NAME := Jsuper

JAVAC_ARGS := -h $(_NATIVE_DIR)/inc

all:
	make Jsuper
	make native

native:
	@if not exist $(subst /,\, $(TARGET_DIRECTORY)) mkdir $(subst /,\, $(TARGET_DIRECTORY))
	$(CC) $(ARGS) $(INC_DIRS) $(SRC_FILES) -o $(TARGET_DIRECTORY)/$(TARGET_NAME).$(TARGET_EXTENSION)

Jsuper:
	javac  $(JAVA_SRC_FILES) -d $(JAVA_OUT_DIR) $(JAVAC_ARGS)

clean:
	clean

jar: 
	@if not exist .\\bin mkdir .\\bin
	cd $(JAVA_OUT_DIR) && jar cmvf ../../Manifest.mf ../../$(JAR_DIR)/$(JAR_NAME).jar $(JAVA_CLS_FILES) 
	@copy $(subst /,\, $(TARGET_DIRECTORY))\\$(TARGET_NAME).$(TARGET_EXTENSION) $(JAR_DIR)\\$(TARGET_NAME).$(TARGET_EXTENSION)