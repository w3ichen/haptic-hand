/**
 * ProcessingHapticsHand.pde
 * 
 * Main sketch file for the Haptic Hand Interface Visualization.
 * Uses PeasyCam for camera control and modular files for organization.
 */

// Import PeasyCam library
import peasy.*;
// REMOVED: import g4p_controls.*;

// Global state variables (updated by SerialHandler or DataSimulator)
PVector thumb_end;
PVector index_end;
PVector middle_end;
PVector object_position;
float object_radius;

// Flag to track if user is interacting with the GUI
boolean draggingGUI = false; 

// Variables for slider text input
int activeTextInputSliderIndex = -1; // Index of slider being edited (-1 = none)
String textInputBuffer = "";

// Variables for window resize detection
int prevWidth = -1;
int prevHeight = -1;

// Colors for GUI Elements
color toggleColor = color(200, 200, 255); // Light blue for radio buttons
color resetButtonColor = color(150);       // Neutral gray for reset button background

// GUI Visibility State
boolean showGUI = true;

// Global state for GUI toggles
boolean useSimulationData = true; 
boolean showAxes = true;
boolean showPlaneLabels = true;
boolean showTargets = true; 
boolean showPlanes = true; 

// Global GUI3D Controls
Toolbar bar_left; // Assuming Toolbar class exists from GUI3D code

// Global G4P Controls (REMOVED)
/*
GCheckbox cbToggleSimulation;
GCheckbox cbToggleAxes;
GCheckbox cbTogglePlaneLabels;
GCheckbox cbToggleTargets;
GCheckbox cbTogglePlanes; // <<< ADDED
GSlider sliderBaseX, sliderBaseY, sliderBaseZ;
GLabel labelBaseX, labelBaseY, labelBaseZ; // Labels for sliders
*/
// GButton testButton; // REMOVED Test button

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
  smooth(8); 
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
  object_radius = OBJECT_BASE_RADIUS; 
  // Set fixed object position
  object_position.set(80, -60, 100); 
  
  // Initialize simulation state from config 
  useSimulationData = SIMULATION_MODE;
  
  // Initialize PeasyCam
  cam = new PeasyCam(this, 400); 
  // cam.rotateY(-PI/2); // Commented out - potential cause of orientation issues

  // --- Create GUI3D Toolbar --- 
  int BAR_X = 10;
  int BAR_Y = 10;
  int BAR_W = 160;
  int BAR_H = height - 20; // Adjust height as needed
  int MARGIN = 10;

  bar_left = new Toolbar(BAR_X, BAR_Y, BAR_W, BAR_H, MARGIN);
  bar_left.title = "Controls"; // Optional title
  
  // --- Add Radio Buttons for Toggles ---
  bar_left.addRadio("Toggle Sim", toggleColor, useSimulationData, ' ', true); // Index 0
  bar_left.addRadio("Show Axes", toggleColor, showAxes, ' ', true);          // Index 1
  bar_left.addRadio("Show Labels", toggleColor, showPlaneLabels, ' ', true); // Index 2
  bar_left.addRadio("Show Planes", toggleColor, showPlanes, ' ', true);      // Index 3
  bar_left.addRadio("Show Targets", toggleColor, showTargets, ' ', true);    // Index 4

  // --- Add Base Offset Sliders ---
  float baseMin = -200; 
  float baseMax = 200;
  bar_left.addSlider("Base X", "mm", (int)baseMin, (int)baseMax, FINGER_BASE_OFFSET.x, 1.0f, ' ', ' ', true); // Index 0
  bar_left.addSlider("Base Y", "mm", (int)baseMin, (int)baseMax, FINGER_BASE_OFFSET.y, 1.0f, ' ', ' ', true); // Index 1
  bar_left.addSlider("Base Z", "mm", (int)baseMin, (int)baseMax, FINGER_BASE_OFFSET.z, 1.0f, ' ', ' ', true); // Index 2

  // --- Add Reset Button ---
  // Use the defined resetButtonColor variable
  bar_left.addButton("Reset Base", resetButtonColor, ' ', true); // Index 0 (in buttons list)
  
  // --- Setup Serial (if needed) --- 
  setupSerial(); 
  
  // --- Initial GUI Layout ---
  recalculateGUILayout(); // Calculate initial layout based on starting size
  prevWidth = width;      // Store initial size
  prevHeight = height;
  
  println("Setup complete. Initial mode: " + (useSimulationData ? "simulation" : "serial") + " data.");
}

// draw() runs repeatedly
void draw() {
  // --- Check for Window Resize ---
  if (width != prevWidth || height != prevHeight) {
    if (prevWidth != -1) { // Avoid running on first frame before setup is complete
       recalculateGUILayout();
    }
    prevWidth = width;
    prevHeight = height;
  }
  
  // --- Update State from GUI --- 
  try {
    // Read Radio Buttons (Indices 0-4 in radios list)
    useSimulationData = bar_left.radios.get(0).value;
    showAxes = bar_left.radios.get(1).value;         
    showPlaneLabels = bar_left.radios.get(2).value; 
    showPlanes = bar_left.radios.get(3).value;      
    showTargets = bar_left.radios.get(4).value;

    // Read Sliders (Indices 0-2 in sliders list now)
    FINGER_BASE_OFFSET.x = bar_left.sliders.get(0).value; 
    FINGER_BASE_OFFSET.y = bar_left.sliders.get(1).value;
    FINGER_BASE_OFFSET.z = bar_left.sliders.get(2).value;
  } catch (IndexOutOfBoundsException e) {
     // Handle potential errors if GUI lists are empty or indices are wrong
     println("Error accessing GUI controls (check indices): " + e.getMessage());
  } catch (Exception e) {
     // Handle other potential errors
     println("Error accessing GUI controls: " + e.getMessage());
  }

  // Update data (either from simulation or serial)
  if (useSimulationData) { 
    updateSimulationData();
  } else {
    updateSerialData(); 
  }
  
  // Set background color
  background(50); 
  
  // --- Drawing starts --- 
  // PeasyCam handles camera transformations.
  drawScene(); 
  // --- Drawing ends --- 
  
  // --- Draw GUI (if enabled) --- 
  if (showGUI) {
    // Use PeasyCam's HUD mode for 2D overlay drawing
    cam.beginHUD(); 
    if (bar_left != null) bar_left.draw(); // Draw the toolbar
    
    // Draw toggle hint text
    pushStyle();
    // fill(200); // Light gray text
    textSize(12);
    textAlign(LEFT, BOTTOM);
    text("Press 'h' to toggle panel", 18, height - 15); // Bottom-left corner
    popStyle();
    
    cam.endHUD();
  }
}

// --- Recalculate GUI Layout on Resize ---
void recalculateGUILayout() {
  if (bar_left == null) return; // Safety check
  
  println("Window resized (" + width + "x" + height + "), recalculating GUI height...");
  
  // --- Recalculate Toolbar Height ONLY ---
  // Keep X, Y, Width, Margin fixed as defined in setup()
  int newBarH = height - 2 * bar_left.margin; 
  if (newBarH < 100) newBarH = 100; // Apply minimum height
  bar_left.barH = newBarH;
  bar_left.contentH = bar_left.barH - 2 * bar_left.margin; // Update content height
  
  // --- Removed individual control recalculation ---
  // Relying on Toolbar.draw() to clip content correctly based on new barH.

  println("GUI height recalculated."); 
  
  if (cam != null) {
     cam.feed(); // Nudge PeasyCam to update its state
     println("PeasyCam state fed after resize.");
  }
}

// --- Reset Function ---
void resetBaseOffsetSliders() {
  // Need to access the initial base offset values. 
  // Re-creating the initial PVector defined in Configuration.pde
  // If Configuration.pde changes, this needs to be updated.
  // Alternatively, store initial values in global variables in setup().
  PVector initialBaseOffset = new PVector(0, -60, 100); // Values from Configuration.pde
  
  try {
    if (bar_left != null && bar_left.sliders.size() >= 3) {
      bar_left.sliders.get(0).value = initialBaseOffset.x; // Base X slider
      bar_left.sliders.get(1).value = initialBaseOffset.y; // Base Y slider
      bar_left.sliders.get(2).value = initialBaseOffset.z; // Base Z slider
      println("Base Offset sliders reset to defaults.");
    }
  } catch (Exception e) {
    println("Error resetting base offset sliders: " + e.getMessage());
  }
}

// --- Input Event Handlers (GUI Interaction) --- 

void mousePressed() {
  // If GUI is hidden, ensure camera is active and do nothing else
  if (!showGUI) {
    cam.setActive(true);
    return; 
  }
  
  boolean clickedOnGuiElement = false;
  
  // If mouse is over the toolbar...
  if (bar_left != null && bar_left.hover()) {
    clickedOnGuiElement = true;
    boolean clickedOnTextEditLabel = false;
    
    // --- Check for Clicks on Slider Value Labels to Activate Text Input ---
    int baseSliderStartIndex = 0; // Index of the first base offset slider (Base X)
    int numBaseSliders = 3;
    float labelClickWidth = 60; // Approximate width for clicking the value label
    float labelClickHeight = 20; // Approximate height
    
    for (int i = 0; i < numBaseSliders; i++) {
      int sliderIndex = baseSliderStartIndex + i;
      if (sliderIndex < bar_left.sliders.size()) {
        ControlSlider slider = bar_left.sliders.get(sliderIndex);
        // Estimate label area (right-aligned text)
        float labelX = slider.xpos + slider.len - labelClickWidth;
        float labelY = slider.ypos - 10; // Centered around ypos-5 where text is drawn
        
        if (mouseX > labelX && mouseX < labelX + labelClickWidth &&
            mouseY > labelY && mouseY < labelY + labelClickHeight) {
              
          // Clicked on this slider's value label
          clickedOnTextEditLabel = true;
          activeTextInputSliderIndex = sliderIndex;
          textInputBuffer = nfp(slider.value, 0, 1); // Start buffer with current value, formatted
          slider.isEditingText = true;
          println("Activated text input for slider: " + slider.name);
          
          // Deactivate other sliders' text edit mode
          for (int j = 0; j < numBaseSliders; j++) {
             if (i != j && (baseSliderStartIndex + j) < bar_left.sliders.size()) {
               bar_left.sliders.get(baseSliderStartIndex + j).isEditingText = false;
             }
          }
          break; // Stop checking labels once one is found
        }
      }
    }

    // --- Handle Other GUI Clicks (Sliders, Radios, Reset Button) ---
    if (!clickedOnTextEditLabel) {
      // Deactivate text input if clicking elsewhere on the bar
      if(activeTextInputSliderIndex != -1) {
         if (activeTextInputSliderIndex < bar_left.sliders.size()) {
            bar_left.sliders.get(activeTextInputSliderIndex).isEditingText = false;
         }
         activeTextInputSliderIndex = -1;
         textInputBuffer = "";
      }
      
      // Normal toolbar press handling (drags, radio toggles)
      bar_left.pressed(); 
      
      // Check Reset button press (moved from direct check)
      try {
        if (bar_left.buttons.size() > 0 && bar_left.buttons.get(0).hasBeenPressed) {
          resetBaseOffsetSliders();
          bar_left.buttons.get(0).hasBeenPressed = false; // Manually reset flag
        }
      } catch (Exception e) {
        println("Error checking reset button: " + e.getMessage());
      }
    }

    // Keep camera inactive while interacting with GUI
    cam.setActive(false); 
    draggingGUI = true; // Set flag

  } else {
    // Click was outside the GUI bar
    clickedOnGuiElement = false;
    draggingGUI = false;
    cam.setActive(true); // Activate camera control
    
    // Deactivate any active text input
    if (activeTextInputSliderIndex != -1) {
      if (activeTextInputSliderIndex < bar_left.sliders.size()) {
         bar_left.sliders.get(activeTextInputSliderIndex).isEditingText = false;
      }
      activeTextInputSliderIndex = -1;
      textInputBuffer = "";
    }
  }
}

void mouseReleased() {
  // Always tell the toolbar when the mouse is released
  if (bar_left != null) {
    bar_left.released(); 
  }
  // Reset the flag and ensure PeasyCam is active
  draggingGUI = false;
  cam.setActive(true);
}

// --- Key Press Handler for Text Input ---
void keyPressed() {
  if (activeTextInputSliderIndex != -1) {
    // Input is active for a slider
    if (key >= '0' && key <= '9' || key == '.' || key == '-') {
      textInputBuffer += key;
    } else if (key == BACKSPACE) {
      if (textInputBuffer.length() > 0) {
        textInputBuffer = textInputBuffer.substring(0, textInputBuffer.length() - 1);
      }
    } else if (key == ENTER || key == RETURN) {
      // Commit the value
      try {
        float newValue = float(textInputBuffer);
        ControlSlider slider = bar_left.sliders.get(activeTextInputSliderIndex);
        slider.value = newValue;
        slider.checkLimit(); // Ensure value stays within min/max
        // Update the corresponding FINGER_BASE_OFFSET component
        if (activeTextInputSliderIndex == 0) FINGER_BASE_OFFSET.x = slider.value;
        else if (activeTextInputSliderIndex == 1) FINGER_BASE_OFFSET.y = slider.value;
        else if (activeTextInputSliderIndex == 2) FINGER_BASE_OFFSET.z = slider.value;
        
        println("Set " + slider.name + " to: " + slider.value);
        
        // Deactivate text input
        slider.isEditingText = false;
        activeTextInputSliderIndex = -1;
        textInputBuffer = "";
        
      } catch (NumberFormatException e) {
        println("Invalid number format: " + textInputBuffer);
        // Optionally reset buffer or keep editing
        // textInputBuffer = ""; // Clear buffer on error
      } catch (Exception e) {
        println("Error applying text input: " + e.getMessage());
        // Deactivate to be safe
        if (activeTextInputSliderIndex < bar_left.sliders.size()) {
           bar_left.sliders.get(activeTextInputSliderIndex).isEditingText = false;
        }
        activeTextInputSliderIndex = -1;
        textInputBuffer = "";
      }
    } else if (key == ESC) {
      // Cancel text input
      bar_left.sliders.get(activeTextInputSliderIndex).isEditingText = false;
      activeTextInputSliderIndex = -1;
      textInputBuffer = "";
    }
  } else {
    // No text input active, handle other keys if needed
    // e.g., pass to PeasyCam or other functions
    // PeasyCam handles its own default keys like WASD/Arrows if active.
  }
}

// --- Key Released Handler for GUI Toggle ---
void keyReleased() {
  if (key == 'h' || key == 'H') {
    showGUI = !showGUI;
    println("GUI Visibility Toggled: " + showGUI);
    // Ensure camera is active if GUI is hidden
    if (!showGUI) {
        cam.setActive(true);
    }
  }
}

// --- Original PeasyCam Input Handlers (commented out as PeasyCam handles them) --- 
// These are no longer needed as PeasyCam handles mouse/keyboard input for camera control.
// void mouseDragged() { ... }
// void mouseWheel(MouseEvent event) { ... }

// You can still add other event handlers if needed for non-camera interaction.
// void keyPressed() {
//   if (key == 's') {
//     // Example: toggle simulation mode (requires handling state change)
//   }
// }
