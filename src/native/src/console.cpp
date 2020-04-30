#include "Ssuper_utils_Console.h"
#include "console.hpp"
#include "private/pconsole.hpp"

#include <iostream>

Console* console;

JNIEXPORT void JNICALL Java_ssuper_utils_Console_init(JNIEnv* env, jobject obj) {
	console = new Console();
}

JNIEXPORT void JNICALL Java_ssuper_utils_Console_setCursorPosition(JNIEnv* env, jobject obj, jshort x, jshort y) {
	console->setPosition(x, y);
}

JNIEXPORT jobject JNICALL Java_ssuper_utils_Console_getCursorPosition(JNIEnv* env, jobject obj) {
	jclass cCursorPosition = env->FindClass("ssuper/utils/Console$CursorPosition");
	jmethodID constructorID = env->GetMethodID(cCursorPosition, "<init>", "(Lssuper/utils/Console;)V");
	short x, y;
	console->getPosition(x, y);
	jobject oCursorPosition = env->NewObject(cCursorPosition, constructorID, obj);
	jmethodID setX = env->GetMethodID(cCursorPosition, "setX", "(S)V");
	jmethodID setY = env->GetMethodID(cCursorPosition, "setY", "(S)V");
	env->CallVoidMethod(oCursorPosition, setX, x);
	env->CallVoidMethod(oCursorPosition, setY, y);
	return oCursorPosition;
}

Console::Console(void) {
	mData = new pConsole;
	mData->mInfo = new CONSOLE_SCREEN_BUFFER_INFO;
	mData->mInput = GetStdHandle(STD_INPUT_HANDLE);
	mData->mOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	mData->mError = GetStdHandle(STD_ERROR_HANDLE);
	GetConsoleScreenBufferInfo(mData->mOutput, mData->mInfo);
}

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
	//std::cout << pos.X << " " << pos.Y << std::endl;
	x = pos.X;
	y = pos.Y;
}