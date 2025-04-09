/**
 * ===============================================
 * Creating a custom scaler
 * ===============================================
 * 
 * This sketch is a simple modification of the tube
 * example. The main difference is the addition of 
 * a custom scaler that causes the tube to taper at 
 * one end.
 * The texture image had to be modified and the end
 * cap at the sharp end is made invisible because 
 * its radius is zero.
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

//int xaxis, yaxis, zaxis, curve, text, arrow;
//float hweight = 1.1, cweight = 1.8;

float ax, ay, az;
String s = "";

Tube shape;

void setup() {
  size(300, 250, P3D);
  cursor(CROSS);
  PImage pncl = loadImage("pencilsharp.png");
  int eraser = color(215, 111, 110);
  // Use a linear path for the tube
  Path path = new Linear(new PVector(-70, 0, 0), new PVector(70, 0, 0), 5);
  // Create a hexagonal cross-section of radius 20
  Oval hexagon = new Oval(20.0, 6);
  // Create scaler
  Scale scale = new PencilScale();
  //####################################################################
  // Create the tube
  shape = new Tube(path, hexagon, scale);
  shape.tag = "Pencil";
  // Apply the rendering attributes
  shape
    .use(S3D.BODY) // Apply attribute commands to main tube body only
    .texture(pncl).uv(0, 1, 0, 6) // add texture and texture coordinates 
    .drawMode(S3D.TEXTURE) // set the drawining mode
    .visible(false, S3D.END0) // hide end cap at pointed end
    .use(S3D.END1)  // Apply attribute commands to eraser end only
    .fill(eraser).drawMode(S3D.SOLID); // set fill color and drawmode

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
  // context so we view the shape from different 
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
  // Display a status bar and show the results from the
  // last shape pick operation (see mouseClicked method)
  fill(0, 64, 0);
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

/**
 This custom scaler creates 
 a) a linear scale 0.0 to 1.0 for t values 0-0.2scale, and
 b) 1.0 for all t values > 0.2
 
 effectively creating a cone at the start of the tube
 
 */
class PencilScale implements Scale {

  public float scaleX(float t) {
    return t <= 0.2 ? t / 0.2 : 1;
  }

  public float scaleY(float t) {
    return t <= 0.2 ? t / 0.2 : 1;
  }
}
