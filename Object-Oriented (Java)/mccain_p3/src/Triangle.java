public class Triangle extends Shape2D {
    //private variables of Triangle...
    private final double base;
    private final double height;

    //constructor...
    public Triangle(double baseInput, double heightInput) {
        //store inputs to private variables within Triangle...
        base = baseInput;
        height = heightInput;
    }

    //Override superclass...
    @Override
    public String getName() {
        return "triangle";
    }

    @Override
    public double getArea() {
        return ((base * height) / 2);
    }
}
