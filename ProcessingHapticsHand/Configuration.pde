/**
 * Configuration.pde
 * 
 * Holds configuration variables for the sketch.
 */

// Window dimensions
final int windowWidth = 800;
final int windowHeight = 800;

// Serial Port Configuration
// IMPORTANT: Find the correct index for your Nucleo board!
// Run the sketch once. It will print the list of available serial ports.
// Identify the correct port for your device and update the index below.
final int SERIAL_PORT_INDEX = 8; // <--- CHANGE THIS INDEX AS NEEDED
final int BAUD_RATE = 115200;

// Simulation Mode
// Set to true to use simulated data instead of serial data
boolean SIMULATION_MODE = false;

// --- Visualization Settings (Units assumed to be mm) ---
final float FINGER_RADIUS = 5; // Radius for drawing finger segments/joints
final float OBJECT_BASE_RADIUS = 30; 

// --- Position History Settings ---
final int POSITION_HISTORY_SIZE = 5; // Number of previous positions to track for jump detection
final float JUMP_THRESHOLD_PERCENT = 0.95; // Threshold as percentage of object radius (e.g., 0.9 = 27mm for 30mm radius)

// --- Hand Geometry ---
// Base offset for the entire hand structure in world coordinates
// Goal: Palm parallel to XY plane, facing -Y (down). Fingers spread along Z.
// Positioned in +Z space.
final PVector FINGER_BASE_OFFSET = new PVector(-20, -60, 45.41); 

// Relative offsets for individual finger bases from FINGER_BASE_OFFSET
// Spread fingers along Z axis (Blue/Right in view). Thumb smallest Z, Middle largest Z.
// Index/Middle bases should be further forward (+X) than Thumb.
final PVector THUMB_FINGER_RELATIVE_OFFSET = new PVector(10, 50, -25);  // Smallest X, smallest Z (-)
final PVector INDEX_FINGER_RELATIVE_OFFSET = new PVector(25, 0, 0);    // Larger X, medium Z (0)
final PVector MIDDLE_FINGER_RELATIVE_OFFSET = new PVector(25, 0, 41.18);   // Larger X, largest Z (+)

// --- Implied Finger Segment Lengths (mm) ---
// These are used for visualization only, not for IK solving.

// Index Finger (3 segments)
final float IMPLIED_INDEX_BONE_1_LEN = 60; 
final float IMPLIED_INDEX_BONE_2_LEN = 40;
final float IMPLIED_INDEX_BONE_3_LEN = 30;

// Middle Finger (3 segments)
final float IMPLIED_MIDDLE_BONE_1_LEN = 65; 
final float IMPLIED_MIDDLE_BONE_2_LEN = 45;
final float IMPLIED_MIDDLE_BONE_3_LEN = 32;

// Thumb (3 segments - treat as 3 flexible segments for simplicity)
final float IMPLIED_THUMB_BONE_1_LEN = 40; 
final float IMPLIED_THUMB_BONE_2_LEN = 35;
final float IMPLIED_THUMB_BONE_3_LEN = 25;

// --- Transformation Matrices for Finger Positions ---
// Translation matrices for each finger (in mm)
final PVector THUMB_TRANSLATION = new PVector(0, 0, 0);    // Default no translation
final PVector INDEX_TRANSLATION = new PVector(0, 0, 0);    // Default no translation
final PVector MIDDLE_TRANSLATION = new PVector(0, 0, 0);   // Default no translation

// Rotation matrices for each finger (in radians)
// Each PVector represents rotation around X, Y, Z axes respectively
final PVector THUMB_ROTATION = new PVector(0, 0, 0);      // Default no rotation
final PVector INDEX_ROTATION = new PVector(0, 0, 0);      // Default no rotation
final PVector MIDDLE_ROTATION = new PVector(0, 0, 0);     // Default no rotation
