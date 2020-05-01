package jsuper.utils;

// All native methods are private in case I decide to implement multi-console editing later on, keeping the handles away from the user

public class Console {
	private native void init();
	private native void setCursorPosition(short x, short y);
	private native Coordinate getCursorPosition();
	private native Coordinate getConsoleSize();
	private native Coordinate getFirstViewableCoordinate();

	private Coordinate cursorPosition;
	private Coordinate size;
	private Coordinate startPosition;

	private void update() {
		setCursorPosition(cursorPosition.getX(), cursorPosition.getY());
	}

	public Console() {
		init();
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