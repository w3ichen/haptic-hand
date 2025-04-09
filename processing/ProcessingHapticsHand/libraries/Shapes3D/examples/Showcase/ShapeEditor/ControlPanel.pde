GGroup createControlPanel() {
  GGroup grp = new GGroup(this);
  GButton btn = new GButton(this, 430, 10, 140, 36, "Path Editor");
  btn.setLocalColorScheme(G4P.GREEN_SCHEME);
  btn.setTextBold();
  btn.tagNo = 127;
  btn.tag = "path";
  grp.addControl(btn);
  btn = new GButton(this, 430, 50, 140, 36, "Contour Editor");
  btn.setLocalColorScheme(G4P.GREEN_SCHEME);
  btn.setTextBold();
  btn.tagNo = 127;
  btn.tag = "contour";
  grp.addControl(btn);
  btn = new GButton(this, 430, 90, 140, 36, "Code Editor");
  btn.setLocalColorScheme(G4P.GREEN_SCHEME);
  btn.setTextBold();
  btn.tagNo = 127;
  btn.tag = "code";
  grp.addControl(btn);
  return grp;
}
