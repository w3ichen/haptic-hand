/**
 * SerialHandler.pde
 * 
 * Handles serial communication setup, reading, and parsing.
 */

import processing.serial.*;

Serial myPort;  // Create object from Serial class
boolean dataReceived = false;
int sayHiForFirstTime = 0;
String messageBuffer = ""; // Changed to String for character buffering
float[] serialVals = new float[13]; // Array to store parsed values

void setupSerial() {
  if (!SIMULATION_MODE) {
    println("Available serial ports:");
    String[] portList = Serial.list();
    println(portList);
    
    if (portList.length > SERIAL_PORT_INDEX) {
      String portName = portList[SERIAL_PORT_INDEX];
      println("Attempting to connect to: " + portName + " at index " + SERIAL_PORT_INDEX);
      try {
        myPort = new Serial(this, portName, BAUD_RATE);
        myPort.bufferUntil('\n'); // Buffer until newline character
        println("Serial port opened successfully.");
      } catch (Exception e) {
        println("Error opening serial port: " + portName);
        println("Check SERIAL_PORT_INDEX in Configuration.pde");
        println("Switching to simulation mode.");
        exit();
      }
    } else {
      println("Error: SERIAL_PORT_INDEX is out of bounds.");
      println("Found " + portList.length + " ports, but index is " + SERIAL_PORT_INDEX + ".");
      println("Switching to simulation mode.");
      exit();
    }
  }
}

// Function to update data from serial port
void updateSerialData() {
  if (myPort == null || SIMULATION_MODE) {
    println("Error: myPort=null");
    return; // Don't try to read if not initialized or in simulation
  }
  
  // Initial handshake/request
  if (sayHiForFirstTime == 0) {
      myPort.write("1l"); // Send initial request if needed
      // delay(10); // Short delay after write
      sayHiForFirstTime = 1;
  }
  
  // Request new data (adjust command if needed based on your firmware)
  myPort.write("3l");
  // delay(10); // Short delay
}

// Called automatically when serial data arrives (ending with newline)
void serialEvent(Serial p) {
  String messageString = p.readStringUntil('\n');
  if (messageString != null) {
    messageString = messageString.trim(); // Remove leading/trailing whitespace
    println("Raw Serial: " + messageString);
    try {
      // Expecting 13 tab-separated float values
      String[] tokens = splitTokens(messageString, "\t");
      if (tokens.length != 13) {
        return; // Silently discard messages with incorrect number of tokens
      }
      serialVals = float(tokens);
      // Update global state variables with correct finger order
      middle_end.set(serialVals[0], serialVals[1], serialVals[2]);
      index_end.set(serialVals[3], serialVals[4], serialVals[5]);
      thumb_end.set(serialVals[6], serialVals[7], serialVals[8]);
      object_position.set(serialVals[9], serialVals[10], serialVals[11]);
      object_radius = serialVals[12];
      dataReceived = true; // Flag that we have valid data
      println("Parsed Floats: " + join(nf(serialVals, 0, 2), ", "));
      p.write("1l");
      // delay(10);
    } catch (NumberFormatException e) {
      println("Serial Error: Could not parse float values from '" + messageString + "'");
    } catch (Exception e) {
      println("Serial Error: Unexpected error processing message: " + e.getMessage());
    }
  }
}
