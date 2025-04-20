/**
 * DataSimulator.pde
 * 
 * Generates simulated data for finger and object positions.
 */

// Simulation mode variables
float simulationTime = 0;       // Time counter for simulation
float simulationSpeed = 0.02;   // Speed of the simulation

void updateSimulationData() {
  if (!SIMULATION_MODE) {
    return; // Only run if simulation mode is enabled
  }
  
  // Update simulation time
  simulationTime += simulationSpeed;
  
  // Simulate finger movements in a circular pattern
  float radius = 100;
  float baseZ = 50; // Adjusted Z base for better PeasyCam view
  
  // Thumb movement
  thumb_end.set(
    radius * cos(simulationTime),
    radius * sin(simulationTime),
    baseZ + 50 * sin(simulationTime * 0.5)
  );
  
  // Index finger movement (slightly different phase)
  index_end.set(
    radius * cos(simulationTime + 1),
    radius * sin(simulationTime + 1),
    baseZ + 50 * sin(simulationTime * 0.5 + 1)
  );
  
  // Middle finger movement (different phase)
  middle_end.set(
    radius * cos(simulationTime + 2),
    radius * sin(simulationTime + 2),
    baseZ + 50 * sin(simulationTime * 0.5 + 2)
  );
  
  // Simulate object movement
  float objectMovementRadius = 150;
  object_position.set(
    objectMovementRadius * cos(simulationTime * 0.5),
    objectMovementRadius * sin(simulationTime * 0.5),
    baseZ + 100
  );
  object_radius = OBJECT_BASE_RADIUS + 10 * sin(simulationTime * 0.8); // Vary radius slightly
  
  dataReceived = true; // Mark data as available for drawing
} 