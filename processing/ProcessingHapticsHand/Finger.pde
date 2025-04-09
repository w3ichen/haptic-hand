/**
 * Finger.pde
 * 
 * A class that represents a finger in 3D space using the shapes3d library.
 * Each finger is modeled as a curved tube with a spherical end cap.
 */

//use shapes3d library
import shapes3d.*;

/**
 * Finger class
 * Represents a finger with a start point, end point, and radius
 */
class Finger {
  // Start and end points of the finger
  PVector start, end;
  
  // Default radius for the finger tube
  float radius;
  
  // Amount of flex in the middle of the finger
  float flex_amount = 2.0;
  
  // Direction vector for the flex
  PVector flex_direction = new PVector(0, 0, 1);
  
  // 3D curve representing the finger's path
  BCurve3D path;
  
  // Cross-section shape of the finger
  Oval xsection;

  /**
   * Constructor with custom radius
   * @param start Starting point of the finger
   * @param end Ending point of the finger
   * @param radius Radius of the finger tube
   */
  Finger(PVector start, PVector end, float radius) {
    this.start = start;
    this.end = end;
    this.radius = radius;
  }

  /**
   * Constructor with default radius
   * @param start Starting point of the finger
   * @param end Ending point of the finger
   */
  Finger(PVector start, PVector end) {
    this.start = start;
    this.end = end;
    this.radius = 2.0;
  }

  /**
   * Draws the finger as a curved tube with a spherical end cap
   * The finger is created using a Bezier curve with three control points:
   * 1. Start point
   * 2. Middle point with flex
   * 3. End point
   */
  void draw() {
    // Create control points for the Bezier curve
    PVector[] points = new PVector[3];
    points[0] = start;
    points[1] = PVector.add(PVector.lerp(start, end, 0.5), PVector.mult(flex_direction, flex_amount));
    points[2] = end;
    
    // Number of segments for the tube
    int nbr_slices = 2;
    int nbr_sides = 9;
    
    // Create the 3D curve and cross-section
    path = new BCurve3D(points, nbr_slices);
    xsection = new Oval(radius, nbr_sides);

    // Draw the finger tube
    Tube finger = new Tube(path, xsection);
    finger.draw(g);

    // Draw the finger tip using Shapes3D sphere
    Ellipsoid tip = new Ellipsoid(radius, radius, radius, nbr_sides, nbr_sides, new Orientation(new PVector(0,0,0), null));
    tip.draw(g);
  }
}
