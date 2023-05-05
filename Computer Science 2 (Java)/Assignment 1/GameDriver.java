/* PLACE YOUR NAME HERE
   Dr. Steinberg
   COP3503 Fall 2022
   Programming Assignment 1
*/


public class GameDriver
{
	public static void main(String [] args) throws Exception
	{
		System.out.println("Testing to See if Player 1 will always win...");
		System.out.println("********************");
		Game g1 = new Game(8, "moves1.txt");
		Game g2 = new Game(8, "moves2.txt");
		Game g3 = new Game(8, "moves3.txt");
		Game g4 = new Game(8, "moves4.txt");
		Game g5 = new Game(8, "moves5.txt");
		
		if(g1.play(1) == 1)
			System.out.println("Player 1 Game 1 Pass!");
		else
			System.out.println("Player 1 Game 1 Fail!");
		
		if(g2.play(1) == 1)
			System.out.println("Player 1 Game 2 Pass!");
		else
			System.out.println("Player 1 Game 2 Fail!");
		
		if(g3.play(1) == 1)
			System.out.println("Player 1 Game 3 Pass!");
		else
			System.out.println("Player 1 Game 3 Fail!");
		
		if(g4.play(1) == 1)
			System.out.println("Player 1 Game 4 Pass!");
		else
			System.out.println("Player 1 Game 4 Fail!");
		
		if(g5.play(1) == 1)
			System.out.println("Player 1 Game 5 Pass!");
		else
			System.out.println("Player 1 Game 5 Fail!");
		

		
		System.out.println("Testing to See if Player 2 will always win...");
		System.out.println("********************");
		if(g1.play(2) == 2)
			System.out.println("Player 2 Game 1 Pass!");
		else
			System.out.println("Player 2 Game 1 Fail!");
		
		if(g2.play(2) == 2)
			System.out.println("Player 2 Game 2 Pass!");
		else
			System.out.println("Player 2 Game 2 Fail!");
		
		if(g3.play(2) == 2)
			System.out.println("Player 2 Game 3 Pass!");
		else
			System.out.println("Player 2 Game 3 Fail!");
		
		if(g4.play(2) == 2)
			System.out.println("Player 2 Game 4 Pass!");
		else
			System.out.println("Player 2 Game 4 Fail!");
		
		if(g5.play(2) == 2)
			System.out.println("Player 2 Game 5 Pass!");
		else
			System.out.println("Player 2 Game 5 Fail!");
	}
}