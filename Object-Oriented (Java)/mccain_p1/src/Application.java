public class Application {
    public static void main(String ...args) {

        String exampleText = "1234";
        String encReturned;
        String decReturned;

        encReturned = Encrypter.encrypt(exampleText);
        decReturned = Decrypter.decrypt(encReturned);

        System.out.println(encReturned);
        System.out.println(decReturned);
    }
}
