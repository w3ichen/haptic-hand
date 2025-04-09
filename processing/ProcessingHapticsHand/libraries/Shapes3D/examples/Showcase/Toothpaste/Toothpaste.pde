/*
 * ===============================================
 * Toothpaste V1.1
 * ===============================================
 * 
 * 
 * This example demonstrates how to use a variety of shapes 
 * to create a 3D scene. Each shape is created in its own 
 * method and has its own comments.
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

float camX, camY, camZ, camAngle, camDist;

Box table_top;
Tube tube, nozzle, paste, cap;
LatheStock nozzle_end;

// change to true to see world space axes
boolean showAxes = false;
// Red axis = +X : Green axis = +Y : Blue axis = +Z
GraphAxes axes = null;

void settings() {
  size(600, 500, P3D);
}

/**
 * The table top is created using a Box. Since we only want to see the 
 * top all other sides are made invisible and only the top is textured.
 */
void createTableTop() {
  System.out.println("\nMAKE TABLE");
  //           box wdith, height, depth,
  table_top = new Box(1400, 2, 1400, 
    //centre the box arround [0,116,0] leave the UP vector unchanged
    new Orientation(new PVector(0, 116, 0), null));
  // make ALL the sides except the TOP invisible
  table_top.visible(false, S3D.ALL ^ S3D.TOP); 
  // Using the top only add a texture and set the texture coordinates
  table_top.use(S3D.TOP).drawMode(S3D.TEXTURE).texture(this, "fabric3.jpg").uv(0, 1.25f, 0, 1.25f);
  table_top.tag = "table top";
}

/**
 * This is the main tube with the "Signal" brand graphics. A Shape3D tube consists
 * of three parts the curved body and two end caps, in this case one end on the 
 * tube is flattened so its end cap is a very narrow ellipse. The cap at the large 
 * end will not be visible because we have the curved closure and nozzle at that end.
 * 
 */
void createSqueezeTubeBody() {
  System.out.println("\nMAKE SQUEEZE TUBE BODY");
  tube = new Tube(
    // Defines the path of the tube's centre-line in 3D space
    //                      start                  end 
    new Linear(new PVector(-400, 0, 0), new PVector(0, 0, 0), 
    // number of slices along tube length
    10, 
    // the orthoganol calculator
    S3D.ORTHO_Y), 
    // X-sectional shape, in this case an oval with X and Y axis 
    // radii the same at 80. The circumference is split into 36 segments (10
    // degrees per segment) to give a smooth surface.
    new Oval(80, 80, 36), 
    // The scaling factor to apply along its length
    // X radius is scaled from 1.05 to 1.0 and the
    // Y radius is scaled from 0.01 to 1.0
    new LinearScale(1.05f, 1, 0.01f, 1)
    );
  tube.use(S3D.BODY).texture(this, "signal.jpg").uv(0, 1, 0, 2).drawMode(S3D.TEXTURE)
    .visible(false, S3D.END1).use(S3D.END0).fill(color(164)).drawMode(S3D.SOLID);
  tube.tag = "Squeeze tube body";
}

/**
 * This is the curved closure at the large end of the squeeze 
 * tube. This is created by rotating a 2D curve (the path) 
 * around the Y axis.
 */
void createTubeBigEndClosure() {
  System.out.println("\nMAKE TUBE BIG END CLOSURE");
  // Start by creating the surface path in this case a 2D Bezier curve is used
  // define the Bezier curve control points. Note I have made sure the start
  // end is of radius 80 to match the squeeze tube
  PVector[] cpoints = new PVector[] { new PVector(80, 0), new PVector(70, -15), 
    new PVector(50, -20), new PVector(15, -25) };
  // Make the Path
  Path tbec_path = new BCurve2D(cpoints, 8);
  // Now make the rotated shape for the closure
  nozzle_end = new LatheStock(
    // Rotate the full 360 degrees about the Y axis in 36 segments
    new LatheSurface(tbec_path, 36), 
    // Orient the shape to fit the end of the squeeze tube
    new Orientation(null, new PVector(-1, 0, 0))
    );
  // Make the shapes end caps invisible
  nozzle_end.visible(false, S3D.END0 | S3D.END1);
  // Texture and texture coordinates for the main surface
  nozzle_end.use(S3D.BODY).texture(this, "closure.jpg").drawMode(S3D.TEXTURE).uv(0, 1, 0, 3);
  nozzle_end.tag = "squeeze tube big end closure";
}

/**
 * This is the nozzle that the paste comes out of, it is threaded 
 * to take the screw-on cap.
 */
void createThreadedNozzle() {
  System.out.println("\nMAKE THREADED NOZZLE");
  nozzle = new Tube(
    // Defines the path of the tube's centre-line in 3D space
    //                      start                  end 
    new Linear(new PVector(0, 0, 0), new PVector(50, 0, 0), 
    // number of slices along length
    1), 
    // but only 15 radius and 18 segments round its circumference
    new Oval(15, 15, 18)
    );
  nozzle.visible(false, S3D.END0 | S3D.END1);
  nozzle.use(S3D.BODY).texture(this, "nthread.jpg").drawMode(S3D.TEXTURE).uv(0, 7, 0, 1);
  nozzle.tag = "threaded nozzle";
}

/**
 * This is the blue screw-on cap is is yet another tube with a linear path.
 */
void createScrewOnCap() {
  System.out.println("\nMAKE SCREW-ON CAP");
  cap = new Tube(
    // Defines the path of the tube's centre-line in 3D space
    //                      start                  end 
    new Linear(new PVector(-200, 90, 300), new PVector(-200, 10, 300), 
    // number of slices along length
    2), 
    // 80 radius and 36 segments to match squeeze tube
    new Oval(80, 80, 36), 
    // add slight taper along the length
    new LinearScale(1, 0.8f, 1, 0.8f)
    );
  cap.drawMode(S3D.TEXTURE, S3D.BODY | S3D.END1).texture(this, "capside.jpg", S3D.BODY).uv(0, 0.4f, 0, 0.4f);
  cap.use(S3D.END1).texture(this, "captop.jpg").uv(0.3f, 0.7f, 0.3f, 0.7f);
  cap.visible(false, S3D.END0);  
  cap.tag = "screw-on cap";
}

/**
 * This is a tube just like the others except that its path is not 
 * linear. Instead it uses a Bezier spline curve to define its 
 * path through 3D space. A Bezier spline is defined by a series 
 * of vertices that it passes through.
 */
void createToothpaste() {
  System.out.println("\nMAKE TOOTHPASTE");
  // First create a lits of 'waypoints' the spline passes through
  // This string holds the waypoint coordinates i.e.
  // {x0,y0,z0,x1,y1,z1,x2...
  String wps = "50,0,0,120,10,0,150,90,0,250,100,40,320,100,160,"
    + "300,100,300,140,100,320,40,100,200,-40,100,0,"
    + "-60,100,-200,0,100,-300,200,100,-300";
  // Now convert the string into an array of PVectors
  String[] sa = wps.split(",");
  PVector[] way_points = new PVector[sa.length / 3];
  for (int i = 0; i < sa.length; i += 3) {
    way_points[i/3] = new PVector(Float.valueOf(sa[i]), Float.valueOf(sa[i+1]), Float.valueOf(sa[i+2]));
  }
  // We are ready to make the tube
  paste = new Tube(
    // Defines the path of the tube's centre-line in 3D space
    new BSpline3D(way_points, 
    //number of slices along length
    100, 
    // the orthogonal calculator
    S3D.ORTHO_Z), 
    new Oval(12, 12, 10)
    );
  paste.visible(false, S3D.END0).use(S3D.END1).fill(color(255), S3D.END1).drawMode(S3D.SOLID, S3D.END1)
    .use(S3D.BODY).texture(this, "stripes.png").drawMode(S3D.TEXTURE).uv(0, 1, 0.15f, 3.15f);
  paste.tag = "toothpaste";
}

public void setup() {
  camDist = 550;
  camAngle = 0;
  createTableTop();
  createSqueezeTubeBody();
  createTubeBigEndClosure();
  createThreadedNozzle();
  createScrewOnCap();
  createToothpaste();
  // Graph axes
  if (showAxes) {
    axes = new GraphAxes(-20, 300, 3);
  }
}

void draw() {
  PGraphics pg = getGraphics();
  camAngle += 0.005f;
  camX = camDist * cos(camAngle);
  camY = -300; //-400; 
  camZ = camDist * sin(camAngle);
  background(32);
  lights();
  ambientLight(50, 50, 50);
  directionalLight(50, 50, 50, 1, 1, 1);
  camera(camX, camY, camZ, 0, 100, 0, 0, 1, 0);
  table_top.draw(pg);
  tube.draw(pg);
  nozzle_end.draw(pg);
  nozzle.draw(pg);
  paste.draw(pg);
  cap.draw(pg);
  if (axes != null) {
    axes.draw(pg);
  }
}

void mouseClicked() {
  Picked selected = Shape3D.pick(this, this.getGraphics(), mouseX, mouseY);
  if (selected != null) {
    System.out.println("You clicked on the " + selected.shape.tag + " after " + (millis()/1000.0f) + " seconds") ;
  } else {
    System.out.println("Missed");
  }
}
