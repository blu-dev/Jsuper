import jsuper.utils.*;

public class Jsuper {
	private Console baseConsole;

	private static Coordinate absoluteCoordinates(Coordinate relativePos, Coordinate start) {
		return new Coordinate((short)(relativePos.getX() + start.getX()), (short)(relativePos.getY() + start.getY()));
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
		Coordinate start = app.baseConsole.getStart();
		app.baseConsole.out.println(start.getX() + ' ' + start.getY());
		for (short i = 0; i < 50; i++) {
			for (short j = 0; j < 50; j++) {
				app.baseConsole.setCursor(absoluteCoordinates(new Coordinate(j, i), start));
				app.baseConsole.out.print('h');
				Thread.sleep(20);
			}
		}
		Thread.sleep(5000);
	}
}