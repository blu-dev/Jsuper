package jsuper.utils.actions;

import jsuper.utils.*;

public abstract class Action implements IPerformable {
	// Private fields

	private int actionID;
	private Console console;

	// Protected methods

	protected Console getLinkedConsole() {
		return console;
	}

	// Public methods

	public Action(int id, Console link) {
		actionID = id;
		linkConsole(link);
	}

	public boolean isThisAction(int testID) {
		boolean ret = false;
		if (testID == actionID)
			ret = true;
		return ret;
	}

	public void linkConsole(Console link) {
		console = link;
	}

	public void perform() {
		System.err.println("Error: Abstract class performing, id:" + actionID);
	}
}