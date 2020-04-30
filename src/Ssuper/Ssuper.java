import Ssuper.utils.Console;

public class Ssuper {
	public static void main(String[] args) {
		Console myConsole = new Console();
		for (short i = 0; i < 10; i++) {
			for (short j = 0; j < 10; j++) {
				myConsole.setCoordinates(i, j);
			}
		}
	}
}