/**
 * ===============================================
 * LatheStock demo
 * ===============================================
 * 
 * This sketch creates a vase decorated like a fish 
 * tank. The lathe surface is created using a
 * Bezier curve of order 5 (i.e. 5 control points).
 * End caps are created automatically with this shape
 * but in this example the top end cap is made 
 * invisible.
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

LatheStock shape;

void setup() {
  size(300, 250, P3D);
  cursor(CROSS);

  // The control points to be used for the lathe surface 
  PVector[] v = new PVector[] {
    new PVector(100, 150), 
    new PVector(120, 100), 
    new PVector(60, 20), 
    new PVector(60, -20), 
    new PVector(80, -150), 
  };
  // Use a Bezier curve path to define the lathe surface path for the tube
  Path path = new BCurve3D(v, 30);
  // Create the lathe surface
  LatheSurface surface = new LatheSurface(path, 36);
  // Create the lathe stock (vase)
  shape = new LatheStock(surface);
  shape.tag = "Vase";
  // Apply the rendering attributes
  PImage skin = loadImage("fishtanktexture.jpg");
  skin = Image.rotateCCW(skin); // rotate image 90 degreess

  shape
    .use(S3D.BODY) // Apply attribute commands to main tube body only
    .texture(skin).uv(0, 1, 0, 1) // add texture and texture coordinates 
    .drawMode(S3D.TEXTURE) // set the drawining mode
    .use(S3D.END0)  // Apply attribute commands to eraser end only
    .fill(color(243, 211, 126)).stroke(color(120, 105, 63)) // set fill & stroke colors
    .drawMode(S3D.SOLID | S3D.WIRE) // set fill color and drawmode
    .visible(false, S3D.END1);


  textSize(14);
  textAlign(CENTER, CENTER);
}

void draw() {
  background(60);
  pushMatrix();
  camera(0, 0, 350, 0, 0, 0, 0, 1, 0);
  // The next few lines rotate the graphics 
  // context so we view the shape from dfiierent 
  // angles making it appear to be tumbling.
  ax += 0.0043;
  ay += 0.0093;
  az += 0.0079;
  rotateX(ax);
  rotateY(ay);
  rotateZ(az);

  // Render the shape on the main display area
  shape.draw(getGraphics());

  popMatrix();
}
