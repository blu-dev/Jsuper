package ssuper.utils;

// All native methods are private in case I decide to implement multi-console editing later on, keeping the handles away from the user

public class Console {
	public class CursorPosition {
		private short x;
		private short y;
		private void setX(short pos) {x = pos;}
		private void setY(short pos) {y = pos;}
		public CursorPosition() {}
		public short getX() {return x;}
		public short getY() {return y;}
	}


	private native void init();
	private native void setCursorPosition(short x, short y);
	private native CursorPosition getCursorPosition();

	public Console() {
		init();
	}

	public void setCoordinates(short x, short y) {
		setCursorPosition(x, y);
	}

	public CursorPosition getCoordinates() {
		return getCursorPosition();
	}

	static {
		System.loadLibrary("native");
	}
}