import ssuper.utils.Console;

public class Ssuper {
	public static void main(String[] args) {
		Console myConsole = new Console();
		Console.Coordinate size = myConsole.getSize();
		System.out.println(size.getX() + " " + size.getY());
		Console.Coordinate first = myConsole.getStartCoordinate();
		System.out.println(first.getX() + " " + first.getY());
	}
}