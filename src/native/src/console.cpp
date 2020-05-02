#include "jsuper_utils_Console.h"
#include "console.hpp"
#include "private/pconsole.hpp"

#include <iostream>


// Global console for us to interact with (will be implemented differently in the future)
Console* console;

JNIEXPORT void JNICALL Java_jsuper_utils_Console_test(JNIEnv* env, jobject obj) {
	HANDLE newOutput = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE ,  FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(newOutput);
}

// Instantiates the console, let's constructor handle the rest
JNIEXPORT jobject JNICALL Java_jsuper_utils_Console_init(JNIEnv* env, jobject obj) {
	console = new Console();
	std::cout << "the" << std::endl;
	jclass clazz = env->FindClass("java/io/PrintStream");
	std::cout << "help" << std::endl;
	jmethodID constructorID = env->GetMethodID(clazz, "<init>", "(Ljava/lang/String;)V");
	std::cout << "bruh" << std::endl;
	jobject instant = env->NewObject(clazz, constructorID, env->NewStringUTF("CONOUT$"));
	std::cout << "4" << std::endl;
	return instant;
}

JNIEXPORT void JNICALL Java_jsuper_utils_Console_setCursorPosition(JNIEnv* env, jobject obj, jshort x, jshort y) {
	console->setPosition(x, y);
}

// Creates a coordinate class and bypasses the access restrictions to set the X and Y coordinates of the cursor
JNIEXPORT jobject JNICALL Java_jsuper_utils_Console_getCursorPosition(JNIEnv* env, jobject obj) {
	jclass clazz = env->FindClass("jsuper/utils/Coordinate");
	jmethodID constructorID = env->GetMethodID(clazz, "<init>", "()V");
	short x, y;
	console->getPosition(x, y);
	jobject instant = env->NewObject(clazz, constructorID);
	jmethodID setX = env->GetMethodID(clazz, "setX", "(S)V");
	jmethodID setY = env->GetMethodID(clazz, "setY", "(S)V");
	env->CallVoidMethod(instant, setX, x);
	env->CallVoidMethod(instant, setY, y);
	return instant;
}

// Creates a coordinate class and bypasses the access restrictions to set the viewable size of the console window
JNIEXPORT jobject JNICALL Java_jsuper_utils_Console_getConsoleSize(JNIEnv* env, jobject obj) {
	jclass clazz = env->FindClass("jsuper/utils/Coordinate");
	jmethodID constructorID = env->GetMethodID(clazz, "<init>", "()V");
	short x, y;
	console->getConsoleSize(x, y);
	jobject instant = env->NewObject(clazz, constructorID);
	jmethodID setX = env->GetMethodID(clazz, "setX", "(S)V");
	jmethodID setY = env->GetMethodID(clazz, "setY", "(S)V");
	env->CallVoidMethod(instant, setX, x);
	env->CallVoidMethod(instant, setY, y);
	return instant;
}

// Creates a coordinate class and bypasses the access restrictions to set the first coordinate of the viewable console
JNIEXPORT jobject JNICALL Java_jsuper_utils_Console_getFirstViewableCoordinate(JNIEnv* env, jobject obj) {
	jclass clazz = env->FindClass("jsuper/utils/Coordinate");
	jmethodID constructorID = env->GetMethodID(clazz, "<init>", "()V");
	short x, y;
	console->getViewableCoordinate(x, y);
	jobject instant = env->NewObject(clazz, constructorID);
	jmethodID setX = env->GetMethodID(clazz, "setX", "(S)V");
	jmethodID setY = env->GetMethodID(clazz, "setY", "(S)V");
	env->CallVoidMethod(instant, setX, x);
	env->CallVoidMethod(instant, setY, y);
	return instant;
}

// Instantiates the private data of the Console class, fills it up
Console::Console(void) {
	mData = new pConsole;
	mData->mInfo = new CONSOLE_SCREEN_BUFFER_INFO;
	mData->mScreenBuffer = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(mData->mScreenBuffer);
	mData->mInput = GetStdHandle(STD_INPUT_HANDLE);
	mData->mOutput = mData->mScreenBuffer;
	mData->mError = GetStdHandle(STD_ERROR_HANDLE);
	GetConsoleScreenBufferInfo(mData->mOutput, mData->mInfo);
}

// Frees private data of the Console class
Console::~Console(void) {
	delete mData->mInfo;
	delete mData;
}


void Console::setPosition(short x, short y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(mData->mOutput, pos);
}

void Console::getPosition(short& x, short& y) {
	mData->update();
	COORD pos = mData->mInfo->dwCursorPosition;
	x = pos.X;
	y = pos.Y;
}

// Gets the size of the console (minimum of 1)
void Console::getConsoleSize(short& x, short& y) {
	mData->update();
	SMALL_RECT window = mData->mInfo->srWindow;
	x = window.Right - window.Left + 1;
	y = window.Bottom - window.Top + 1;
}

// Gets the top left coordinate of the console
void Console::getViewableCoordinate(short& x, short& y) {
	mData->update();
	SMALL_RECT window = mData->mInfo->srWindow;
	x = window.Left;
	y = window.Top;
}