/**
 * Renderer.pde
 * 
 * Contains the SimpleFinger class and drawing functions for the scene.
 */

// Origin point for the coordinate system (can be defined here or main sketch)
final PVector origin = new PVector(0, 0, 0);

/**
 * Draws the entire scene if data is available.
 */
void drawScene() {
  if (!dataReceived) {
    // Optional: Draw a loading message or placeholder
    fill(255);
    textAlign(CENTER, CENTER);
    text("Waiting for data...", 0, 0); // Centered text because PeasyCam centers the view
    return;
  }
  
  // Set lights
  ambientLight(100, 100, 100);
  pointLight(255, 255, 255, 0, -200, 200); // Light from above-front
  directionalLight(150, 150, 150, 0.5, 1, -1); // Angled light
  
  // Draw elements
  drawCoordinateSystem(100);
  drawFingers();
  drawObject();
}

/**
 * Draws X, Y, Z coordinate axes.
 */
void drawCoordinateSystem(float axisLength) {
  strokeWeight(2);
  // X axis (red)
  stroke(255, 0, 0);
  line(0, 0, 0, axisLength, 0, 0);
  // Y axis (green) - Processing's Y is typically down in 2D, but up in 3D default
  stroke(0, 255, 0);
  line(0, 0, 0, 0, -axisLength, 0); // Draw negative Y to point upwards
  // Z axis (blue) - Towards the viewer
  stroke(0, 0, 255);
  line(0, 0, 0, 0, 0, axisLength);
  strokeWeight(1);
  noStroke(); // Turn off stroke for shapes unless needed
}

/**
 * Draws the fingers based on current end positions.
 */
void drawFingers() {
  SimpleFinger thumb = new SimpleFinger(origin, thumb_end);
  SimpleFinger index = new SimpleFinger(origin, index_end);
  SimpleFinger middle = new SimpleFinger(origin, middle_end);
  
  thumb.draw();
  index.draw();
  middle.draw();
}

/**
 * Draws the object as a sphere.
 */
void drawObject() {
  pushMatrix();
  translate(object_position.x, object_position.y, object_position.z);
  noStroke();
  fill(200, 200, 255, 200); // Light blue, slightly transparent
  sphere(object_radius);
  popMatrix();
}

/**
 * Simplified Finger class that uses basic Processing shapes.
 */
class SimpleFinger {
  PVector start, end;
  float radius;
  int sides = 12; // Increased sides for smoother cylinder
  
  SimpleFinger(PVector start, PVector end) {
    this.start = start;
    this.end = end;
    this.radius = FINGER_RADIUS; // Use configured radius
  }
  
  void draw() {
    // Draw the finger as a cylinder with spheres at ends
    noStroke(); // Generally no stroke for fingers
    fill(255, 180, 180); // Light pink color for fingers
    
    // Draw spheres at start and end
    pushMatrix();
    translate(start.x, start.y, start.z);
    sphere(radius);
    popMatrix();
    
    pushMatrix();
    translate(end.x, end.y, end.z);
    sphere(radius);
    popMatrix();
    
    // Draw cylinder connecting the spheres
    drawCylinder(start, end, radius * 0.8); // Make cylinder slightly thinner
  }
  
  // Helper function to draw a cylinder between two points
  void drawCylinder(PVector p1, PVector p2, float r) {
    PVector center = PVector.lerp(p1, p2, 0.5);
    float len = PVector.dist(p1, p2);
    
    if (len < 0.1) return; // Avoid drawing zero-length cylinder
    
    // Calculate rotation axis and angle
    PVector diff = PVector.sub(p2, p1);
    diff.normalize(); // Normalize for angle calculation
    
    PVector rotAxis = new PVector(0, 1, 0).cross(diff);
    float rotAngle = PVector.angleBetween(new PVector(0, 1, 0), diff);
    
    pushMatrix();
    translate(center.x, center.y, center.z);
    // Check if axis is near zero vector (collinear cases)
    if (rotAxis.magSq() > 0.001) {
        rotate(rotAngle, rotAxis.x, rotAxis.y, rotAxis.z);
    } else if (diff.y < 0) { 
        // If pointing directly down (-Y), rotate 180 degrees around X or Z
        rotate(PI, 1, 0, 0); 
    }
    // If pointing directly up (+Y), no rotation needed
    
    // Draw the cylinder body using a quad strip for better lighting
    beginShape(QUAD_STRIP);
    for (int i = 0; i <= sides; i++) {
      float angle = TWO_PI * i / sides;
      float x = cos(angle) * r;
      float z = sin(angle) * r;
      // Define normals for lighting: points outwards from the cylinder axis
      normal(cos(angle), 0, sin(angle)); 
      vertex(x, len/2, z);  // Top vertex
      vertex(x, -len/2, z); // Bottom vertex
    }
    endShape();
    
    // Optional: Draw caps (if needed, requires different shape mode)
    // beginShape(TRIANGLE_FAN); ... endShape(); for top and bottom
    
    popMatrix();
  }
} 