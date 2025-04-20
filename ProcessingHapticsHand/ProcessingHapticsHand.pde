/**
 * ProcessingHapticsHand.pde
 * 
 * Main sketch file for the Haptic Hand Interface Visualization.
 * Uses PeasyCam for camera control and modular files for organization.
 */

// Import PeasyCam library
import peasy.*;
// Import IK library
// import ewbik.processing.singlePrecision.*;

// Global state variables (updated by SerialHandler or DataSimulator)
PVector thumb_end;
PVector index_end;
PVector middle_end;
PVector object_position;
float object_radius;

// IK related globals (defined in IKHandler.pde but declared here for access)
// Armature indexArm; 
// Armature middleArm;
// Armature thumbArm;
// PVector wristPos; // Base position of the hand

// PeasyCam instance for camera control
PeasyCam cam;

// settings() runs before setup()
void settings() {
  // Use window dimensions from Configuration.pde
  size(windowWidth, windowHeight, P3D);
  smooth(8); // Enable anti-aliasing (optional, but looks better)
}

// setup() runs once at the start
void setup() {
  // Set window title
  surface.setTitle("Haptic Hand Visualization");
  
  // Initialize global state PVectors
  thumb_end = new PVector(0, 0, 0);
  index_end = new PVector(0, 0, 0);
  middle_end = new PVector(0, 0, 0);
  object_position = new PVector(0, 0, 0);
  object_radius = OBJECT_BASE_RADIUS; // Use base radius from config
  // Set fixed object position (moved from DataSimulator.pde)
  // Positioned in front of palm (along +X) at the hand's base Z
  object_position.set(80, -20, 100); 
  dataReceived = false; // Initially no data
  
  // Initialize PeasyCam
  // The 'this' argument refers to the PApplet (the main sketch)
  // The second argument is the initial distance from the look-at point (0,0,0)
  cam = new PeasyCam(this, 400); 
  cam.rotateY(-PI/2); // Rotate view to face YZ plane initially (Z-right, Y-up, X-away)
  // cam.setMinimumDistance(50);
  // cam.setMaximumDistance(1000);
  // Optional: customize PeasyCam behavior (e.g., rotation modes, sensitivity)
  // cam.setYawRotationMode(); // Example: Only allow yaw rotation with left drag

  // --- Setup IK Armatures ---
  // setupIK(); // Call the setup function from IKHandler.pde
  
  // Setup serial communication (if not in simulation mode)
  setupSerial(); 
  
  println("Setup complete. Using " + (SIMULATION_MODE ? "simulation" : "serial") + " data.");
}

// draw() runs repeatedly
void draw() {
  // Update data (either from simulation or serial)
  if (SIMULATION_MODE) {
    updateSimulationData();
  } else {
    updateSerialData(); // Request new data (reading happens in serialEvent)
  }
  
  // --- Update IK Solver --- 
  // updateIK(); // Solve IK for the current target positions
  
  // Set background color
  background(50); // Darker gray background
  
  // --- Drawing starts --- 
  // PeasyCam automatically handles camera transformations here.
  // No need for manual translate(), rotateX(), rotateY().
  
  // Draw the scene elements using the Renderer
  drawScene(); 
  
  // --- Drawing ends --- 
  
  // Optional: Display framerate or other info using PeasyCam's HUD
  // cam.beginHUD();
  // fill(255);
  // text("FrameRate: " + nfp(frameRate, 1, 1), 20, 20);
  // text("Mode: " + (SIMULATION_MODE ? "Simulation" : "Serial"), 20, 40);
  // cam.endHUD();
}

// --- Input Event Handlers --- 
// These are no longer needed as PeasyCam handles mouse/keyboard input for camera control.
// void mouseDragged() { ... }
// void mousePressed() { ... }
// void mouseWheel(MouseEvent event) { ... }

// You can still add other event handlers if needed for non-camera interaction.
// void keyPressed() {
//   if (key == 's') {
//     // Example: toggle simulation mode (requires handling state change)
//   }
// }
