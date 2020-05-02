#include "console.hpp"
#include "private\pconsole.hpp"

#include <stdlib.h>

Console::Console(void) {
	mData = new pConsole;
	mData->mInfo = (CONSOLE_SCREEN_BUFFER_INFO*)malloc(sizeof(CONSOLE_SCREEN_BUFFER_INFO));
	mData->mOutput = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	SetConsoleActiveScreenBuffer(mData->mOutput);
	mData->hasFocus = true;
	GetConsoleScreenBufferInfo(mData->mOutput, mData->mInfo);
}

Console::~Console(void) {
	free(mData->mInfo);
	delete mData;
}

void Console::showDefault() {
	SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
}

void Console::show(void) {
	if (mData->hasFocus == false) {
		SetConsoleActiveScreenBuffer(mData->mOutput);
		mData->hasFocus = true;
	}
}

void Console::unfocus(void) {
	mData->hasFocus = false;
}

void Console::setCursor(short x, short y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(mData->mOutput, pos);
}

bool Console::getFocus(void) {
	return mData->hasFocus;
}

void Console::getCursor(short* x, short* y) {
	mData->update();
	COORD pos = mData->mInfo->dwCursorPosition;
	*x = pos.X;
	*y = pos.Y;
}

void Console::getSize(short* x, short* y) {
	mData->update();
	SMALL_RECT size = mData->mInfo->srWindow;
	*x = size.Right - size.Left + 1;
	*y = size.Bottom - size.Top + 1;
}

void Console::getStart(short* x, short* y) {
	mData->update();
	SMALL_RECT size = mData->mInfo->srWindow;
	*x = size.Left;
	*y = size.Top;
}