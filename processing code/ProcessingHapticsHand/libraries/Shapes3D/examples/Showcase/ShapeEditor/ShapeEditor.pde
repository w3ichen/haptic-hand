/**
 * ===============================================
 * Tube and Extrusion Editor
 * ===============================================
 * 
 * This sketch also requires the G4P and PeasyCam 
 * libraries to be installed.
 * 
 * The purpose of this sketch is to enable the 
 * design and creation of Tubes and Extrusion,
 * exploring some of the options available. It is
 * not intended as an example of how to create similar
 * sketches.
 * 
 * You can see a video of this sketch in action here -
 * http://www.lagers.org.uk/gallery/gy-shape-editor/index.html
 *
 *    A Shapes3D library example 
 *    created by Peter Lager 2020
 */
 
 import peasy.*;

import shapes3d.*;
import shapes3d.contour.*;
import shapes3d.org.apache.commons.math.*;
import shapes3d.org.apache.commons.math.geometry.*;
import shapes3d.path.*;
import shapes3d.utils.*;

import g4p_controls.*;

import shape_3D_editor.*;

import java.awt.*;

String filepath = "data/editor/";

// Editor basic controls and groups
GGroup grpActive, grpControls, grpPath, grpContour, grpCode;

GCustomSlider sdrOvalSegs, sdrPolyAngle;
GImageToggleButton btnCircleConstraint;
GSlider2D s2dShift;
float shiftPosX, shiftPosY, shiftSpeed;

// Views and listeners
GView viewContour, viewScale;
GLabel lblNbrPoints;
LScale scaleXListener, scaleYListener;
LOval ovalListener;
LPolygon polygonListener;
// Global controls
GTextArea code;

Data data;

boolean isOverControls = true;

String sketch_code, template_part_1, template_part_2;

// Mouse sensitivity settings for listeners change these 
// to suit your mouse
float msPath = -0.005f; // For the three 2D path editors
float msContour = -0.005f; // For the polygon and oval contour editors
float msScale = -0.025f; // For the contour scale editors
float msView3D = 0.1f; // For 3D views

void setup() {
  size(580, 460, P2D);
  G4P.messagesEnabled(false);
  // Get the code template
  getCodeTemplate();
  // First create some shared data
  data = new Data();
  // Now create the GUI
  grpActive = grpPath = createPathEditorGUI();
  grpContour = createContourEditorGUI();
  grpControls = createControlPanel();
  grpCode = createCodePanel();
}

void draw() {
  background(32, 32, 192);
}

void mouseMoved() {
  if (mouseX > 410 && !isOverControls) {
    grpControls.fadeTo(0, 250, 255);
    isOverControls = true;
  }
  if (mouseX <= 410 && isOverControls) {
    grpControls.fadeTo(0, 100, 100);
    isOverControls = false;
  }
}

void handleButtonEvents(GButton button, GEvent event) {
  if (button.tagNo == 127) {
    switch (button.tag) {
    case "path":
      activateGroup(grpPath);
      break;
    case "contour":
      activateGroup(grpContour);
      break;
    case "code":
      activateGroup(grpCode);
      sketch_code = getSketchCode();
      code.setText(sketch_code);
      break;
    }
  }
}

void activateGroup(GGroup grpToActivate) {
  if (grpToActivate != grpActive) {
    // Deactivate current group
    grpActive.fadeOut(0, 500);
    // Activate another group
    grpActive = grpToActivate;
    grpActive.fadeIn(500, 500);
  }
}
