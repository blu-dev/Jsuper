package jsuper.utils;

// All native methods are private in case I decide to implement multi-console editing later on, keeping the handles away from the user

public class Console {
	// A basic coordinate class designed to work with the native implementation only
	public class Coordinate {
		private short x;
		private short y;
		private void setX(short pos) {x = pos;}
		private void setY(short pos) {y = pos;}
		public Coordinate() {}
		public short getX() {return x;}
		public short getY() {return y;}
	}


	private native void init();
	private native void setCursorPosition(short x, short y);
	private native Coordinate getCursorPosition();
	private native Coordinate getConsoleSize();
	private native Coordinate getFirstViewableCoordinate();

	public Console() {
		init();
	}

	public void setCoordinates(short x, short y) {
		setCursorPosition(x, y);
	}

	public Coordinate getCoordinates() {
		return getCursorPosition();
	}

	public Coordinate getSize() {
		return getConsoleSize();
	}

	public Coordinate getStartCoordinate() {
		return getFirstViewableCoordinate();
	}

	static {
		System.loadLibrary("native");
	}
}