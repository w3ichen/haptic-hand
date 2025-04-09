import shapes3d.*;
import shapes3d.contour.*;
import shapes3d.org.apache.commons.math.*;
import shapes3d.org.apache.commons.math.geometry.*;
import shapes3d.path.*;
import shapes3d.utils.*;

int xaxis, yaxis, zaxis, curve, text, arrow;
float hweight = 1.1, cweight = 1.8;

Extrusion ex;

void setup() {
  size(300, 250, P3D);
  // Get the skin for the xtrusion body surface
  PImage skin = loadImage("bte_stripes.jpg");
  // Colour to be used for ends
  int endCol = color(20, 128, 20);
  // Define a short straight path
  Path path = new Linear(
    new PVector(-50, 0, 0), // start of path
    new PVector(50, 0, 0), // end of path
    5, // number of slices
    new PathQortho()        // custom orthogonal calculator
    );
  // Get the contour / cross-section data
  PVector[] v = getQdata();
  //####################################################################
  // Create the extrusion
  Polygon q = new Polygon(v, S3D.CW, true);
  ex = new Extrusion(path, q);
  ex.tag = "Q";
  ex.use(S3D.BODY)  // Apply attribute commands to main extrusion body only 
    .texture(skin).uv(0, 1, 0, 6)  // add texture and texture coordinates 
    .drawMode(S3D.TEXTURE)  // set the drawining mode
    .use(S3D.END0 | S3D.END1).fill(endCol) // Apply attribute commands to end caps only
    .drawMode(S3D.SOLID); // set the drawing mode
}

void draw() {
  background(0);
  pushMatrix();
  camera(250, 0, -150, 0, 0, 0, 0, 1, 0);
  ex.draw(getGraphics());
  popMatrix();
}

/**
 Read the vertex coordinates used for the cross-section 
 from a text file.
 Each line of the file represents the XY coordinates of one vertex
 separated by a comma.
 For complex cross-sections with many vertices this is better than
 hard coding the coordinates into the sketch. It is more flexible
 and the data more easily edited this way.
 
 The method returns a PVector array that can be used diectly when
 creating the path.
 */
PVector[] getQdata() {
  String[] lines = loadStrings("qcoords.txt");
  PVector[] coords = new PVector[lines.length];
  int n = 0;
  for (String line : lines) {
    String[] c = line.split(",");
    coords[n++] = new PVector( Float.valueOf(c[0]), Float.valueOf(c[1]));
  }
  return coords;
}

/**
 A custom path orthogonal calculator. It corrects an unwanted rotation
 caused by the one Shapes3D decides is best.
 
 In this case the actual value was found by trial and error but you can
 use the dot product to help you find a good value. 
 
 The orthogonal should be at 90 degrees to the tangent so the dot product 
 between the tangent [tx,ty,tz] and the orthogonal [ox,oy,oz] should be
 zero
 
 dot product = (tx * ox) + (ty * oy) + (tz + oz)
 
 In this case we have a linear path so the tangent will the same along 
 its length
 
 tangent = [1,0,0]
 
 so the orthogonal can be any vector [0, oy, oz] where oy and oz can 
 be any value provided they are not both zero because the dot product
 will always be zero e.g.
 
 dot product = (1 * 0) + (0 * oy) + (0 + oz)
 
 By trial and error I came up with the orthogonal [0,1,0]
 */


public static class PathQortho extends PathOrthogonal {

  public PVector getOrthogonal(PVector tangent) {
    return new PVector(0, 1, 0);
  }
}
