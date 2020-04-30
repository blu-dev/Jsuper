package Ssuper.utils;

// All native methods are private in case I decide to implement multi-console editing later on, keeping the handles away from the user

public class Console {
	private native void init();
	private native void setCursorPosition(short x, short y);
	public Console() {
		init();
	}

	public void setCoordinates(short x, short y) {
		setCursorPosition(x, y);
	}

	static {
		System.loadLibrary("native");
	}
}