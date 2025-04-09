/**
 * ===============================================
 * Simple box with texture animation
 * ===============================================
 * 
 * This sketch shows how to change the texture 
 * coordinates every frame thus animating the 
 * texture.
 *
 * The key method is updateUV(float), the comments 
 * on that method explains how it works.
 *
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

Box b;
float u, a = 0;

void setup() {
  size(300, 300, P3D);
  surface.setTitle("Animation using texture coordinates");
  // Now create the 3D box
  b = new Box(228, 100, 72);
  // Set the top and box faces as solid color
  b.drawMode(Box.SOLID, S3D.TOP | S3D.BOTTOM)
    .fill(color(120, 120, 240), S3D.TOP)
    .fill(color(60, 100, 60), S3D.BOTTOM);  
  // Set the other four sides to show the texture
  b.use(S3D.FRONT | S3D.RIGHT | S3D.BACK | S3D.LEFT)
    .texture(this, "london360.jpg")
    .drawMode(S3D.TEXTURE);
  // Initialise the uv coordinates for the four textured sides
  u = 0;
  updateUV(u);
}

void draw() {
  u = (u + 0.002) % 1.0f;
  updateUV(u);
  a -= 0.005;
  background(240, 240, 255);
  camera(0, -100, 300, 0, 0, 0, 0, 1, 0);
  b.draw(getGraphics());
  b.rotateToY(a);
}

/**
 The aspect ratio of the image is 6:1 so to keep that ratio
 the perimeter of the box must be six times it's height so the 
 the box was created width = 232, depth = 72 and height = 100 
 so that
           2 * (width + depth) = 6 * height
 To wrap the texture round the box without distorting the image
 the u coordinate at each corner must be calculated. 

   U_______U+0.12_________u+0.5____U+0.62_________U+1.0
   |        |               |       |              |
   | LEFT   |     FRONT     | RIGHT |    BACK      |
   |        |               |       |              |
   |________|_______________|_______|______________|
 
 To animate the texture we increment u evry frame but keep it 
 in the range 0.0 - 1.0 inclusive.
*/
void updateUV(float u) {
  b.uv(u, u + 0.12f, 0, 1, S3D.LEFT);
  b.uv(u + 0.12f, u + 0.5f, 0, 1, S3D.FRONT);
  b.uv(u + 0.5f, u + 0.62f, 0, 1, S3D.RIGHT);
  b.uv(u + 0.62f, u + 1f, 0, 1, S3D.BACK);
}