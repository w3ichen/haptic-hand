/**
 * ===============================================
 * Shape picking in a selection area (marquee)
 * ===============================================
 * 
 * This sketch demonstrates how you can use a 
 * marquee selection box and find all shapes/shape 
 * parts inside the selection rectangle.
 * 
 * Simple click and drag a selection area, when you
 * release the mouse button all box faces inside the
 * selection area will be given a new random colour.
 * 
 * Notice there is a slight pause on first use,
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

float bsize, a, d = 50, c = 120;

// Marquee variables
int mx0, my0, mx1, my1;
boolean mvisible = false;

void settings() {
  size(400, 400, P3D);
}

void setup() {
  cursor(CROSS);
  for (int i = 0; i < box.length; i++) {
    bsize = 5 + (int)random(12);
    box[i] = new Box(bsize, bsize, bsize);
    box[i].moveTo(random(-d, d), random(-d, d), random(-d, d));
    box[i].fill(randomColor());
    box[i].stroke(color(64, 0, 64));
    box[i].strokeWeight(1.2f);
    box[i].drawMode(S3D.SOLID | S3D.WIRE);
    box[i].tag = "#" + i;
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
  if (mvisible) {
    hint(DISABLE_DEPTH_TEST);
    stroke(255);
    strokeWeight(2);
    fill(255, 60);
    rectMode(CORNERS);
    rect(mx0, my0, mx1, my1);
    rectMode(CORNER);
    hint(ENABLE_DEPTH_TEST);
  }
}

public void mousePressed() {
  mx0 = mx1 = mouseX;
  my0 = my1 = mouseY;
  mvisible = true;
}

public void mouseDragged() {
  mx1 = mouseX;
  my1 = mouseY;
}

void mouseReleased() {
  Picked[] ms = Shape3D.pick(this, getGraphics(), mx0, my0, mx1, my1);
  int c = randomColor();
  for (Picked p : ms) {
    p.shape.fill(c, p.partFlag);
    System.out.println(p.shape.tag + " - face: " + p.part);
  }
  System.out.println("---------------------------------");
  mvisible = false;
}

int randomColor() {
  return color(random(100, 220), random(100, 220), random(100, 220));
}
