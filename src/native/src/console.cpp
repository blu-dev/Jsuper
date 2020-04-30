#include "Ssuper_utils_Console.h"
#include "console.hpp"
#include "private/pconsole.hpp"

Console* console;

JNIEXPORT void JNICALL Java_Ssuper_utils_Console_init(JNIEnv* env, jobject obj) {
	console = new Console();
}

JNIEXPORT void JNICALL Java_Ssuper_utils_Console_setCursorPosition(JNIEnv* env, jobject obj, jshort x, jshort y) {
	console->setPosition(x, y);
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