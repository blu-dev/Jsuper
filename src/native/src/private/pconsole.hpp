#ifndef PRIVATE_CONSOLE_HPP
#define PRIVATE_CONSOLE_HPP

#include "console.hpp"

class Console;

struct pConsole {
	HANDLE mInput;
	HANDLE mOutput;
	HANDLE mError;
	CONSOLE_SCREEN_BUFFER_INFO* mInfo;
};

#endif