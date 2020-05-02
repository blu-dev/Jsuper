package jsuper.utils;

import java.io.PrintStream;

public class Console {
	// Native functions

	private static native int readRawInput();
	private native PrintStream init();
	private native void close();
	private native void focus();
	private native Coordinate getCursorPosition();
	private native Coordinate getConsoleSize();
	private native Coordinate getStartCoordinate();
	private native void setCursorPosition(short x, short y);

	// Private fields

	private int nativeHandle;
	private Coordinate cursorPosition;
	private Coordinate size;
	private Coordinate startPosition;

	// Private methods

	private void update() {

	}

	// Public fields

	public PrintStream out;

	// Public methods

	public Console() {
		out = init();
		query();
	}

	public void show() {
		focus();
	}

	public void query() {
		cursorPosition = getCursorPosition();
		size = getConsoleSize();
		startPosition = getStartCoordinate();
	}

	public void terminate() {
		close();
		nativeHandle = -1;
	}

	public void setCursor(Coordinate pos) {
		setCursorPosition(pos.getX(), pos.getY());
	}

	public Coordinate getCursor() { return cursorPosition; }
	public Coordinate getSize() { return size; }
	public Coordinate getStart() { return startPosition; }

	static {
		System.loadLibrary("native");
	}


}