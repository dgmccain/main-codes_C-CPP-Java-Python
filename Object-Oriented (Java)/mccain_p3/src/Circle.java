import java.lang.Math.*;

public class Circle extends Shape2D {
    //private variables of Circle...
    private final double pi = Math.PI;
    private final double radius;

    //constructor...
    public Circle(double radiusInput) {
        //store input to private variables within Circle...
        radius = radiusInput;
    }

    //Override superclass...
    @Override
    public String getName() {
        return "circle";
    }

    @Override
    public double getArea() {
        return (pi * radius * radius);
    }
}
