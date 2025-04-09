/**
 * ===============================================
 * Simple box with shape pciking
 * ===============================================
 * 
 * This sketch creates a box with the 3 orthogonal
 * side os different length. It uses the default 
 * attributes where every side is a different colour. 
 *
 * Also demonstrates
 *  - 3D shape picking
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

Box shape;

void setup() {
  size(300, 300, P3D);
  cursor(CROSS);
  //       (width, height, depth)
  shape = new Box(
    180,    // width
    100,    // height
    40      // depth
    );
}

void draw() {
  background(0);
  pushMatrix();
  // Move the world view coordinates [0,0,0] 
  // to the centre of the display.
  translate(width/2, height/2);
  // The next few lines rotate the graphics 
  // context so we view the shape from dfiierent 
  // angles making it appear to be tumbling.
  ax += 0.0063;
  ay += 0.0123;
  az += 0.0099;
  rotateX(ax);
  rotateY(ay);
  rotateZ(az);

  // Render the shape on the main display area
  shape.draw(getGraphics());

  popMatrix();
  // Display a status bar and show the results from the
  // last shape pick operation (see mouseClicked method)
  fill(200, 255, 200);
  textAlign(CENTER, CENTER);
  text(s, 0, height-20, width, 20);
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
