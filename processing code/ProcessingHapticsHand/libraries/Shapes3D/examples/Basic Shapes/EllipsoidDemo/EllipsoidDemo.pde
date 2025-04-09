/**
 * ===============================================
 * Simple ellipsoid with texture
 * ===============================================
 * 
 * This sketch creates a simple ellipsoid to 
 * represent the planet Earth. The ellipsoid
 * is animated by rotating about the Y axis.
 *
 * Also demonstrates
 *  - using texture mmode
 *  - rotating a shape about its own axis
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

Ellipsoid shape;

void setup() {
  size(300, 300, P3D);
  cursor(CROSS);

  shape = new Ellipsoid(
    100, 80, 100, // 3 orthogonal radii
    24,           // number of segments (in XZ plane)
    12            // number of slices along Y axis
    );

  shape
    .texture(this, "earth.jpg")  // load and set the texture for this shape
    .drawMode(S3D.TEXTURE);       // make sure the shape is rendered using the texture
}

void draw() {
  background(0);
  pushMatrix();
  // Move the world view coordinates [0,0,0] 
  // to the centre of the display.
  translate(width/2, height/2);
  // Rotate the graphics context so it appears we 
  // are looking down from somewhere in the northern 
  // hemisphere
  rotateX(-0.6);
  rotateZ(-0.1);

  // Rotate shape about the y axis so it looks like the
  // Earth is revolving on its axis.
  shape.rotateBy(0, 0.01, 0);
  // Render the shape on the main display area
  shape.draw(getGraphics());

  popMatrix();
}
