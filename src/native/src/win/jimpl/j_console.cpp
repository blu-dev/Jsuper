#include "jsuper_utils_Console.h"

#include "console.hpp"
#include "..\private\pconsole.hpp"

#include <vector>

std::vector<Console*>* consoles;

void updateFocus(int exclude);
void testFunctionKeys(int* val);
void testNavigationKeys(int* val);
int getConsoleHandle(JNIEnv* env, jobject obj);
int nextAvailableHandle(void);
jobject createCoordinate(JNIEnv* env, short x, short y);

JNIEXPORT jint JNICALL Java_jsuper_utils_Console_readRawInput(JNIEnv* env, jclass cls) {
	int ret = _getwch();
	if (ret == 0 || ret == 0xE0) { // Getting some function keys and/or numpad input
		ret == _getwch();
		testFunctionKeys(&ret);
		if (ret > 0)
			testNavigationKeys(&ret);
	}
	return ret;
}

JNIEXPORT jobject JNICALL Java_jsuper_utils_Console_init(JNIEnv* env, jobject obj) {
	static bool hasInitConsoles = false;
	if (!hasInitConsoles) {
		consoles = new std::vector<Console*>;
		hasInitConsoles = true;
	}

	int handle = nextAvailableHandle();
	if (handle >= consoles->size())
		consoles->push_back(new Console());
	else
		consoles->at(handle) = new Console();

	updateFocus(handle);

	// TODO: Add exception handling here
	jclass conClass = env->FindClass("jsuper/utils/Console");
	jfieldID handleID = env->GetFieldID(conClass, "nativeHandle", "I");
	env->SetIntField(obj, handleID, handle);

	// TODO: Add exception handling here
	jclass psClass = env->FindClass("java/io/PrintStream");
	jmethodID psConstructor = env->GetMethodID(psClass, "<init>", "(Ljava/lang/String;)V");
	jobject psObj = env->NewObject(psClass, psConstructor, env->NewStringUTF("CONOUT$"));
	
	return psObj;
}

JNIEXPORT void JNICALL Java_jsuper_utils_Console_close(JNIEnv* env, jobject obj) {
	int handle = getConsoleHandle(env, obj);

	if (consoles->at(handle)->getFocus()) {
		bool success = false;
		for (int i = consoles->size() - 1; i >= 0; i--) {
			if (consoles->at(i) != nullptr && i != handle) {
				consoles->at(i)->show();
				updateFocus(i);
				success = true;
			}
		}
		if (!success)
			Console::showDefault();
	}

	if (handle >= 0) {
		delete consoles->at(handle);
		consoles->at(handle) = nullptr;
	}
}

JNIEXPORT void JNICALL Java_jsuper_utils_Console_focus(JNIEnv* env, jobject obj) {
	int handle = getConsoleHandle(env, obj);

	consoles->at(handle)->show();
	updateFocus(handle);
}

JNIEXPORT jobject JNICALL Java_jsuper_utils_Console_getCursorPosition(JNIEnv* env, jobject obj) {
	int handle = getConsoleHandle(env, obj);

	short x, y;
	consoles->at(handle)->getCursor(&x, &y);
	jobject ret = createCoordinate(env, x, y);

	return ret;
}

JNIEXPORT jobject JNICALL Java_jsuper_utils_Console_getConsoleSize(JNIEnv* env, jobject obj) {
	int handle = getConsoleHandle(env, obj);

	short x, y;
	consoles->at(handle)->getSize(&x, &y);
	jobject ret = createCoordinate(env, x, y);

	return ret;
}

JNIEXPORT jobject JNICALL Java_jsuper_utils_Console_getStartCoordinate(JNIEnv* env, jobject obj) {
	int handle = getConsoleHandle(env, obj);

	short x, y;
	consoles->at(handle)->getStart(&x, &y);
	jobject ret = createCoordinate(env, x, y);

	return ret;
}

JNIEXPORT void JNICALL Java_jsuper_utils_Console_setCursorPosition(JNIEnv* env, jobject obj, jshort x, jshort y) {
	int handle = getConsoleHandle(env, obj);

	consoles->at(handle)->setCursor(x, y);
}

void updateFocus(int exclude) {
	for (int i = 0; i < consoles->size(); i++) {
		if (i != exclude && consoles->at(i) != nullptr)
			consoles->at(i)->unfocus(); 
	}
}

void testFunctionKeys(int* val) {
	bool breakFlag = false;
	for (int i = 0x3B; i < 0x45; i++) {
		*val = (*val = i) ? -(i - 0x3A) : *val;
		if (*val < 0) {
			breakFlag = true;
			break;
		}
	}
	if (!breakFlag) {
		if (*val == 0x85) {
			*val = -11;
			breakFlag = true;
		} else if (*val = 0x86) {
			*val = -12;
			breakFlag = true;
		}
	}
}

void testNavigationKeys(int* val) {
	for (int i = 0x47; i < 0x54; i++) {
		*val = (*val = i) ? (-i - 0x46) : *val;
		if (*val < 0) {
			break;
		}
	}
}

int getConsoleHandle(JNIEnv* env, jobject obj) {
	// TODO: Add exception handling here
	jclass conClass = env->FindClass("jsuper/utils/Console");
	jfieldID handleID = env->GetFieldID(conClass, "nativeHandle", "I");
	int ret = env->GetIntField(obj, handleID);

	return ret;
}

jobject createCoordinate(JNIEnv* env, short x, short y) {
	// TODO: Add exception handling here
	jclass crdClass = env->FindClass("jsuper/utils/Coordinate");
	jmethodID crdConstructor = env->GetMethodID(crdClass, "<init>", "(SS)V");
	jobject crdObj = env->NewObject(crdClass, crdConstructor, x, y);

	return crdObj;
}

int nextAvailableHandle(void) {
	int ret = consoles->size();
	for (int i = 0; i < consoles->size(); i++) {
		if (consoles->at(i) == nullptr) {
			ret = i;
			break;
		}
	}
	return ret;
}