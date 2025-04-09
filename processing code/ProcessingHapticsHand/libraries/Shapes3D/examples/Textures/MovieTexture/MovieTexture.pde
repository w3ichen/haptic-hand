/**
 * ===============================================
 * Lathe shape with movie texture
 * ===============================================
 * 
 * This sketch creates a 'vase' shape using a 
 * LatheStock object. The texture is created from 
 * a movie but with the default uv coordinates it
 * would appear at right angles to the case base.
 * 
 * To make the movie appear 'on the vase side' 
 * the uv coordinates are transformed using the
 * uvt(...) method. (see line 48)
 * 
 *    A Shapes3D library example 
 *    created by Peter Lager 2019
 */

import processing.video.*;

import shapes3d.*;
import shapes3d.contour.*;
import shapes3d.org.apache.commons.math.*;
import shapes3d.org.apache.commons.math.geometry.*;
import shapes3d.path.*;
import shapes3d.utils.*;

Movie fishes;
LatheStock shape;
float a = 0;

void setup() {
  size(600, 450, P3D);
  fishes = new Movie(this, "fishtank2.mp4");
  fishes.loop();
  PVector[] v = new PVector[] {
    new PVector(100, 150), 
    new PVector(120, 100), 
    new PVector(60, 20), 
    new PVector(60, -20), 
    new PVector(80, -150), 
  };
  Path path =  new BCurve3D(v, 30);
  LatheSurface surface = new LatheSurface(path, 36);

  shape = new LatheStock(surface);
  shape.use(S3D.BODY)
    .uvt(S3D.ROT_270) // Transform uv coordinates by rotating them 270 degrees
    .uv(0, 2, 0, 1)
    .movie(this, fishes)
    .drawMode(S3D.TEXTURE);
  shape.use(S3D.END0 | S3D.END1)
    .drawMode(S3D.SOLID);
}

void draw() {
  background(0);
  camera(0, 100, 400, 0, 0, 0, 0, 1, 0);
  a += 0.003;
  rotateY(a);
  shape.draw(getGraphics());
}