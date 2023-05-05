public class Decrypter {
    public static String decrypt(String d) {
        int decArray[] = new int[4];
        char charArray[] = new char[4];
        int tempInt;
        String newD = "";

        //copy string to char array...
        for (int i = 0; i < 4; i++) {
            charArray[i] = d.charAt(i);
        }

        //copy char array to int array...
        for (int i = 0; i < 4; i++) {
            decArray[i] = Character.getNumericValue(charArray[i]);
        }

        //swap digits 1 and 3...
        tempInt = decArray[0];
        decArray[0] = decArray[2];
        decArray[2] = tempInt;
        //swap digits 2 and 4...
        tempInt = decArray[1];
        decArray[1] = decArray[3];
        decArray[3] = tempInt;

        /*add 3 to each num in array so that the addition
        of 7 in encryption will total 10 before mod...*/
        for (int i = 0; i < 4; i++) {
            decArray[i] += 3;
        }

        //mod by 10...
        for (int i = 0; i < 4; i++) {
            decArray[i] = decArray[i] % 10;
        }

        //copy int array to string...
        for (int i = 0; i < 4; i++) {
            newD += Integer.toString(decArray[i]);
        }
        return newD;
    }
}
