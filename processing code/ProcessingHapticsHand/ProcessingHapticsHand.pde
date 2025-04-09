/**
 * ProcessingHapticsHand.pde
 * 
 * This sketch visualizes a haptic hand interface in 3D space using Processing.
 * It communicates with a Nucleo board to receive real-time finger position data
 * and displays a virtual environment with fingers and an interactive object.
 */

import processing.serial.*;
import processing.event.*;
Serial myPort;  // Create object from Serial class

float[] vals = {};
boolean dataReceived = false;
byte [] messageBuffer = new byte[100];
int messageSize = 0;

String serial_list;                // list of serial ports
int serial_list_index = 0;         // currently selected serial port 
int num_serial_ports = 0;          // number of serial ports in the list
String portInfo;

// Window dimensions for the 3D visualization
final int windowlength = 800; //these have to match the window width and length declared in size
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

// Flag to ensure initial handshake is only sent once
int sayHiForFirstTime = 0;

// Simulation mode variables
boolean simulationMode = true;  // Set to true to use simulated data
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

/**
 * Initializes the sketch, sets up the window and serial communication
 */
void setup()
{
  // Initialize PVectors
  thumb_end = new PVector(0, 0, 0);
  index_end = new PVector(0, 0, 0);
  middle_end = new PVector(0, 0, 0);
  object_position = new PVector(0, 0, 0);
  object_radius = 30;
  
  if (!simulationMode) {
    String portName = Serial.list()[8];
    myPort = new Serial(this, portName, 9600);
  }
}

/**
 * Generates simulated data for testing purposes
 */
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

/**
 * Main draw loop that handles:
 * 1. Serial communication with the Nucleo board
 * 2. Data parsing and processing
 * 3. 3D visualization of fingers and object
 */
void draw() 
{
  background(200);  // Light gray background
  
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
    //background(255,255,255);
  
    //say hi to Nucleo
    if (sayHiForFirstTime ==0) {
      myPort.write("1l");
      delay(10);
      sayHiForFirstTime = 1;
    }

    //println("req");
    //request Data
    myPort.write("3l"); //send message to request data from Nucleo
    delay(10);

    //check if data is available:
    if ( myPort.available() > 0) {  // If data is available, and have received all of it!
      messageSize = myPort.readBytes(messageBuffer);
    
      //if message isn't empty:
      if (messageSize > 0) {
        String messageString = new String(messageBuffer);
        //split the message into values
        vals = float(splitTokens(messageString, "\t"));
        //load the thumb, index, and middle finger end positions
        thumb_end = new PVector(vals[0], vals[1], vals[2]);
        index_end = new PVector(vals[3], vals[4], vals[5]);
        middle_end = new PVector(vals[6], vals[7], vals[8]);
        //load the object position and radius
        object_position = new PVector(vals[9], vals[10], vals[11]);
        object_radius = vals[12];
        //just received data, send acknowledgment:
        myPort.write("1l");
        delay(10);
      }
    } else {
      // println("fasdf");
    }


    // ----> draw virtual environment

    Finger thumb = new Finger(origin, thumb_end);
    Finger index = new Finger(origin, index_end);
    Finger middle = new Finger(origin, middle_end);
    
    thumb.draw();
    index.draw();
    middle.draw();

    // pushMatrix();
    // translate(object_position.x, object_position.y, object_position.z);
    // sphere(object_radius);
    // popMatrix();

    Ellipsoid object = new Ellipsoid(object_radius, object_radius, object_radius, 10, 10, new Orientation(object_position, null));
    object.draw(g);
    
    //Don't edit past here
  } else {
    //DrawSelectionButtons();
    sayHiForFirstTime=0; 
  }
}

void mouseDragged() {
  float deltaX = mouseX - lastMouse.x;
  float deltaY = mouseY - lastMouse.y;
  
  // Left mouse button: Rotate
  if (mouseButton == LEFT) {
    rotationY += deltaX * 0.01;
    rotationX += deltaY * 0.01;
  }
  // Right mouse button or middle button: Pan
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

//EOF
