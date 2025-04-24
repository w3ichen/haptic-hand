/**
 * Renderer.pde
 * 
 * Contains drawing functions for the scene, using implied joints.
 */

// import ewbik.processing.singlePrecision.*; // REMOVED IK import

// Colors for drawing (Restored)
color fingerColor = color(255, 180, 180); // Light pink
color objectColor = color(200, 200, 255, 200); // Light blue, slightly transparent
// color boneColor = color(240); // Off-white for bones - Not used directly now
color jointColor = color(100, 100, 255); // Blue for joints

/**
 * Draws the entire scene if data is available.
 */
void drawScene() {
  if (!dataReceived) {
    // Optional: Draw a loading message or placeholder
    fill(255);
    textAlign(CENTER, CENTER);
    text("Waiting for data...", 0, 0); // Centered text because PeasyCam centers the view
    return;
  }
  
  // Set lights
  ambientLight(100, 100, 100);
  pointLight(255, 255, 255, 0, -200, 200); // Light from above-front
  directionalLight(150, 150, 150, 0.5, 1, -1); // Angled light
  
  // Draw elements conditionally based on GUI toggles
  if (showAxes) { drawCoordinateSystem(100); }
  if (showPlaneLabels) { drawPlaneLabels(); }
  if (showPlanes) { drawCoordinatePlanes(100); }
  drawFingers(); // Draw the bezier curve fingers
  drawObject();
  if (showTargets) { drawTargets(); } // Added conditional drawing for targets
}

/**
 * Draws X, Y, Z coordinate axes.
 */
void drawCoordinateSystem(float axisLength) {
  strokeWeight(2);
  // X axis (red)
  stroke(255, 0, 0);
  line(0, 0, 0, axisLength, 0, 0);
  // Y axis (green) - Up
  stroke(0, 255, 0);
  line(0, 0, 0, 0, -axisLength, 0); // Draw negative Y to point upwards
  // Z axis (blue) - Out
  stroke(0, 0, 255);
  line(0, 0, 0, 0, 0, axisLength);
  strokeWeight(1);
}

/**
 * Draws the fingers using implied joints directed towards the target.
 */
void drawFingers() {
  // Calculate absolute base positions for each finger
  PVector indexBaseAbs = PVector.add(FINGER_BASE_OFFSET, INDEX_FINGER_RELATIVE_OFFSET);
  PVector middleBaseAbs = PVector.add(FINGER_BASE_OFFSET, MIDDLE_FINGER_RELATIVE_OFFSET);
  PVector thumbBaseAbs = PVector.add(FINGER_BASE_OFFSET, THUMB_FINGER_RELATIVE_OFFSET);

  // Apply transformations to finger end positions
  PVector transformedThumbEnd = applyTransformations(thumb_end, THUMB_TRANSLATION, THUMB_ROTATION);
  PVector transformedIndexEnd = applyTransformations(index_end, INDEX_TRANSLATION, INDEX_ROTATION);
  PVector transformedMiddleEnd = applyTransformations(middle_end, MIDDLE_TRANSLATION, MIDDLE_ROTATION);

  // Draw each finger using the helper function with its specific base position
  drawImpliedFinger(thumbBaseAbs, transformedThumbEnd, 
                    IMPLIED_THUMB_BONE_1_LEN, IMPLIED_THUMB_BONE_2_LEN, IMPLIED_THUMB_BONE_3_LEN, 
                    FINGER_RADIUS * 0.9); // Slightly thicker thumb
                    
  drawImpliedFinger(indexBaseAbs, transformedIndexEnd, 
                    IMPLIED_INDEX_BONE_1_LEN, IMPLIED_INDEX_BONE_2_LEN, IMPLIED_INDEX_BONE_3_LEN, 
                    FINGER_RADIUS * 0.8);
                    
  drawImpliedFinger(middleBaseAbs, transformedMiddleEnd, 
                    IMPLIED_MIDDLE_BONE_1_LEN, IMPLIED_MIDDLE_BONE_2_LEN, IMPLIED_MIDDLE_BONE_3_LEN, 
                    FINGER_RADIUS * 0.8);
}

/**
 * Applies translation and rotation transformations to a point
 */
PVector applyTransformations(PVector point, PVector translation, PVector rotation) {
  PVector result = point.copy();
  
  // Negate Y component to handle graphics coordinate system
  result.y = -result.y;
  
  // Apply translation
  result.add(translation);
  
  // Apply rotation around X axis
  float y = result.y;
  float z = result.z;
  result.y = y * cos(rotation.x) - z * sin(rotation.x);
  result.z = y * sin(rotation.x) + z * cos(rotation.x);
  
  // Apply rotation around Y axis
  float x = result.x;
  z = result.z;
  result.x = x * cos(rotation.y) + z * sin(rotation.y);
  result.z = -x * sin(rotation.y) + z * cos(rotation.y);
  
  // Apply rotation around Z axis
  x = result.x;
  y = result.y;
  result.x = x * cos(rotation.z) - y * sin(rotation.z);
  result.y = x * sin(rotation.z) + y * cos(rotation.z);
  
  return result;
}

/**
 * Helper function to draw a single finger with implied joints using a Bezier curve.
 * Draws 3 segments starting from fingerBase, curving towards targetEnd.
 */
void drawImpliedFinger(PVector fingerBase, PVector targetEnd, 
                       float len1, float len2, float len3, 
                       float segmentRadius) {
  pushStyle();
  noStroke();
  fill(fingerColor);

  PVector joint0 = fingerBase.copy();
  float totalLen = len1 + len2 + len3;
  
  // Define the bend direction (towards palm/floor = -Y world axis)
  PVector bendDir = new PVector(0, -1, 0); 
  
  // Calculate the distance and vector from base to target
  PVector totalVec = PVector.sub(targetEnd, fingerBase);
  float dist = totalVec.mag();
  
  // Define Bezier control points
  // Control point 1: Offset from base towards bend direction
  // Control point 2: Offset from target towards bend direction
  // The amount of offset determines the curve intensity - adjust 'bendAmount' as needed
  float bendAmount = dist * 0.3; // Example: 30% of distance, creates a noticeable curve
  PVector control1 = PVector.add(PVector.lerp(fingerBase, targetEnd, 0.25), PVector.mult(bendDir, bendAmount));
  PVector control2 = PVector.add(PVector.lerp(fingerBase, targetEnd, 0.75), PVector.mult(bendDir, bendAmount));

  // Calculate joint positions along the Bezier curve based on bone lengths
  // Parameter t is the fraction of the total *bone length* along the curve
  float t1 = len1 / totalLen;
  float t2 = (len1 + len2) / totalLen;
  float t3 = 1.0; // End of the curve

  float j1x = bezierPoint(joint0.x, control1.x, control2.x, targetEnd.x, t1);
  float j1y = bezierPoint(joint0.y, control1.y, control2.y, targetEnd.y, t1);
  float j1z = bezierPoint(joint0.z, control1.z, control2.z, targetEnd.z, t1);
  PVector joint1 = new PVector(j1x, j1y, j1z);

  float j2x = bezierPoint(joint0.x, control1.x, control2.x, targetEnd.x, t2);
  float j2y = bezierPoint(joint0.y, control1.y, control2.y, targetEnd.y, t2);
  float j2z = bezierPoint(joint0.z, control1.z, control2.z, targetEnd.z, t2);
  PVector joint2 = new PVector(j2x, j2y, j2z);
  
  // Joint 3 is the end point of the curve, approximating the target
  float j3x = bezierPoint(joint0.x, control1.x, control2.x, targetEnd.x, t3);
  float j3y = bezierPoint(joint0.y, control1.y, control2.y, targetEnd.y, t3);
  float j3z = bezierPoint(joint0.z, control1.z, control2.z, targetEnd.z, t3);
  PVector joint3 = new PVector(j3x, j3y, j3z);
  
  // Draw segments as cylinders and joints as spheres
  // Joint 0 (Base)
  pushMatrix();
  translate(joint0.x, joint0.y, joint0.z);
  fill(jointColor); 
  sphere(segmentRadius * 1.2);
  popMatrix();

  // Bone 1
  fill(fingerColor);
  drawCylinder(joint0, joint1, segmentRadius);
  pushMatrix();
  translate(joint1.x, joint1.y, joint1.z);
  fill(jointColor); 
  sphere(segmentRadius * 1.2);
  popMatrix();

  // Bone 2
  fill(fingerColor);
  drawCylinder(joint1, joint2, segmentRadius);
  pushMatrix();
  translate(joint2.x, joint2.y, joint2.z);
  fill(jointColor); 
  sphere(segmentRadius * 1.2);
  popMatrix();
  
  // Bone 3
  fill(fingerColor);
  drawCylinder(joint2, joint3, segmentRadius);
  pushMatrix();
  translate(joint3.x, joint3.y, joint3.z);
  fill(jointColor); // Also color the final joint/tip
  sphere(segmentRadius * 1.2);
  popMatrix();

  popStyle();
}

/**
 * Draws the object as a sphere.
 */
void drawObject() {
  pushMatrix();
  translate(object_position.x, object_position.y, object_position.z);
  noStroke();
  fill(objectColor);
  sphere(object_radius);
  popMatrix();
}

/**
 * Optional: Draws the target points for visualization/debugging.
 */
void drawTargets() {
  pushStyle();
  noFill();
  strokeWeight(2);
  
  // Index Target (Cyan)
  stroke(0, 255, 255);
  pushMatrix();
  translate(index_end.x, -index_end.y, index_end.z);  // Negate Y component
  box(10); // Draw a small box at the target
  popMatrix();
  
  // Middle Target (Magenta)
  stroke(255, 0, 255);
  pushMatrix();
  translate(middle_end.x, -middle_end.y, middle_end.z);  // Negate Y component
  box(10);
  popMatrix();
  
  // Thumb Target (Yellow)
  stroke(255, 255, 0);
  pushMatrix();
  translate(thumb_end.x, -thumb_end.y, thumb_end.z);  // Negate Y component
  box(10);
  popMatrix();
  
  popStyle();
}

/**
 * Draws text labels for the coordinate planes near the origin.
 */
void drawPlaneLabels() {
  if (!showPlaneLabels) return; // Check the global toggle

  pushStyle();
  float offset = 60; // How far from the origin to place the label
  float textSize = 16;
  textSize(textSize);
  textAlign(CENTER, CENTER);
  fill(255, 255, 200); // Bright yellow-white

  // XY Label (on Z axis)
  pushMatrix();
  translate(offset, -offset, 0); // Position near the XY plane corner
  // No rotation needed, text faces camera by default in PeasyCam
  text("XY", 0, 0);
  popMatrix();

  // XZ Label (on Y axis)
  pushMatrix();
  translate(offset, 0, offset); // Position near the XZ plane corner
  rotateX(PI/2); // Orient text to roughly face out from XZ plane 
  text("XZ", 0, 0);
  popMatrix();

  // YZ Label (on X axis)
  pushMatrix();
  translate(0, -offset, offset); // Position near the YZ plane corner
  rotateY(-PI/2); // Orient text to roughly face out from YZ plane
  text("YZ", 0, 0);
  popMatrix();
  
  popStyle();
}

/**
 * Draws translucent colored squares representing coordinate planes.
 */
void drawCoordinatePlanes(float planeSize) {
  if (!showPlanes) return; // Check the global toggle
  
  pushStyle();
  noStroke();
  rectMode(CORNER); // Keep CORNER mode for XY and XZ
  float labelOffset = 5; // How far off the plane to draw text - REMOVED FROM HERE
  float textSize = 16;
  // REMOVED textSize setting and textAlign - moved to drawPlaneLabels
  
  // XY Plane (Z=0, Red/Green -> Yellowish)
  pushMatrix();
  // No rotation needed, already aligned
  fill(255, 255, 0, 50); // Semi-transparent yellow
  rect(0, 0, planeSize, -planeSize); // Draw from origin along +X, -Y (Up)
  // REMOVED Label drawing
  popMatrix();

  // XZ Plane (Y=0, Red/Blue -> Magentish)
  pushMatrix();
  rotateX(PI/2); // Rotate plane to align with XZ
  fill(255, 0, 255, 50); // Semi-transparent magenta
  rect(0, 0, planeSize, planeSize); // Draw from origin along +X, +Z (local)
  // REMOVED Label drawing
  popMatrix();

  // YZ Plane (X=0, Green/Blue -> Cyannish)
  pushMatrix();
  // No rotation needed, draw directly with vertices
  fill(0, 255, 255, 50); // Semi-transparent cyan
  beginShape(QUADS);
  vertex(0, 0, 0);           // Origin
  vertex(0, -planeSize, 0);  // Up Y axis
  vertex(0, -planeSize, planeSize); // Up Y, Forward Z
  vertex(0, 0, planeSize);    // Forward Z
  endShape(CLOSE);
  // REMOVED Label drawing
  popMatrix();
  
  popStyle();
}

// Helper function to draw a cylinder between two points (Restored)
void drawCylinder(PVector p1, PVector p2, float r) {
  PVector center = PVector.lerp(p1, p2, 0.5);
  float len = PVector.dist(p1, p2);
  int sides = 12;
    
  if (len < 0.1) return; // Avoid drawing zero-length cylinder
    
  // Calculate rotation axis and angle
  PVector diff = PVector.sub(p2, p1);
  diff.normalize(); // Normalize for angle calculation
    
  PVector rotAxis = new PVector(0, 1, 0).cross(diff);
  float rotAngle = PVector.angleBetween(new PVector(0, 1, 0), diff);
    
  pushMatrix();
  translate(center.x, center.y, center.z);
  // Check if axis is near zero vector (collinear cases)
  if (rotAxis.magSq() > 0.001) {
    rotate(rotAngle, rotAxis.x, rotAxis.y, rotAxis.z);
  } else if (diff.y < -0.99) { // Check Y component after normalization
    // If pointing directly down (-Y), rotate 180 degrees around X or Z
    rotate(PI, 1, 0, 0); 
  } else if (diff.y > 0.99) {
    // If pointing directly up (+Y), no rotation needed
  }
    
  // Draw the cylinder body using a quad strip for better lighting
  beginShape(QUAD_STRIP);
  for (int i = 0; i <= sides; i++) {
    float angle = TWO_PI * i / sides;
    float x = cos(angle) * r;
    float z = sin(angle) * r;
    // Define normals for lighting: points outwards from the cylinder axis
    normal(cos(angle), 0, sin(angle)); 
    vertex(x, len/2, z);  // Top vertex
    vertex(x, -len/2, z); // Bottom vertex
  }
  endShape();
    
  popMatrix();
}

// [REMOVED SimpleFinger CLASS] 