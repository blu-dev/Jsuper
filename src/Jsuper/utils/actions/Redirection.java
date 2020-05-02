package jsuper.utils.actions;

import jsuper.utils.*;

public class Redirection extends Action {
	// Private fields

	Coordinate localRedirection;

	// Public methods

	public Redirection(int id, Console link, short localX, short localY) {
		super(id, link);
		localRedirection = new Coordinate(localX, localY);
	}

	@Override
	public void perform() {
		Console console = getLinkedConsole();
		Coordinate start = console.getStart();
		Coordinate cur = console.getCursor();
		Coordinate size = console.getSize();
		short x = cur.getX();
		short y = cur.getY();
		short lx = localRedirection.getX();
		short ly = localRedirection.getY();

		if (lx == -size.getX())
			x = start.getX();
		else
			x += lx;
		if (ly == -size.getY())
			y = start.getY();
		else
			y += ly;
		console.setCursor(new Coordinate(x, y));
	}		
}