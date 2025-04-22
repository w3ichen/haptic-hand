/*  TOOLBAR ALGORITHMS
 *  Ira Winder, ira@mit.edu, 2018
 *
 *  input are generalizable for parameterized models. For a generic 
 *  implementation check out the repo at: http://github.com/irawinder/GUI3D
 *  
 *  CLASSES CONTAINED:
 *
 *    Toolbar()       - Toolbar that may implement ControlSlider(), Radio Button(), and TriSlider()
 *    ControlSlider() - A customizable horizontal slider ideal for generic parameritization of integers
 *    Button()        - A customizable button that triggers a one-time action
 *    RadioButton()   - A customizable radio button ideal for generic parameritization of boolean
 *    TriSlider()     - A customizable triable slider that outputs three positive floats that add up to 1.0
 *
 *  MIT LICENSE: Copyright 2018 Ira Winder
 *
 *               Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 *               and associated documentation files (the "Software"), to deal in the Software without restriction, 
 *               including without limitation the rights to use, copy, modify, merge, publish, distribute, 
 *               sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is 
 *               furnished to do so, subject to the following conditions:
 *
 *               The above copyright notice and this permission notice shall be included in all copies or 
 *               substantial portions of the Software.
 *
 *               THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT 
 *               NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 *               NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
 *               DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 *               OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
  
class Toolbar {
  int barX, barY, barW, barH; // X, Y, Width, and Height of Toolbar on Screen
  int contentW, contentH;     // pixel width and height of toolbar content accounting for margin
  int margin;                 // standard internal pixel buffer distance from edge of canvas
  int CONTROL_H = 35;         // standard vertical pixel distance between control elements
  int controlY;               // vertical position where controls begin
  
  String title, credit, explanation;
  ArrayList<ControlSlider> sliders;
  ArrayList<RadioButton> radios;
  ArrayList<Button> buttons;
  ArrayList<TriSlider> tSliders;
  
  Toolbar(int barX, int barY, int barW, int barH, int margin) {
    this.barX = barX;
    this.barY = barY;
    this.barW = barW;
    this.barH = barH;
    this.margin = margin;
    contentW = barW - 2*margin;
    contentH = barH - 2*margin;
    // Initialize text fields to prevent "null" concatenation
    title = ""; 
    credit = "";
    explanation = "";
    sliders  = new ArrayList<ControlSlider>();
    buttons  = new ArrayList<Button>();
    radios  = new ArrayList<RadioButton>();
    tSliders = new ArrayList<TriSlider>();
    controlY = 8*CONTROL_H; // Default starting position for controls
  }
  
  void addSlider(String name, String unit, int valMin, int valMax, float DEFAULT_VALUE, float inc, char keyMinus, char keyPlus, boolean keyCommand) {
    float num = sliders.size() + radios.size() + 2*buttons.size() + 6*tSliders.size();
    ControlSlider s;
    s = new ControlSlider();
    s.name = name;
    s.unit = unit;
    s.keyPlus = keyPlus;
    s.keyMinus = keyMinus;
    s.keyCommand = keyCommand;
    s.xpos = barX + margin;
    s.ypos = controlY + int(num*CONTROL_H);
    s.len = contentW - margin;
    s.valMin = valMin;
    s.valMax = valMax;
    s.DEFAULT_VALUE = DEFAULT_VALUE;
    s.value = s.DEFAULT_VALUE;
    s.s_increment = inc;
    sliders.add(s);
  }
  
  void addRadio(String name, int col, boolean DEFAULT_VALUE, char keyToggle, boolean keyCommand) {
    float num = sliders.size() + radios.size() + 2*buttons.size() + 6*tSliders.size();
    RadioButton b;
    b = new RadioButton();
    b.name = name;
    b.keyToggle = keyToggle;
    b.keyCommand = keyCommand;
    b.xpos = barX + margin;
    b.ypos = controlY + int(num*CONTROL_H);
    b.DEFAULT_VALUE = DEFAULT_VALUE;
    b.value = b.DEFAULT_VALUE;
    b.col = col;
    radios.add(b);
  }
  
  void addButton(String name, int col, char keyToggle, boolean keyCommand) {
    float num = sliders.size() + radios.size() + 2*buttons.size() + 6*tSliders.size() - 0.25;
    Button b = new Button();
    b.name = name;
    b.col = col;
    b.keyToggle = keyToggle;
    b.keyCommand = keyCommand;
    b.xpos = barX + margin;
    b.ypos = controlY + int(num*CONTROL_H);
    b.bW = barW - 2*margin;
    b.bH = CONTROL_H;
    buttons.add(b);
  }
  
  void addTriSlider(String name, String name1, int col1, String name2, int col2, String name3, int col3) {
    float num = sliders.size() + radios.size() + 2*buttons.size() + 6*tSliders.size();
    TriSlider t;
    t = new TriSlider();
    t.name = name;
    t.name1 = name1;
    t.col1 = col1;
    t.name2 = name2;
    t.col2 = col2;
    t.name3 = name3;
    t.col3 = col3;
    t.xpos = barX + margin;
    t.ypos = controlY + int(num*CONTROL_H);
    t.corner1.x = barX + 0.50*barW;
    t.corner1.y = controlY + (num+0.70)*CONTROL_H + 16;
    t.corner2.x = barX + 0.33*barW;
    t.corner2.y = controlY + (num+2.90)*CONTROL_H + 16;
    t.corner3.x = barX + 0.67*barW;
    t.corner3.y = controlY + (num+2.90)*CONTROL_H + 16;
    t.avgX = (t.corner1.x+t.corner2.x+t.corner3.x)/3.0;
    t.avgY = (t.corner1.y+t.corner2.y+t.corner3.y)/3.0;
    t.avg = new PVector(t.avgX, t.avgY);
    t.r = t.avg.dist(t.corner1);
    t.pt = new PVector(t.avgX, t.avgY);
    t.calculateValues();
    tSliders.add(t);
  }
  
  void pressed() {
    if (sliders.size()  > 0) for (ControlSlider s: sliders ) s.listen();
    if (radios.size()   > 0) for (RadioButton   b: radios  ) b.listen();
    if (buttons.size()  > 0) for (Button        b: buttons ) b.listen();
    if (tSliders.size() > 0) for (TriSlider     t: tSliders) t.listen();
  }
  
  void released() {
    if (sliders.size()  > 0) for (ControlSlider s: sliders ) s.isDragged = false;
    if (tSliders.size() > 0) for (TriSlider     t: tSliders) t.isDragged = false;
    if (buttons.size()  > 0) for (Button        b: buttons ) b.released();
  }
  
  void restoreDefault() {
    if (sliders.size()  > 0) for (ControlSlider s: sliders ) s.value = s.DEFAULT_VALUE;
    if (radios.size()   > 0) for (RadioButton   b: radios  ) b.value = b.DEFAULT_VALUE;
    if (tSliders.size() > 0) for (TriSlider     t: tSliders) t.useDefault();
  }
  
  // Draw Margin Elements
  //
  void draw() {
    pushMatrix();
    translate(barX, barY);
    
    // Shadow
    pushMatrix(); translate(3, 3);
    noStroke();
    fill(0, 100);
    rect(0, 0, barW, barH, margin);
    popMatrix();
    
    // Canvas
    fill(255, 20);
    noStroke();
    rect(0, 0, barW, barH, margin);
    
    // Canvas Content
    translate(margin, margin);
    textAlign(LEFT, TOP);
    fill(255);
    text(title + credit + explanation, 0, 0, contentW, contentH);
    popMatrix();
    
    // Sliders
    for (ControlSlider s: sliders) {
      s.update();
      s.drawMe();
    }
    
    // Buttons
    for (RadioButton b: radios) b.drawMe();
    for (Button b: buttons)     b.drawMe();
    
    // TriSliders
    for (TriSlider t: tSliders) {
      t.update();
      t.drawMe();
    }
  }
  
  boolean hover() {
    if (mouseX > barX && mouseX < barX + barW && 
        mouseY > barY && mouseY < barY + barH) {
      return true;
    } else {
      return false;
    }
  }
}

class ControlSlider {
  String name;
  String unit;
  int xpos;
  int ypos;
  int len;
  int diameter;
  char keyMinus;
  char keyPlus;
  boolean keyCommand;
  boolean isDragged;
  int valMin;
  int valMax;
  float value;
  float DEFAULT_VALUE = 0;
  float s_increment;
  int col;
  boolean isEditingText; // Flag for text input mode
  String textInputBuffer; // Added for text input buffer
  
  ControlSlider() {
    xpos = 0;
    ypos = 0;
    len = 200;
    diameter = 15;
    keyMinus = '-';
    keyPlus = '+';
    keyCommand = true;
    isDragged = false;
    valMin = 0;
    valMax = 0;
    value = 0;
    s_increment = 1;
    col = 255;
    isEditingText = false; // Initialize flag
    textInputBuffer = ""; // Initialize text input buffer
  }
  
  void update() {
    if (isDragged) value = (mouseX-xpos)*(valMax-valMin)/len+valMin;
    checkLimit();
    if (value % s_increment < s_increment/2) {
      value = s_increment*int(value/s_increment);
    } else {
      value = s_increment*(1+int(value/s_increment));
    }
  }
  
  void checkLimit() {
    value = max(valMin, min(valMax, value));
  }
  
  void checkKey() {
    if (keyMinus == '+' && keyCommand) {
      value = value + s_increment;
      checkLimit();
    }
    if (keyMinus == '-' && keyCommand) {
      value = value - s_increment;
      checkLimit();
    }
  }
  
  void listen() {
    float dist = abs(mouseY - (ypos+0.5*diameter));
    if (dist < diameter && mouseX > xpos && mouseX < xpos + len) {
      isDragged = true;
      value = (mouseX-xpos)*(valMax-valMin)/len+valMin;
      checkLimit();
    }
  }
  
  void drawMe() {
    textAlign(LEFT, CENTER);
    fill(255);
    text(name, xpos, ypos-5);
    
    // Draw value text or text input buffer (accessed globally)
    textAlign(RIGHT, CENTER);
    if (isEditingText) {
      // Display the text buffer with a blinking cursor
      String displayText = textInputBuffer; // Uses global textInputBuffer
      if (frameCount % 60 < 30) { // Blink cursor every ~0.5 seconds
        displayText += "|";
      }
      fill(200, 255, 200); // Highlight color while editing
      text(displayText, xpos + len, ypos - 5); 
    } else {
      // Display normal slider value
      fill(255);
      text(nfp(value, 0, 1) + " " + unit, xpos + len, ypos - 5); // Use nfp for formatting
    }
    
    // Draw slider bar and handle
    stroke(255, 50);
    strokeWeight(1);
    line(xpos, ypos+0.5*diameter, xpos+len, ypos+0.5*diameter);
    noStroke();
    fill(col, 100);
    ellipse(xpos + len * (value-valMin) / (valMax-valMin), ypos+0.5*diameter, diameter, diameter);
    fill(col, 255);
    ellipse(xpos + len * (value-valMin) / (valMax-valMin), ypos+0.5*diameter, diameter*0.75, diameter*0.75);
    stroke(255);
  }
}

class RadioButton {
  String name;
  int xpos, ypos;
  int diameter;
  int col;
  char keyToggle;
  boolean keyCommand;
  boolean value;
  boolean DEFAULT_VALUE;
  
  RadioButton() {
    xpos = 0;
    ypos = 0;
    diameter = 15;
    col = 255;
    keyToggle = 'b';
    keyCommand = true;
    value = false;
    DEFAULT_VALUE = false;
  }
  
  void listen() {
    // Adjust click detection to match the new circle position (right side)
    float textW = textWidth(name); 
    float gap = 5; // Small gap between text and button
    float buttonX = xpos + textW + gap + diameter * 0.5; // Center X of the button
    float centerY = ypos + 0.5*diameter;
    
    float dist = dist(mouseX, mouseY, buttonX, centerY);
    if (dist < diameter * 0.5) { // Check distance from button center
        value = !value;
    }
  }
  
  void drawMe() {
    // Calculate vertical center for alignment
    float centerY = ypos + 0.5*diameter;
    float textW = textWidth(name);
    float gap = 5; // Small gap between text and button
    float buttonX = xpos + textW + gap + diameter * 0.5; // Center X of the button
    
    // Draw the text label first
    textAlign(LEFT, CENTER); 
    fill(255);
    text(name, xpos, centerY); // Draw text at original xpos
    
    // Draw the radio button circle to the right of the text
    stroke(255);
    strokeWeight(1);
    if (value) fill(col, 255);
    else noFill();
    ellipse(buttonX, centerY, diameter*0.75, diameter*0.75); // Draw circle at buttonX
  }
}

class Button {
  String name;
  int xpos, ypos;
  int bW, bH;
  int col;
  char keyToggle;
  boolean keyCommand;
  boolean isPressed;
  boolean hasBeenPressed;
  
  Button() {
    xpos = 0;
    ypos = 0;
    bW = 100;
    bH = 15;
    col = 255;
    keyToggle = 'p';
    keyCommand = true;
    isPressed = false;
    hasBeenPressed = false;
  }
  
  void listen() {
    if (mouseX > xpos && mouseX < xpos + bW && 
        mouseY > ypos && mouseY < ypos + bH) {
        isPressed = true;
        hasBeenPressed = true;
    }
  }
  
  void released() {
    isPressed = false;
  }
  
  void drawMe() {
    noStroke();
    
    // Shadow
    pushMatrix(); translate(2, 2);
    noStroke();
    fill(0, 100);
    rect(xpos, ypos, bW, bH, bH/2);
    popMatrix();
    
    // Button Background - Use lower alpha to blend in
    fill(col, 40); // Changed alpha from 150 to 40
    rect(xpos, ypos, bW, bH, bH/2);
    
    // Button Text
    fill(255);
    textAlign(CENTER, CENTER);
    text(name, xpos + 0.5*bW, ypos + 0.4*bH);
  }
}

class TriSlider {
  String name;
  String name1, name2, name3;
  int xpos, ypos;
  int col1, col2, col3;
  
  PVector corner1 = new PVector();
  PVector corner2 = new PVector();
  PVector corner3 = new PVector();
  
  PVector pt = new PVector(); // location of point
  PVector avg = new PVector(); // centroid of triangle
  float avgX, avgY;
  float r; // radius
  
  float[] values = new float[3]; // outputs 
  float d1, d2, d3; // distance from triangle corners
  float sum;
  
  boolean isDragged;
  
  TriSlider() {
    xpos = 0;
    ypos = 0;
    name = "Triangle";
    name1 = "One";
    col1 = color(255,0,0);
    name2 = "Two";
    col2 = color(0,255,0);
    name3 = "Three";
    col3 = color(0,0,255);
    isDragged = false;
  }
  
  void listen() {
    float dist = dist(mouseX, mouseY, pt.x, pt.y);
    if (dist < r) isDragged = true;
  }
  
  void useDefault() {
    pt.x = avg.x;
    pt.y = avg.y;
  }
  
  void update() {
    if (isDragged) {
      pt.x = mouseX;
      pt.y = mouseY;
    }
    calculateValues();
  }
  
  void calculateValues() {
    d1 = pt.dist(corner1);
    d2 = pt.dist(corner2);
    d3 = pt.dist(corner3);
    
    sum = d1+d2+d3;
    
    values[0] = 1.0 - d1/sum;
    values[1] = 1.0 - d2/sum;
    values[2] = 1.0 - d3/sum;
    
    sum = values[0] + values[1] + values[2];
    values[0] /= sum;
    values[1] /= sum;
    values[2] /= sum;
  }
  
  void drawMe() {
    pushStyle();
    textAlign(CENTER, CENTER);
    fill(255);
    text(name, avg.x, ypos);
    
    // Lines
    stroke(255, 50);
    strokeWeight(1);
    line(corner1.x, corner1.y, corner2.x, corner2.y);
    line(corner2.x, corner2.y, corner3.x, corner3.y);
    line(corner3.x, corner3.y, corner1.x, corner1.y);
    
    // Draw Triangle Labels
    fill(col1); text(name1 + ": " + nf(values[0], 1, 2), avg.x, ypos + 1*12);
    fill(col2); text(name2 + ": " + nf(values[1], 1, 2), avg.x, ypos + 2*12);
    fill(col3); text(name3 + ": " + nf(values[2], 1, 2), avg.x, ypos + 3*12);
    
    // Corner Circles
    noStroke();
    fill(col1); ellipse(corner1.x, corner1.y, 10, 10);
    fill(col2); ellipse(corner2.x, corner2.y, 10, 10);
    fill(col3); ellipse(corner3.x, corner3.y, 10, 10);
    
    // Slider Location
    noStroke();
    fill(255, 100);
    ellipse(pt.x, pt.y, 15, 15);
    fill(255, 255);
    ellipse(pt.x, pt.y, 15*0.75, 15*0.75);
    stroke(255);
    popStyle();
  }
} 