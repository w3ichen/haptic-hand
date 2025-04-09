GGroup createContourEditorGUI() {
  // Make initial data #########################################    
  GGroup grp = new GGroup(this);
  // Make listeners
  polygonListener = new LPolygon(data, msContour);
  registerMethod("pre", polygonListener);
  ovalListener = new LOval(data, msContour);
  // Create view and start with polygon listener (Extrusion)
  viewContour = new GView(this, 10, 10, 160, 160, JAVA2D);
  viewContour.tag = "Contour";
  viewContour.addListener(polygonListener);
  viewContour.tag = "Contour";
  grp.addControl(viewContour);
  GToggleGroup optContourGroup = new GToggleGroup();
  GOption option = new GOption(this, 10, 180, 70, 20, "Oval");
  option.setIconPos(GAlign.EAST);
  option.setTextAlign(GAlign.RIGHT, GAlign.CENTER);
  option.addEventHandler(this, "contourTypeImpl");
  option.setOpaque(true);
  option.tagNo = S3D.C_OVAL;
  optContourGroup.addControl(option);
  grp.addControl(option);
  option = new GOption(this, 80, 180, 90, 20, "Polygon");
  option.addEventHandler(this, "contourTypeImpl");
  option.setOpaque(true);
  option.tagNo = S3D.C_POLYGON;
  optContourGroup.addControl(option);
  option.setSelected(true);
  grp.addControl(option);
  // Custom slider for number of segments in oval contour
  sdrOvalSegs = new GCustomSlider(this, 220, 10, 160, 40, "grey_blue");
  sdrOvalSegs.setShowValue(true);
  sdrOvalSegs.setShowLimits(true);
  sdrOvalSegs.setTextOrientation(G4P.ORIENT_LEFT);
  sdrOvalSegs.setRotation(PI/2, GControlMode.CORNER);
  sdrOvalSegs.setLimits(data.nbrOvalSegs(), 3, 30);
  sdrOvalSegs.setNumberFormat(G4P.INTEGER, 0);
  sdrOvalSegs.setOpaque(true);
  sdrOvalSegs.addEventHandler(ovalListener, "processChangeNbrSegs");
  sdrOvalSegs.setVisible(false);
  grp.addControl(sdrOvalSegs);
  // Custom slider for polygon angle
  sdrPolyAngle = new GCustomSlider(this, 220, 10, 150, 40, "blue18px");
  sdrPolyAngle.setNbrTicks(3);
  sdrPolyAngle.setShowTicks(true);
  sdrPolyAngle.setEasing(6);
  sdrPolyAngle.setTextOrientation(G4P.ORIENT_LEFT);
  sdrPolyAngle.setRotation(PI/2, GControlMode.CORNER);
  sdrPolyAngle.setLimits(0, -PI, PI);
  sdrPolyAngle.setOpaque(true);
  sdrPolyAngle.addEventHandler(polygonListener, "processAngleEvent");
  grp.addControl(sdrPolyAngle);
  // Shift all stick
  s2dShift = new GSlider2D(this, 180, 160, 40, 40);
  s2dShift.setEasing(6);
  s2dShift.setLimitsX(0.0f, -0.1f, 0.1f);
  s2dShift.setLimitsY(0.0f, -0.1f, 0.1f);
  s2dShift.setOpaque(true);
  s2dShift.addEventHandler(polygonListener, "processShiftEvent");
  grp.addControl(s2dShift);
  // Button  to constrain tube to circle
  btnCircleConstraint = new GImageToggleButton(this, 180, 180, filepath + "tubexsection.png", 2);
  btnCircleConstraint.setState(LOval.OVAL);
  btnCircleConstraint.setVisible(false);
  btnCircleConstraint.addEventHandler(ovalListener, "processSectionConstraint");
  grp.addControl(btnCircleConstraint);
  // ==============================================================================
  // ==============================================================================
  // Scale view
  viewScale = new GView(this, 230, 60, 170, 110, JAVA2D);
  scaleXListener = new LScale(data, msScale, 'X');
  scaleYListener = new LScale(data, msScale, 'Y');
  // start with x scale
  viewScale.addListener(scaleXListener);  
  viewScale.tag = "X";
  grp.addControl(viewScale);
  // ==============================================================================
  // Scale X / Y selector
  GLabel label = new GLabel(this, 230, 10, 110, 20, "Scale Axis ---");
  label.setOpaque(true);
  grp.addControl(label);
  GToggleGroup optGroup = new GToggleGroup();
  option = new GOption(this, 370, 10, 30, 20, "Y");
  option.tag = "Y";
  option.addEventHandler(this, "scaleAxisImpl");
  option.setOpaque(true);
  optGroup.addControl(option);
  grp.addControl(option);
  option = new GOption(this, 340, 10, 30, 20, "X");
  option.tag = "X";
  option.addEventHandler(this, "scaleAxisImpl");
  option.setOpaque(true);
  optGroup.addControl(option);
  option.setSelected(true);
  grp.addControl(option);
  // ==============================================================================
  // Bezier curve / spline selector
  optGroup = new GToggleGroup();
  option = new GOption(this, 230, 30, 90, 20, "Spline");
  option.setIconPos(GAlign.EAST);
  option.setTextAlign(GAlign.RIGHT, GAlign.CENTER);
  option.addEventHandler(this, "scalerTypeImpl");
  option.setOpaque(true);
  option.tagNo = S3D.P_BSPLINE2D;
  optGroup.addControl(option);
  grp.addControl(option);
  option = new GOption(this, 320, 30, 80, 20, "Curve");
  option.addEventHandler(this, "scalerTypeImpl");
  option.setOpaque(true);
  option.tagNo = S3D.P_BCURVE2D;
  optGroup.addControl(option);
  option.setSelected(true);
  grp.addControl(option);
  // ==============================================================================
  // Copy X > Y or Y > X or RESET buttons
  GButton btn = new GButton(this, 230, 230, 40, 20, "X-Y");
  btn.tag = "X2Y";
  btn.addEventHandler(this, "copyScalerData");
  grp.addControl(btn);
  btn = new GButton(this, 280, 230, 40, 20, "Y-X");
  btn.tag = "Y2X";
  btn.addEventHandler(this, "copyScalerData");
  grp.addControl(btn);
  btn = new GButton(this, 330, 230, 70, 20, "Reset");
  btn.tag = "RESET";
  btn.addEventHandler(this, "resetScalerData");
  grp.addControl(btn);
  // ==============================================================================
  // the number of points used in the scaler (2-10)
  GCustomSlider sdrScaleDetail = new GCustomSlider(this, 230, 180, 170, 20, "grey_blue");
  sdrScaleDetail.setLimits(data.scale_detail(), 2, 20);
  sdrScaleDetail.setNbrTicks(19);
  sdrScaleDetail.setStickToTicks(true);
  sdrScaleDetail.setNumberFormat(G4P.INTEGER, 0);
  sdrScaleDetail.setOpaque(true);
  sdrScaleDetail.addEventHandler(this, "scaleDetailImpl");
  grp.addControl(sdrScaleDetail);
  GLabel lblScaleDetail = new GLabel(this, 230, 200, 130, 20, "No. of control points");
  lblScaleDetail.setTextAlign(GAlign.LEFT, null);
  lblScaleDetail.setOpaque(true);
  grp.addControl(lblScaleDetail);
  lblNbrPoints = new GLabel(this, 360, 200, 40, 20, "" + data.scale_detail());
  lblNbrPoints.setOpaque(true);
  lblNbrPoints.setTextAlign(GAlign.CENTER, null);
  grp.addControl(lblNbrPoints);
  // ==============================================================================
  // Path Orthogonal
  label = new GLabel(this, 230, 278, 140, 20, "Path Orthogonal");
  label.setOpaque(true);
  label.setTextAlign(GAlign.CENTER, GAlign.MIDDLE);
  grp.addControl(label);
  GDropList dl = new GDropList(this, 230, 300, 140, 120, 5, 20);
  String[] items = { "Default", "X orthogonal", "Y orthogonal", "Z orthogonal", "A orthogonal" }; 
  dl.setItems(items, 0);
  dl.addEventHandler(this, "setOrthoData");
  grp.addControl(dl);  
  // ==============================================================================
  // 3D view of shape
  GViewPeasyCam view3D;
  view3D = new GViewPeasyCam(this, 10, 210, 210, 210, 300);
  view3D.getPeasyCam().setWheelScale(msView3D);
  view3D.getPeasyCam().setMinimumDistance(100);
  view3D.getPeasyCam().setMaximumDistance(1600);
  view3D.tag = "Contour 3D";
  view3D.addListener(new LView3D(data, LView3D.CONTOUR_VIEW));
  grp.addControl(view3D);
  grp.setAlpha(0);
  return grp;
}

void scaleDetailImpl(GCustomSlider customslider, GEvent event) { 
  int n = customslider.getValueI();
  data.scale_detail(n, !customslider.isDragging());
  lblNbrPoints.setText("" + n);
}

void setOrthoData(GDropList droplist, GEvent event) {
  switch(droplist.getSelectedIndex()) {
  case 1:
    data.path_othogonal(S3D.ORTHO_X);
    break;
  case 2:
    data.path_othogonal(S3D.ORTHO_Y);
    break;
  case 3:
    data.path_othogonal(S3D.ORTHO_Z);
    break;
  case 4:
    data.path_othogonal(S3D.ORTHO_A);
    break;
  default:
    data.path_othogonal(null);
  }
}

void scaleAxisImpl(GOption option, GEvent event) {
  switch(option.tag) {
  case "X":
    viewScale.removeListener();
    viewScale.addListener(scaleXListener);
    viewScale.tag = "X";
    break;
  case "Y":
    viewScale.removeListener();
    viewScale.addListener(scaleYListener);
    viewScale.tag = "Y";
  }
}

void scalerTypeImpl(GOption option, GEvent event) {
  data.scale_type = option.tagNo;
  data.remake_scalers(true, true);
}

void copyScalerData(GButton button, GEvent event) {
  data.copy_scaler(button.tag);
}

public void resetScalerData(GButton button, GEvent event) {
  data.restore_scaler_original_data();
  data.remake_scalers(true, true);
  data.use_scaler(false);
}

// Change GUI depending whether we using a polygon or an oval
void contourTypeImpl(GOption option, GEvent event) { 
  switch(option.tagNo) {
  case S3D.C_POLYGON:
    viewContour.removeListener();
    viewContour.addListener(polygonListener);
    sdrOvalSegs.setVisible(false);
    btnCircleConstraint.setVisible(false);
    sdrPolyAngle.setVisible(true);
    s2dShift.setVisible(true);
    break;
  case S3D.C_OVAL:
    viewContour.removeListener();
    viewContour.addListener(ovalListener);
    sdrOvalSegs.setVisible(true);
    btnCircleConstraint.setVisible(true);
    sdrPolyAngle.setVisible(false);
    s2dShift.setVisible(false);
    break;
  }
  data.contour_type(option.tagNo);
}
