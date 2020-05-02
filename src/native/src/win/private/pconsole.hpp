#ifndef PRIVATE_CONSOLE_HPP
#define PRIVATE_CONSOLE_HPP

struct pConsole {
	HANDLE mOutput;
	CONSOLE_SCREEN_BUFFER_INFO* mInfo;
	bool hasFocus;
	inline void update(void) {GetConsoleScreenBufferInfo(mOutput, mInfo);}
};

#endif