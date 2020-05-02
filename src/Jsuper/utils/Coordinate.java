package jsuper.utils;

public class Coordinate {
	// Private fields

	private short x;
	private short y;
	
	// Public methods

	public Coordinate(short cx, short cy) {
		x = cx;
		y = cy;
	}

	public short getX() { return x; }
	public short getY() { return y; }
}