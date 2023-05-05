/* PLACE YOUR NAME HERE
   Dr. Steinberg
   COP3503 Spring 2023
   Programming Assignment 3
*/

public class CookiesDriver
{
		
	public static void main(String [] args) throws Exception
	{
		Cookies test = new Cookies(105, 100, "campers1.txt", "cookies1.txt");
		Cookies test2 = new Cookies(800, 750, "campers2.txt", "cookies2.txt");
		Cookies test3 = new Cookies(2000, 1900, "campers3.txt", "cookies3.txt");
		Cookies test4 = new Cookies(9000, 8888, "campers4.txt", "cookies4.txt");
		Cookies test5 = new Cookies(20000, 19700, "campers5.txt", "cookies5.txt");

		System.out.println("Testing First Scenario...");
		test.passCookies();
		test.display();

		
		System.out.println("Testing Second Scenario...");
		test2.passCookies();
		test2.display();
		
		System.out.println("Testing Third Scenario...");
		test3.passCookies();
		test3.display();
		
		System.out.println("Testing Fourth Scenario...");
		test4.passCookies();
		test4.display();
		
		System.out.println("Testing Fifth Scenario...");
		test5.passCookies();
		test5.display();
	}
}