/**
 * ===============================================
 * Extrusion with shape picking
 * ===============================================
 * 
 * This sketch creates an extrusion with a concave 
 * cross-section. The main body is textured but the 
 * ends are solid colour.
 * The sketch shows how you can rotate the vertices
 * of the contour which is useful if the orthogonal
 * calculation produces unwanted rotation about the
 * shape's length.
 *
 * Also demonstrates
 *  - 3D shape picking
 *  - rotating the contour vertices
 * 
 *    A Shapes3D library example 
 *    created by Peter Lager 2019
 */

import shapes3d.*;
import shapes3d.contour.*;
import shapes3d.org.apache.commons.math.*;
import shapes3d.org.apache.commons.math.geometry.*;
import shapes3d.path.*;
import shapes3d.utils.*;

float ax, ay, az;
String s = "";

Extrusion shape;

void setup() {
  size(300, 250, P3D);
  cursor(CROSS);
  // The texture to be used on the main body of the extrusion
  PImage skin = loadImage("qavatar.png");
  // The vertices for the cross-section
  PVector[] v = new PVector[] {
    new PVector(0.75f, -1f), // 0
    new PVector(0.25f, -1f), // 1
    new PVector(0.5f, -0.5f), // 2
    new PVector(0f, 0.25f), // 3
    new PVector(-0.5f, 0.25f), // 4
    new PVector(-0.25f, 1f), // 5
    new PVector(0.75f, 1f), // 6
  };
  // Rotate the contour vertices 90 degrees clockwise to get rid of an
  // unwanted rotation
  v = Contour.rotateCW(v);
  // Use a spiral path for the extrusion
  Path path = new Spiral(80, 50, // radius of orthogonal axis of rotation
    2.75f, // Number of twirls
    52, // twirl pitch
    80 // number of slices along spiral length
    );
  // Create a hexagonal cross-section of radius 20
  Polygon xsection = new Polygon(v, S3D.CCW, true);
  Scale scale = new LinearScale(15, 15, 15, 15);
  // Create the tube
  shape = new Extrusion(path, xsection, scale);
  shape.tag = "My Extrusion";
  // Apply the rendering attributes
  shape
    .use(S3D.BODY) // Apply attribute commands to main tube body only
    .texture(skin).uv(0, 9, 0, 1) // add texture and texture coordinates 
    .drawMode(S3D.TEXTURE) // set the drawing mode
    .use(S3D.END0 | S3D.END1) // Apply attribute commands to both ends
    .fill(color(0,128,0)).drawMode(S3D.SOLID); // set fill color and drawmode

  textSize(14);
  textAlign(CENTER, CENTER);
}

void draw() {
  background(250, 250, 240);
  pushMatrix();
  // Move the world view coordinates [0,0,0] 
  // to the centre of the display.
  translate(width/2, height/2);
  // The next few lines rotate the graphics 
  // context so we view the shape from dfiierent 
  // angles making it appear to be tumbling.
  ax += 0.0033;
  ay += 0.0083;
  az += 0.0069;
  rotateX(ax);
  rotateY(ay);
  rotateZ(az);

  // Render the shape on the main display area
  shape.draw(getGraphics());

  popMatrix();
  // Display a status bar and show the results from the
  // last shape pick operation (see mouseClicked method)
  hint(DISABLE_DEPTH_TEST);
  fill(0, 64, 0);
  rect(0, height-20, width, 20);
  textAlign(CENTER, CENTER);
  fill(100, 255, 100);
  text(s, 0, height-20, width, 20);
  hint(ENABLE_DEPTH_TEST);
}

void mouseClicked() {
  // If te mouse is clicked see if the cursor is over a shape
  // if so show details of the shape and shape part clicked on
  Picked p = Shape3D.pick(this, getGraphics(), mouseX, mouseY);
  if (p != null) {
    // Mouse cursor was over a shape
    s = p.shape.tag + "  part no. "  + p.part + " picked";
  } else {
    // Mouse cursor was not over a shape
    s = "Missed";
  }
  println(millis() + "\t" + s);
}
