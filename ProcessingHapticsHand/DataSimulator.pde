/**
 * DataSimulator.pde
 * 
 * Generates simulated data for finger and object positions.
 */

// Simulation mode variables
float simulationTime = 0;       // Time counter for simulation
float simulationSpeed = 0.03;   // Slightly faster speed for flexing

// --- Define open (extended) and closed (flexed) positions in WORLD COORDINATES ---
// Goal: Palm parallel to XY, facing -Y. Fingers spread along Z, extend along +X.
// Base Offset: (0, -60, 100)
// Abs Bases: Thumb(10,-50,75), Index(25,-60,100), Middle(25,-60,125)

// Thumb (Base X=10, Y=-50, Z=75, moves along X)
// Open: Extends forward (+X)
// Closed: Curls back (-X) and slightly up (+Y)
PVector openThumbPos   = new PVector(70, -50, 75); // BaseX(10)+60
PVector closedThumbPos = new PVector(20, -40, 80); // BaseX(10)+10, Y/Z curl

// Index (Base X=25, Y=-60, Z=100, moves along X)
// Open: Extends far forward (+X)
// Closed: Curls back (-X) and slightly up (+Y)
PVector openIndexPos   = new PVector(125, -60, 100); // BaseX(25)+100
PVector closedIndexPos = new PVector(55, -45, 105);  // BaseX(25)+30, Y/Z curl

// Middle (Base X=25, Y=-60, Z=125, moves along X)
// Open: Extends forward (+X)
// Closed: Curls back (-X) and slightly up (+Y)
PVector openMiddlePos   = new PVector(125, -60, 125); // BaseX(25)+100
PVector closedMiddlePos = new PVector(55, -45, 130); // BaseX(25)+30, Y/Z curl

void updateSimulationData() {
  if (!SIMULATION_MODE) {
    return; // Only run if simulation mode is enabled
  }
  
  // Update simulation time
  simulationTime += simulationSpeed;
  
  // Calculate interpolation factor (oscillates between 0.0 and 1.0)
  float flexFactor = (1 + sin(simulationTime)) / 2.0;
  
  // Interpolate finger WORLD positions between open and closed states
  thumb_end.set(PVector.lerp(openThumbPos, closedThumbPos, flexFactor));
  index_end.set(PVector.lerp(openIndexPos, closedIndexPos, flexFactor));
  middle_end.set(PVector.lerp(openMiddlePos, closedMiddlePos, flexFactor));
  
  // --- Object Simulation (Keep relative to world origin) ---
  // REMOVED object movement calculation
  // object_position remains fixed as set in setup()
  // object_radius remains fixed as set in setup()
  
  dataReceived = true; // Mark data as available for drawing
} 