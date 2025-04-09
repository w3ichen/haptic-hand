/**
 * ===============================================
 * Shape picking with user defined event handler
 * ===============================================
 * 
 * This sketch has a number of boxes flying about
 * the display. When you click on one of the boxes
 * it changes the colour of the face clicked on.
 *
 * This sketch uses the Processing mouseClicked 
 * function to test whether a box has been clicked
 * on, but an event handler manages the changing of
 * the correct face colour.
 *
 * Notice there is a slight pause on the first click,
 * this is caused by Shapes3D creating the pick 
 * graphics buffer and will not happen again unless
 * you resize the display.
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

Box[] box = new Box[20];
Picked picked = null;
boolean clicked = false;
String s = "";

float bsize, a, d = 50, c = 120;

void settings() {
  size(400, 400, P3D);
} 

void setup() {
  cursor(CROSS);
  for (int i = 0; i < box.length; i++) {
    bsize = 5 + (int)random(12);
    box[i] = new Box(bsize, bsize, bsize);
    box[i].moveTo(random(-d, d), random(-d, d), random(-d, d));
    box[i].rotateTo(random(TWO_PI), random(TWO_PI), random(TWO_PI));
    box[i].fill(randomColor(), S3D.FRONT);
    box[i].fill(randomColor(), S3D.BACK);
    box[i].fill(randomColor(), S3D.TOP);
    box[i].fill(randomColor(), S3D.BOTTOM);
    box[i].fill(randomColor(), S3D.LEFT);
    box[i].fill(randomColor(), S3D.RIGHT);
    box[i].stroke(color(64, 0, 64));
    box[i].strokeWeight(1.2);
    box[i].drawMode(S3D.SOLID | S3D.WIRE);
    box[i].tag = "Box " + i;
    box[i].tagNo = i;
    // Add the event handler method to this box
    box[i].addPickHandler(this, "shapePicker");
  }
}

void draw() {
  background(128);
  pushMatrix();
  a += 0.005;
  camera(c * sin(a), 10, c * cos(a), 0, 0, 0, 0, 1, 0);
  for (int i = 0; i < box.length; i++) {
    box[i].draw(getGraphics());
  }
  popMatrix();
  // Display a status bar and show the results from the
  // last shape pick operation (see mouseClicked method)
  fill(200, 255, 200);
  textAlign(CENTER, CENTER);
  text(s, 0, height-20, width, 20);
}

void mouseClicked() {
  // See if we have clicked on a shape. We don't have to store
  // the return Picked object because all the boxes have an event
  // handler.
  Shape3D.pick(this, getGraphics(), mouseX, mouseY);
}

// This event handler is only called when a shape has been picked.
void shapePicker(Shape3D shape3d, int part, int flag) {
  // shape3d will never be null
  shape3d.fill(randomColor(), flag);
  s = shape3d.tag + "  part no. "  + part + "  part flag " + binary(flag, 8);
}

int randomColor() {
  return color(random(100, 220), random(100, 220), random(100, 220));
}