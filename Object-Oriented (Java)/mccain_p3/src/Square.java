public class Square extends Shape2D {
    //private variables of Square...
    private final double sideLength;

    //constructor...
    public Square(double sideInput) {
        //stores input as private variable within Square class...
        sideLength = sideInput;
    }

    //Override superclass...
    @Override
    public String getName() {
        return "square";
    }

    @Override
    public double getArea() {
        return (sideLength * sideLength);
    }
}
