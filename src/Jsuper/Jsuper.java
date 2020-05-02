import jsuper.utils.*;

public class Jsuper {
	private Console baseConsole;

	private static Coordinate absoluteCoordinates(Coordinate relativePos, Coordinate start) {
		return new Coordinate((short)(relativePos.getX() + start.getX()), (short)(relativePos.getY() + start.getY()));
	}

	private static Coordinate relativeCoordinates(Coordinate absolutePos, Coordinate start) {
		return new Coordinate((short)(absolutePos.getX() - start.getX()), (short)(absolutePos.getY() - start.getY()));
	}

	public boolean processInput(int input) {
		boolean ret = true;
		Coordinate start = baseConsole.getStart();
		Coordinate curPos = relativeCoordinates(baseConsole.getCursor(), start);
		short x = curPos.getX();
		short y = curPos.getY();
		if (input >= 0) {
			baseConsole.out.print((char)(input));
			x++;
		}
		else {
			switch (input) {
				case -1:
					ret = false;
					break;
				case -100:
					y--;
					break;
				case -101:
					x--;
					break;
				case -102:
					x++;
					break;
				case -103:
					y++;
					break;
			}
		}
		baseConsole.setCursor(absoluteCoordinates(new Coordinate(x, y), start));
		return ret;
	}

	private static Coordinate clamp(Coordinate pos, Coordinate bounds) {
		short x = pos.getX();
		short y = pos.getY();
		if (x > bounds.getX())
			x = bounds.getX();
		if (y > bounds.getY())
			y = bounds.getY();
		return new Coordinate(x, y);
	}

	public Jsuper() throws Exception {
		baseConsole = new Console();
	}

	public static void main(String[] args) throws Exception {
		Jsuper app = new Jsuper();
		boolean cont = app.processInput(app.baseConsole.getNext());
		while (cont) {
			cont = app.processInput(app.baseConsole.getNext());
		}
	}
}