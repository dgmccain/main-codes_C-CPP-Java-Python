import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

class ShapeTest {

    //Square Tests...
    @Test
    public void TestSquareName() {
        Shape shape = new Square(10);
        assertEquals("square", shape.getName());
    }

    @Test
    public void TestSquareArea() {
        Shape2D shape = new Square(10);
        assertEquals(100, shape.getArea());
    }

    @Test
    public void TestSquareArea2() {
        Shape2D shape = new Square(0.5);
        assertEquals(0.25, shape.getArea());
    }

    //Triangle Tests...
    @Test
    public void TestTriangleName() {
        Shape shape = new Triangle(100, 100);
        assertEquals("triangle", shape.getName());
    }

    @Test
    public void TestTriangleArea() {
        Shape2D shape = new Triangle(10, 10);
        assertEquals(50, shape.getArea());
    }

    @Test
    public void TestTriangleArea2() {
        Shape2D shape = new Triangle(0.5, 0.25);
        assertEquals(0.063, shape.getArea(), 0.001);
    }

    //Circle Tests...
    @Test
    public void TestCircleName() {
        Shape shape = new Circle(10);
        assertEquals("circle", shape.getName());
    }

    @Test
    public void TestCircleArea() {
        Shape2D shape = new Circle(10);
        assertEquals(314.16, shape.getArea(), 0.01);
    }

    @Test
    public void TestCircleArea2() {
        Shape2D shape = new Circle(0.5);
        assertEquals(0.79, shape.getArea(), 0.01);
    }

    //Cube Tests...
    @Test
    public void TestCubeName() {
        Shape shape = new Cube(100);
        assertEquals("cube", shape.getName());
    }

    @Test
    public void TestCubeArea() {
        Shape3D shape = new Cube(10);
        assertEquals(600, shape.getArea());
    }

    @Test
    public void TestCubeArea2() {
        Shape shape = new Cube(0.5);
        assertEquals(1.5, shape.getArea());
    }

    @Test
    public void TestCubeVolume() {
        Shape3D shape = new Cube(10);
        assertEquals(1000, shape.getVolume());
    }

    @Test
    public void TestCubeVolume2() {
        Shape3D shape = new Cube(0.5);
        assertEquals(0.13, shape.getVolume(), 0.01);
    }

    //Pyramid Tests...
    @Test
    public void TestPyramidName() {
        Shape shape = new Pyramid(10, 10, 10);
        assertEquals("pyramid", shape.getName());
    }

    @Test
    public void TestPyramidArea() {
        Shape3D shape = new Pyramid(10, 10, 10);
        assertEquals(323.61, shape.getArea(), 0.01);
    }

    @Test
    public void TestPyramidArea2() {
        Shape3D shape = new Pyramid(5, 10, 15);
        assertEquals(281.13, shape.getArea(), 0.01);
    }

    @Test
    public void TestPyramidVolume() {
        Shape3D shape = new Pyramid(10, 10, 10);
        assertEquals(333.33, shape.getVolume(), 0.01);
    }

    @Test
    public void TestPyramidVolume2() {
        Shape3D shape = new Pyramid(1.5, 0.5, 2.5);
        assertEquals(0.63, shape.getVolume(), 0.01);
    }

    //Sphere Tests...
    @Test
    public void TestSphereName() {
        Shape shape = new Sphere(10);
        assertEquals("sphere", shape.getName());
    }

    @Test
    public void TestSphereArea() {
        Shape3D shape = new Sphere(10);
        assertEquals(1256.64, shape.getArea(), 0.01);
    }

    @Test
    public void TestSphereArea2() {
        Shape3D shape = new Sphere(0.75);
        assertEquals(7.07, shape.getArea(), 0.01);
    }

    @Test
    public void TestSphereVolume() {
        Shape3D shape = new Sphere(10);
        assertEquals(4188.79, shape.getVolume(), 0.01);
    }

    @Test
    public void TestSphereVolume2() {
        Shape3D shape = new Sphere(0.6);
        assertEquals(0.9, shape.getVolume(), 0.01);
    }
}