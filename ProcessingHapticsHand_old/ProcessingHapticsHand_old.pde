/**
 * ProcessingHapticsHand.pde
 * 
 * A simplified version of the haptic hand interface visualization
 * using Processing's built-in 3D functions instead of the shapes3d library.
 */

import processing.serial.*;
import processing.event.*;
Serial myPort;  // Create object from Serial class

float[] vals = {};
boolean dataReceived = false;
int sayHiForFirstTime = 0;
byte [] messageBuffer = new byte[100];
int messageSize = 0;

// Window dimensions for the 3D visualization
final int windowlength = 800;
final int windowwidth = 800;

// Origin point for the coordinate system
final PVector origin = new PVector(0, 0, 0);

// Finger end positions received from the Nucleo board
PVector thumb_end;
PVector index_end;
PVector middle_end;

// Object properties for visualization
PVector object_position;
float object_radius;

// Simulation mode variables
boolean simulationMode = false;  // Set to true to use simulated data
float simulationTime = 0;       // Time counter for simulation
float simulationSpeed = 0.02;   // Speed of the simulation

// Camera control variables
float rotationX = PI/6;
float rotationY = 0;
float cameraZ = -200;
float panX = 0;
float panY = 0;
PVector lastMouse = new PVector(0, 0);

void settings() {
  size(windowlength, windowwidth, P3D);
}

void setup() {
  // Initialize PVectors
  thumb_end = new PVector(0, 0, 0);
  index_end = new PVector(0, 0, 0);
  middle_end = new PVector(0, 0, 0);
  object_position = new PVector(0, 0, 0);
  object_radius = 30;
  
  if (!simulationMode) {
    String portName = Serial.list()[8];
    println(portName);
    myPort = new Serial(this, portName, 115200);
  }
}

/**
 * Simplified Finger class that uses basic Processing shapes
 */
class SimpleFinger {
  PVector start, end;
  float radius;
  
  SimpleFinger(PVector start, PVector end) {
    this.start = start;
    this.end = end;
    this.radius = 10;  // Default finger radius
  }
  
  void draw() {
    // Draw the finger as a cylinder with spheres at ends
    stroke(200);
    fill(25, 20, 20);  // Light pink color for fingers
    
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
    drawCylinder(start, end, radius/2);
  }
  
  // Helper function to draw a cylinder between two points
  void drawCylinder(PVector p1, PVector p2, float radius) {
    PVector center = PVector.add(p1, p2).mult(0.5);
    float len = PVector.dist(p1, p2);
    
    // Calculate rotation axis and angle
    PVector diff = PVector.sub(p2, p1);
    PVector axis = new PVector(0, 1, 0).cross(diff);
    float angle = PVector.angleBetween(new PVector(0, 1, 0), diff);
    
    pushMatrix();
    translate(center.x, center.y, center.z);
    rotate(angle, axis.x, axis.y, axis.z);
    
    float sides = 8;  // Number of sides for the cylinder
    beginShape(TRIANGLE_STRIP);
    for (float i = 0; i <= sides; i++) {
      float angle2 = TWO_PI * i / sides;
      float x = cos(angle2) * radius;
      float z = sin(angle2) * radius;
      vertex(x, len/2, z);
      vertex(x, -len/2, z);
    }
    endShape();
    popMatrix();
  }
}

void generateSimulatedData() {
  // Update simulation time
  simulationTime += simulationSpeed;
  
  // Simulate finger movements in a circular pattern
  float radius = 100;
  float baseZ = 200;
  
  // Thumb movement
  thumb_end = new PVector(
    radius * cos(simulationTime),
    radius * sin(simulationTime),
    baseZ + 50 * sin(simulationTime * 0.5)
  );
  
  // Index finger movement (slightly different phase)
  index_end = new PVector(
    radius * cos(simulationTime + 1),
    radius * sin(simulationTime + 1),
    baseZ + 50 * sin(simulationTime * 0.5 + 1)
  );
  
  // Middle finger movement (different phase)
  middle_end = new PVector(
    radius * cos(simulationTime + 2),
    radius * sin(simulationTime + 2),
    baseZ + 50 * sin(simulationTime * 0.5 + 2)
  );
  
  // Simulate object movement
  float objectRadius = 150;
  object_position = new PVector(
    objectRadius * cos(simulationTime * 0.5),
    objectRadius * sin(simulationTime * 0.5),
    baseZ + 100
  );
  object_radius = 30;
}

void draw() {
  background(0);  // Light gray background
  
  // Apply camera transformations
  translate(width/2 + panX, height/2 + panY, cameraZ);
  rotateX(rotationX);
  rotateY(rotationY);
  
  // Draw coordinate system for reference
  strokeWeight(2);
  stroke(255, 0, 0); line(0, 0, 0, 100, 0, 0);  // X axis (red)
  stroke(0, 255, 0); line(0, 0, 0, 0, 100, 0);  // Y axis (green)
  stroke(0, 0, 255); line(0, 0, 0, 0, 0, 100);  // Z axis (blue)
  strokeWeight(1);
  
  if (simulationMode) {
    generateSimulatedData();
  } else if (myPort != null) {
     //Serial communication code remains the same
    if (sayHiForFirstTime == 0) {
      myPort.write("1l");
      delay(10);
      sayHiForFirstTime = 1;
    }

    myPort.write("3l");
    delay(10);
    //println("here0");
    if (myPort.available() > 0) {
      //println("here1");
      messageSize = myPort.readBytes(messageBuffer);
      if (messageSize > 0) {
        //println("here2");
        String messageString = new String(messageBuffer);
        println(messageString);
        vals = float(splitTokens(messageString, "\t"));
        print("Received: ");
        println(vals);
        thumb_end = new PVector(vals[6], vals[7], vals[8]);
        println(thumb_end);
        index_end = new PVector(vals[3], vals[4], vals[5]);
        println(index_end);
        middle_end = new PVector(vals[0], vals[1], vals[2]);
        println(middle_end);
        object_position = new PVector(vals[9], vals[10], vals[11]);
        object_radius = vals[12];
        myPort.write("1l");
        delay(10);
      }
    }
  }

  // Draw fingers using simplified finger class
  SimpleFinger thumb = new SimpleFinger(origin, thumb_end);
  SimpleFinger index = new SimpleFinger(origin, index_end);
  SimpleFinger middle = new SimpleFinger(origin, middle_end);
  
  thumb.draw();
  index.draw();
  middle.draw();

  //// Draw object as a sphere
  //pushMatrix();
  //translate(object_position.x, object_position.y, object_position.z);
  //stroke(150);
  //fill(200, 200, 255);  // Light blue color for object
  //sphere(object_radius);
  //popMatrix();
}

void mouseDragged() {
  float deltaX = mouseX - lastMouse.x;
  float deltaY = mouseY - lastMouse.y;
  
  if (mouseButton == LEFT) {
    rotationY += deltaX * 0.01;
    rotationX += deltaY * 0.01;
  }
  else if (mouseButton == RIGHT || mouseButton == CENTER) {
    panX += deltaX;
    panY += deltaY;
  }
  
  lastMouse.set(mouseX, mouseY);
}

void mousePressed() {
  lastMouse.set(mouseX, mouseY);
}

void mouseWheel(MouseEvent event) {
  float delta = event.getCount();
  cameraZ += delta * 50;  // Zoom in/out
} 
