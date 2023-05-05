public class Encrypter {
    public static String encrypt(String e) {
        int encArray[] = new int[4];
        char charArray[] = new char[4];
        int tempInt;
        String newE = "";

        //copy string to char array...
        for (int i = 0; i < 4; i++) {
            charArray[i] = e.charAt(i);
        }

        //copy char array to int array...
        for (int i = 0; i < 4; i++) {
            encArray[i] = Character.getNumericValue(charArray[i]);
        }

        //add 7 to each num in array...
        for (int i = 0; i < 4; i++) {
            encArray[i] += 7;
        }

        //get remainder of int when divided by 10...
        for (int i = 0; i < 4; i++) {
            encArray[i] = encArray[i] % 10;
        }

        //swap digits 1 and 3...
        tempInt = encArray[0];
        encArray[0] = encArray[2];
        encArray[2] = tempInt;
        //swap digits 2 and 4...
        tempInt = encArray[1];
        encArray[1] = encArray[3];
        encArray[3] = tempInt;

        //copy int array to string...
        for (int i = 0; i < 4; i++) {
            newE += Integer.toString(encArray[i]);
        }
        return newE;
    }
}
