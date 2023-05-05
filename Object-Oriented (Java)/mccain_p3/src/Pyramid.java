public class Pyramid extends Shape3D {
    //private variables of Pyramid...
    private final double length;
    private final double width;
    private final double height;

    //constructor...
    public Pyramid(double lengthInput, double widthInput, double heightInput) {
        //store inputs to private variables within Pyramid...
        length = lengthInput;
        width = widthInput;
        height = heightInput;
    }

    //Override superclass...
    @Override
    public String getName() {
        return "pyramid";
    }

    @Override
    public double getArea() {
        return (length * width + length * Math.sqrt(((width / 2) * (width / 2)) + (height * height))
                + width * Math.sqrt(((length / 2) * (length / 2)) + (height * height)));
    }

    @Override
    public double getVolume() {
        return (length * width * height) / 3;
    }
}
