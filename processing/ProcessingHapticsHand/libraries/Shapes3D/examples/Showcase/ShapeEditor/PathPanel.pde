GGroup createPathEditorGUI() {
  // Make initial data #########################################    
  GGroup grp = new GGroup(this);
  GViewPeasyCam view3D;
  GView view2D;
  // 3D view  ##################################################
  view3D = new GViewPeasyCam(this, 210, 210, 190, 190, 220);
  view3D.getPeasyCam().setWheelScale(msView3D);
  view3D.getPeasyCam().setMinimumDistance(100);
  view3D.getPeasyCam().setMaximumDistance(1600);
  view3D.tag = "3D";
  view3D.addListener(new LView3D(data, LView3D.PATH_VIEW));
  grp.addControl(view3D);
  // XY view  ##################################################
  view2D = new GView(this, 10, 10, 190, 190, JAVA2D);
  view2D.tag = "XY";
  view2D.addListener(new LPathXY(data, msPath));
  grp.addControl(view2D);
  // YZ view  ##################################################
  view2D = new GView(this, 210, 10, 190, 190, JAVA2D);
  view2D.tag = "YZ";
  view2D.addListener(new LPathYZ(data, msPath));
  grp.addControl(view2D);
  // ZX view  ##################################################
  view2D = new GView(this, 10, 210, 190, 190, JAVA2D);
  view2D.tag = "ZX";
  view2D.addListener(new LPathZX(data, msPath));
  grp.addControl(view2D);
  // Shape type  ###############################################
  GToggleGroup optGroup = new GToggleGroup();
  GOption option = new GOption(this, 10, 410, 60, 40, "Spline");
  option.setIconPos(GAlign.EAST);
  option.setTextAlign(GAlign.RIGHT, GAlign.CENTER);
  option.addEventHandler(this, "pathTypeImpl");
  option.setOpaque(true);
  option.tagNo = S3D.P_BSPLINE3D;
  optGroup.addControl(option);
  option.setSelected(true);
  grp.addControl(option);
  option = new GOption(this, 70, 410, 60, 40, "Curve");
  option.addEventHandler(this, "pathTypeImpl");
  option.setOpaque(true);
  option.tagNo = S3D.P_BCURVE3D;
  optGroup.addControl(option);
  grp.addControl(option);
  // Nbr slices  ###############################################
  GLabel lblPathSlices = new GLabel(this, 130, 410, 80, 40, "   Detail:");
  lblPathSlices.setOpaque(true);
  grp.addControl(lblPathSlices);
  GCustomSlider sdrPathSlices = new GCustomSlider(this, 210, 410, 190, 40, "grey_blue");
  sdrPathSlices.setShowValue(true);
  sdrPathSlices.setLimits(data.path_detail(), 2, 100);
  sdrPathSlices.setShowLimits(true);
  sdrPathSlices.setNumberFormat(G4P.INTEGER, 0);
  sdrPathSlices.setOpaque(true);
  sdrPathSlices.addEventHandler(this, "pathSlicesChangeImpl");
  grp.addControl(sdrPathSlices);
  return grp;
}

void pathSlicesChangeImpl(GCustomSlider customslider, GEvent event) { 
  data.path_detail(customslider.getValueI());
}

void pathTypeImpl(GOption option, GEvent event) { 
  data.path_type(option.tagNo);
}
