public class Sphere extends Shape3D {
    //private variables of Pyramid...
    private final double pi = Math.PI;
    private final double radius;

    //constructor...
    public Sphere(double radiusInput) {
        //store inputs to private variables within Pyramid...
        radius = radiusInput;
    }

    //Override superclass...
    @Override
    public String getName() {
        return "sphere";
    }

    @Override
    public double getArea() {
        return 4 * pi * (radius * radius);
    }

    @Override
    public double getVolume() {
        return (4.0 / 3.0) * pi * (radius * radius * radius);
        //decimals are used for 4/3, because otherwise integer arithmetic rounds to 1.0...
    }
}