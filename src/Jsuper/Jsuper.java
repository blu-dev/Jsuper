import java.util.ArrayList;
import jsuper.utils.*;

public class Jsuper {
	// Private fields

	private ArrayList<Console> consoles;

	// Private methods

	private static Coordinate absolute(Coordinate relative, Coordinate start) {
		return new Coordinate((short)(relative.getX() + start.getX()), (short)(relative.getY() + start.getY()));
	}

	private static Coordinate relative(Coordinate absolute, Coordinate start) {
		return new Coordinate((short)(absolute.getX() - start.getX()), (short)(absolute.getY() + start.getY()));
	}

	private int nextAvailableConsole() {
		int ret = consoles.size();
		for (int i = 0; i < consoles.size(); i++) {
			if (consoles.get(i).equals(null)) {
				ret = i;
				break;
			}
		}
		return ret;
	}

	// Public methods

	public Jsuper() {
		consoles = new ArrayList<Console>();
	}

	public static void main(String[] args) {
		Jsuper app = new Jsuper();
		int handle = app.createConsole();
		int handle2 = app.createConsole();
		app.consoles.get(handle).out.println("world");
		app.consoles.get(handle2).out.println("hello");
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			System.err.println("InterruptedException Occurred: " + e.getMessage());
		}
		app.consoles.get(handle).show();
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			System.err.println("InterruptedException Occurred: " + e.getMessage());
		}
		app.consoles.get(handle).terminate();
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			System.err.println("InterruptedException Occurred: " + e.getMessage());
		}
		app.consoles.get(handle2).terminate();
	}

	public int createConsole() {
		int handle = nextAvailableConsole();
		if (handle == consoles.size())
			consoles.add(new Console());
		else
			consoles.set(handle, new Console());
		return handle;
	}
}