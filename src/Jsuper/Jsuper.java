import java.util.ArrayList;
import jsuper.utils.*;
import jsuper.utils.actions.*;

public class Jsuper {
	// Private fields

	private ArrayList<Console> consoles;
	private ArrayList<Action> consoleActions;

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
		consoleActions = new ArrayList<Action>();
		consoleActions.add(new Redirection(-102, null, (short)0, (short)-1)); // up arrow
		consoleActions.add(new Redirection(-110, null, (short)0, (short)1)); // down arrow
		consoleActions.add(new Redirection(-107, null, (short)1, (short)0)); // right arrow
		consoleActions.add(new Redirection(-105, null, (short)-1, (short)0)); // left arrow
	}

	public static void main(String[] args) {
		Jsuper app = new Jsuper();
		// This is test code for handling multiple tabs in an order. 
		ArrayList<Integer> handles = new ArrayList<Integer>();

		handles.add(app.createConsole());
		Console activeConsole = app.consoles.get(handles.get(0));
		app.linkActions(activeConsole);
		boolean cont = app.processInput(activeConsole.getInput(), activeConsole);

		while (cont) {
			activeConsole.query();
			cont = app.processInput(activeConsole.getInput(), activeConsole);
		}
	}

	public int createConsole() {
		int handle = nextAvailableConsole();
		if (handle == consoles.size())
			consoles.add(new Console());
		else
			consoles.set(handle, new Console());
		return handle;
	}

	public boolean processInput(int input, Console activeConsole) {
		boolean breakFlag = false;
		boolean ret = true;
		for (Action a : consoleActions) {
			if (a.isThisAction(input)) {
				a.perform();
				breakFlag = true;
				break;
			}
		}
		if (input == (int)('q')) {
			ret = false;
			breakFlag = true;
		}
		if (!breakFlag) {
			activeConsole.out.print((char)input);
		}
		return ret;
	}

	public void linkActions(Console link) {
		for (Action a : consoleActions) {
			a.linkConsole(link);
		}
	}
}