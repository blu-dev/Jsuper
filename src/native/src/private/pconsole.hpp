#ifndef PRIVATE_CONSOLE_HPP
#define PRIVATE_CONSOLE_HPP

#include "console.hpp"

class Console;

struct pConsole {
	HANDLE mScreenBuffer;
	HANDLE mInput;
	HANDLE mOutput;
	HANDLE mError;
	CONSOLE_SCREEN_BUFFER_INFO* mInfo;
	inline void update(void) {GetConsoleScreenBufferInfo(mOutput, mInfo);}
};

#endif