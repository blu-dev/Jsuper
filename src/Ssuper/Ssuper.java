import ssuper.utils.Console;

public class Ssuper {
	public static void main(String[] args) {
		Console myConsole = new Console();
		Console.CursorPosition pos;
		for (short i = 0; i < 50; i++) {
			for (short j = 0; j < 50; j++) {
				myConsole.setCoordinates(i, j);
				System.out.print(" ");
			}
		}
		for (short i = 0; i < 10; i++) {
			for (short j = 0; j < 10; j++) {
				myConsole.setCoordinates((short)(i * 4), j);
				pos = myConsole.getCoordinates();
				System.out.print(pos.getX()/4 + " " + pos.getY());
			}
		}
	}
}