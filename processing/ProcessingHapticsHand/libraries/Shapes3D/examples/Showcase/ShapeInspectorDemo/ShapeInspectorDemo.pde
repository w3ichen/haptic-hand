/**
 * ===============================================
 * Shape Inspector Demo
 * ===============================================
 * 
 * In this sketch demonstrates how to use the shape
 * inspector to view some of the attributes of a 3D
 * shape.
 *
 * In this sketch there are two shapes, a Majong 
 * tile (Box) and a pencil (Tube). If you click on
 * one of these shapes details of the shape and the
 * shape part clicked on will appear in the inspector
 * panel. To view other parts of the selected shape 
 * you can use the number keys 0, 1, 2 etc.
 *
 * Also demonstrates
 *  - 3D shape picking
 *  - shape inspector panel
 *  - rotating an image for a texture
 
 *    A Shapes3D library example 
 *    created by Peter Lager 2019
 */

import shapes3d.*;
import shapes3d.contour.*;
import shapes3d.org.apache.commons.math.*;
import shapes3d.org.apache.commons.math.geometry.*;
import shapes3d.path.*;
import shapes3d.utils.*;

private ShapeInspector si;
Shape3D[] shape;
ShapeMover[] mover;

void setup() {
  size(500, 700, P3D);
  cursor(CROSS);
  // Create the two shapes to be displayed
  createShapes();
  // Create the shape inspector panel. The last two
  // parameters specify the position of the panel's
  // top-left corner. The panel's width and height 
  // are fixed.
  si = new ShapeInspector(this, 3, height - 140);
  si.observeShape(shape[0]);
}

void draw() {
  background(0);
  pushMatrix();
  camera(0, 0, 400, 0, 0, 0, 0, 1, 0);
  for (ShapeMover m : mover) {
    m.update();
  }
  for (Shape3D s : shape) {
    s.draw(getGraphics());
  }

  popMatrix();
  // Need to change to 2D rendering for the shape
  // inspector
  hint(DISABLE_DEPTH_TEST);
  si.draw(getGraphics());
  hint(ENABLE_DEPTH_TEST);
}

public void mouseClicked() {
  Picked selected = Shape3D.pick(this, getGraphics(), mouseX, mouseY);
  if (selected != null) {
    si.observeShape(selected.shape, selected.part);
  }
}

/**
 * Just a simple method to create two shapes and shape movers.
 */
public void createShapes() {
  shape = new Shape3D[2];
  mover = new ShapeMover[2];
  // =========================================================================
  // Shape 1 - Mahjong tile
  PImage front = loadImage("reddragontile.png");
  PImage side = loadImage("tileside.png");
  int bkf = color(40, 130, 40);
  int bks = color(20, 70, 20);
  shape[0] = new Box(40, 52, 20);
  shape[0].tag = "Mahjong Tile";
  shape[0].texture(front, S3D.FRONT)
    .texture(Image.rotateCW(side), S3D.LEFT)
    .texture(Image.rotateCCW(side), S3D.RIGHT)
    .texture(Image.flipV(side), S3D.BOTTOM)
    .texture(side, S3D.TOP)
    .drawMode(S3D.TEXTURE, S3D.ALL ^ S3D.BACK)
    .use(S3D.BACK).fill(bkf).stroke(bks).strokeWeight(2).drawMode(S3D.SOLID | S3D.WIRE);
  mover[0] = new ShapeMover(shape[0], 80);
  // =========================================================================
  // Shape 2 - Pencil
  PImage pncl = loadImage("pencilsharp.png");
  int eraser = color(215, 111, 110);
  shape[1] = new Tube(
    new Linear(new PVector(-70, 0, 0), new PVector(70, 0, 0), 5), 
    new Oval(12, 6), 
    new PencilScaler()
    );
  shape[1].tag = "Pencil";
  shape[1].use(S3D.BODY).texture(pncl).uv(0, 1, 0, 6).drawMode(S3D.TEXTURE)
    .use(S3D.END1).fill(eraser).drawMode(S3D.SOLID)
    .visible(false, S3D.END0);
  mover[1] = new ShapeMover(shape[1], 50);
}

/**
 This custom scaler creates 
 a) a linear scale 0.0 to 1.0 for t values 0-0.2scale, and
 b) 1.0 for all t values > 0.2
 
 effectively creating a cone at the start of the tube
 
 */
class PencilScaler implements Scale {

  public float scaleX(float t) {
    return t > 0.2f ? 1 : t / 0.2f;
  }

  public float scaleY(float t) {
    return t > 0.2f ? 1 : t / 0.2f;
  }
}

/**
 * This is a simple class to move the shapes in front 
 * of the user. It serves no other purpose so is probably
 * of little interest to you :-) 
 */
class ShapeMover {
  Shape3D s;
  float rad;

  float angEW, angNS;
  float deltaEW, deltaNS;
  final float lowEW = 0, rangeEW = TWO_PI;
  final float lowNS = 0, rangeNS = TWO_PI;

  float tEW, tNS;

  public ShapeMover(Shape3D s, float rad) {
    this.s = s;
    this.rad = rad;
    tEW = random(TWO_PI);
    tNS = random(TWO_PI);
    deltaEW = (random(0.5f) < 0.5 ? -1 : 1) * random(0.002f, 0.005f);
    deltaNS = (random(0.5f) < 0.5 ? -1 : 1) * random(0.005f, 0.008f);
  }

  /**
   * Update the XYZ position of the shape
   */
  public void update() {
    tEW += deltaEW;
    tNS += deltaNS;
    angEW = (angleLinear(tEW, lowEW, rangeEW) + TWO_PI) % TWO_PI; 
    angNS = (angleCyclic(tNS, lowNS, rangeNS) + TWO_PI) % TWO_PI;  
    float sinEW = sin(angEW);
    float cosEW = cos(angEW);
    //      float sinNS = sin(angNS);
    float cosNS = cos(angNS);
    s.moveTo(
      rad * cosEW, 
      -100 + rad * cosNS, 
      rad * sinEW
      );
    s.rotateBy(deltaEW * 1.0673f, deltaEW * 1.177f, deltaEW * 1.0379f);
  }

  public float angleCyclic(float t, float low, float range) {
    return low + 0.5f * range * (1 + cos(t));
  }

  public float angleLinear(float t, float low, float range) {
    return low + range * t;
  }
}
