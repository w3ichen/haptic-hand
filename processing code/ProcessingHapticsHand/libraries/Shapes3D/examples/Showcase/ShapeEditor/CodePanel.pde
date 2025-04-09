GGroup createCodePanel() {
  GGroup grp = new GGroup(this);
  code = new GTextArea(this, 10, 10, 390, 400, 
    G4P.SCROLLBARS_VERTICAL_ONLY | G4P.SCROLLBARS_AUTOHIDE);
  code.setFont(new Font("Monospaced", Font.PLAIN, 9));
  grp.addControl(code);
  GButton btn = new GButton(this, 10, 414, 390, 36, "Copy sketch code to clipboard");
  btn.setLocalColorScheme(GCScheme.RED_SCHEME);
  btn.setTextBold();
  btn.addEventHandler(this, "copyTextImpl");
  grp.addControl(btn);
  grp.setAlpha(0);
  return grp;
}

void copyTextImpl(GButton button, GEvent event) { 
  String[] sketch_lines = code.getTextAsArray();
  String sketch_code = join(sketch_lines, "\n");
  GClip.copy(sketch_code);
}

String getSketchCode() {
  StringBuilder s = new StringBuilder();
  // Initial part of the template
  s.append(template_part_1)
    // Shape maker code
    .append(data.codePath())
    .append(data.codeSection())
    .append(data.codeScaler())
    .append(data.codeMakeShape())
    // Last part of template
    .append(template_part_2);
  return s.toString();
}

void getCodeTemplate() {
  String[] code_template = loadStrings(filepath + "core-code.txt");
  StringBuilder s = new StringBuilder();
  // First part of template
  int idx = 0;
  while (!code_template[idx].startsWith("##################")) {
    s.append(code_template[idx++]).append(" \n");
  }
  template_part_1 = s.toString();
  // Last part of template
  s = new StringBuilder();
  idx++;
  while (idx < code_template.length) {
    s.append(code_template[idx++]).append(" \n");
  }
  template_part_2 = s.toString();
}
