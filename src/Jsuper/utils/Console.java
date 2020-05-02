package jsuper.utils;

import java.io.PrintStream;
// All native methods are private in case I decide to implement multi-console editing later on, keeping the handles away from the user

public class Console {
	private native PrintStream init();
	private native void setCursorPosition(short x, short y);
	private native Coordinate getCursorPosition();
	private native Coordinate getConsoleSize();
	private native Coordinate getFirstViewableCoordinate();
	private static native int readRawInput();

	private Coordinate cursorPosition;
	private Coordinate size;
	private Coordinate startPosition;

	private void update() {
		setCursorPosition(cursorPosition.getX(), cursorPosition.getY());
	}

	public PrintStream out;

	public static int getNext() {
		return readRawInput();
	}

	public Console() throws Exception {
		out = init();
		query();
	}

	public void query() {
		cursorPosition = getCursorPosition();
		size = getConsoleSize();
		startPosition = getFirstViewableCoordinate();
	}

	public void setCursor(Coordinate pos) {
		cursorPosition = pos;
		update();
	}

	public Coordinate getCursor() {
		return cursorPosition;
	}

	public Coordinate getSize() {
		return size;
	}

	public Coordinate getStart() {
		return startPosition;
	}

	static {
		System.loadLibrary("native");
	}
}