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
final int SERIAL_PORT_INDEX = 5; // <--- CHANGE THIS INDEX AS NEEDED
final int BAUD_RATE = 115200;

// Simulation Mode
// Set to true to use simulated data instead of serial data
final boolean SIMULATION_MODE = false; 

// Visualization Settings
final float FINGER_RADIUS = 5; // Reduced radius for better visuals
final float OBJECT_BASE_RADIUS = 30; 