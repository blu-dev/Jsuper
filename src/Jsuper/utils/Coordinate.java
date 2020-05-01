package jsuper.utils;

public class Coordinate {
	private short x;
	private short y;
	private void setX(short pos) {x = pos;}
	private void setY(short pos) {y = pos;}
	public Coordinate() {}
	public Coordinate(short cx, short cy) {
		x = cx;
		y = cy;
	}
	public short getX() {return x;}
	public short getY() {return y;}
}