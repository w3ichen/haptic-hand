/*
 * Copyright (c) 2020 Peter Lager
 * <quark(a)lagers.org.uk> http:www.lagers.org.uk
 * 
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 * 
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it freely,
 * subject to the following restrictions:
 * 
 * 1. The origin of this software must not be misrepresented;
 * you must not claim that you wrote the original software.
 * If you use this software in a product, an acknowledgment in the product
 * documentation would be appreciated but is not required.
 * 
 * 2. Altered source versions must be plainly marked as such,
 * and must not be misrepresented as being the original software.
 * 
 * 3. This notice may not be removed or altered from any source distribution.
 */

package shapes3d.utils;

import java.text.DecimalFormat;

import processing.core.PApplet;
import processing.core.PConstants;
import processing.core.PFont;
import processing.core.PGraphics;
import processing.core.PImage;
import processing.event.KeyEvent;
import shapes3d.S3D;
import shapes3d.Shape3D;

/**
 * An instance of this class can be used to inspect some parts of the shapes internal state
 * 
 * @author Peter Lager
 *
 */
public final class ShapeInspector implements PConstants {

	private Shape3D shape3d = null;

	private PApplet app;
	private PGraphics siGraphic;
	private float x = 0, y = 0;
	private boolean visible = true;

	private int[] row;
	private int rowH;
	private int col0 = 0xFF404040, col1 = 0xFF606060, col2 = 0xFFE8E8E8, col3 = 0xFF707070;
	private PFont lblFont, valFont;
	private int selectedPart = 0, nbrParts = 0;
	private DecimalFormat df = new DecimalFormat("#.##");

	private PImage[] skins;
	private PImage[] textures;
	private int[] modes = new int[] { S3D.SOLID, S3D.WIRE, S3D.TEXTURE };
	private String[] modeName = new String[] { "SOLID", "WIRE", "TEXTURE" };

	/**
	 * Create a ShapeInspector instance at the given posin.
	 * 
	 * @param papp the PApplet object to hook into for key events
	 * @param x horizontal position of top-left corner of the interface
	 * @param y vertical position of top-left corner of the interface
	 */
	public ShapeInspector(PApplet papp, float x, float y) {
		this.app = papp;
		this.x = x;
		this.y = y;
		lblFont = app.loadFont("Calibri-14.vlw");
		valFont = app.loadFont("Calibri-12.vlw");
		siGraphic = getDialogBaseImageGUI(papp);
	}

	/**
	 * Handle key event passed from Processing
	 * @param event key event from Processing
	 */
	public void keyEvent(KeyEvent event) {
		if(event.getAction() == KeyEvent.TYPE) {
			int k = event.getKey() - '0';
			if(k >= 0  && k < nbrParts) {
				selectedPart = k;
			}
		}
	}

	/**
	 * Do not call directly. This method is called once per frame by 
	 * Processing and updates the inspector.
	 */
	public void pre() {
		update();
	}

	/**
	 * Sets the shape to be linked to this inspector. It will start with
	 * part 0.
	 * 
	 * @param shape the shape to inspect
	 */
	public void observeShape(Shape3D shape) {
		observeShape(shape, 0);
	}

	/**
	 * Set the shape and part number to be displayed in the inspector.
	 * The partNo will be constrained to a valid value.
	 * 
	 * @param shape the 3D shape
	 * @param partNo the part to examine
	 */
	public void observeShape(Shape3D shape, int partNo) {
		// Unlink inspector from current shape
		if(shape == null) {
			if(this.shape3d != null) {
				nbrParts = selectedPart = 0;
				this.shape3d = null;
				app.unregisterMethod("pre", this);
				app.unregisterMethod("keyEvent", this);			
			}
			return;
		}
		// We have a shape to link to so find out which part is
		// to be examined
		nbrParts = shape.nbrParts();
		selectedPart = (partNo < 0) ? 0 : (partNo >= nbrParts) ? nbrParts - 1 : partNo;
		// If we are not replacing an existing shape then we need to
		// register with Processing for updates
		if(this.shape3d == null) {
			app.registerMethod("pre", this);
			app.registerMethod("keyEvent", this);						
		}
		// See if we are actually linking to a new shape
		if(this.shape3d != shape) {
			this.shape3d = shape;
			skins = new PImage[nbrParts];
			textures = new PImage[nbrParts];
		}
		updateSkins();
		update();		
	}


	/**
	 * Show / hide the inspector
	 * @param visible true to make it visible else false
	 */
	public void visible(boolean visible) {
		this.visible = visible;
	}
	
	/**
	 * 
	 * @return true if visible
	 */
	public boolean isVisible() {
		return visible;
	}
	
	/**
	 * Move the inspector to another position
	 * @param x new horizontal position
	 * @param y new vertical position
	 */
	public void move(float x, float y) {
		this.x = x;
		this.y = y;
	}
	
	/**
	 * Update the skins (textures) used by the shape
	 */
	private void updateSkins() {
		PImage[] curr = shape3d.textures();
		for(int i = 0; i < curr.length; i++ ) {
			if(curr[i] != textures[i]) {
				if(curr[i] == null) {
					textures[i] = null;
					skins[i] = null;
				}
				else {
					textures[i] = curr[i];
					skins[i] = makeSkinImage(textures[i]);
				}
			}
		}
	}

	/**
	 * Create an image of the texture to just fit the inspector's
	 * display
	 * @param texture
	 */
	private PImage makeSkinImage(PImage texture) {
		PImage img = null;
		float aspt = ((float)texture.width) / texture.height;
		int nw = 110, nh = 110;
		if(aspt > 1) {
			nh =  PApplet.round(nh / aspt);
		}
		else if (aspt < 1) {
			nw = PApplet.round(nw * aspt);
		}
		img = texture.get();
		img.resize(nw,  nh);
		return img;
	}

	/**
	 * Draw the unchanging parts of the shape-inspectors display
	 * @param papp the PApplet to draw the inspector on
	 * @return the base graphics context.
	 */
	private PGraphics getDialogBaseImageGUI(PApplet papp) {
		rowH = lblFont.getDefaultSize() + 5;
		// Remember row Y positions to save work later
		row = new int[7];
		for(int r = 0; r < row.length; r++) {
			row[r] = r * rowH;
		}
		PGraphics g = papp.createGraphics(500, 7 * rowH + 6, JAVA2D);
		g.beginDraw();
		// Main dialog background
		g.background(col1);
		g.noFill();
		g.stroke(col0);
		g.strokeWeight(2);
		g.rect(2,2,g.width-4, g.height-4);
		g.line(210, 0, 210, g.height);
		g.line(380, 0, 380, g.height);
		// Left hand side
		g.translate(2, 2);;
		g.fill(col0);
		g.noStroke();
		g.rect(0,0,210,rowH);
		g.textFont(lblFont);
		g.textAlign(CENTER, CENTER);
		g.noStroke();
		g.fill(col0);
		g.fill(col2);
		g.text("SHAPE INSPECTOR", 0, 0, 210, rowH);
		g.textAlign(LEFT, CENTER);
		g.text("Shape", 10, rowH, 40, rowH);
		g.text("Tag", 10, 2 * rowH, 40, rowH);
		//		g.textAlign(CENTER, CENTER);
		g.text("Position", 50, row[3], 70, rowH);
		g.text("Rotation", 130, row[3], 70, rowH);
		g.text("X", 18, row[4], 12, rowH);
		g.text("Y", 18, row[5], 12, rowH);
		g.text("Z", 18, row[6], 12, rowH);
		g.translate(210, 0);
		// right side (starts at 250px)
		g.textAlign(LEFT, CENTER);
		g.text("Part:", 10, row[0], 70, rowH);
		g.text("Use keys 0.. to select part", 10, row[2], 150, rowH);
		g.text("Tag", 10, row[1], 70, rowH);
		g.text("Fill", 10, row[3], 70, rowH);
		g.text("Stroke", 10, row[4], 70, rowH);
		g.textAlign(CENTER, CENTER);
		g.text("Draw Mode", 10, row[5], 150, rowH);
		// texture area
		g.translate(170, 0);
		g.text("Texture", 4, row[6], 110, rowH);
		g.endDraw();		
		return g;
	}

	/**
	 * Display the shapes overall status
	 * @param g graphics context
	 */
	private void displayLHS(PGraphics g) {
		g.pushMatrix();
		g.translate(2, 2);
		g.textFont(valFont);
		g.textAlign(CENTER, CENTER);
		displayValue(g, 50, row[1], 150, rowH, shape3d.getClass().getSimpleName());
		displayValue(g, 50, row[2], 150, rowH, shape3d.tag);
		// Display position and rotation
		float[] pos = shape3d.getPosArray();
		float[] rot = shape3d.getRotArray();
		DecimalFormat df = new DecimalFormat("#.##");
		for(int i = 0; i < pos.length; i++) {
			displayValue(g, 50, row[i + 4], 70, rowH, df.format(pos[i]));
			displayValue(g, 130, row[i + 4], 70, rowH, df.format(rot[i]));		
		}
		g.popMatrix();
	}

	/**
	 * Display shape part status
	 * @param g graphics context
	 */
	private void displayRHS(PGraphics g) {
		g.pushMatrix();
		g.translate(212, 2);
		// Part selector / indicator
		g.noStroke();
		g.fill(col1);
		g.rect(60, 2, 104, rowH - 3);
		g.textAlign(LEFT, CENTER);
		for(int i = 0; i < nbrParts; i++) {
			g.fill(i == selectedPart ? col2 : col1);
			g.rect(60 + i * 12, 2, 10, rowH-3);
			g.fill(i == selectedPart ? col0 : col2);
			g.text("" + i, 60 + i * 12 + 2, 2, rowH, rowH-3);
		}
		// Part name
		g.textAlign(CENTER, CENTER);
		displayValue(g, 60, row[1], 100, rowH, shape3d.tags()[selectedPart]);
		// Fill
		g.stroke(col0);
		g.strokeWeight(1);
		g.fill(shape3d.fills()[selectedPart]);
		g.rect(60, row[3] + 1, 30, rowH-2);
		// Stroke
		g.fill(shape3d.strokes()[selectedPart]);
		g.rect(60, row[4] + 1, 30, rowH-2);
		// Stroke weight
		float w = shape3d.strokeWeights()[selectedPart];
		displayValue(g, 100, row[4], 60, rowH, df.format(w));
		// Draw mode
		int dm = shape3d.drawModes()[selectedPart];
		for(int i = 0; i < modes.length; i++) {
			boolean on = (modes[i] & dm) == modes[i];
			g.fill(on ? col2 : col1);
			g.rect(10 + i * 52, row[6] + 1, 46, rowH-2);
			g.fill(on ? col0 : col2);
			g.text(modeName[i], 10 + i * 52, row[6] + 1, 46, rowH-2);
		}
		g.popMatrix();
	}

	/**
	 * Display the texture image for the current part.
	 * @param g graphics context
	 */
	private void displaySkin(PGraphics g){
		updateSkins();
		g.pushMatrix();
		g.translate(382, 2);
		g.fill(col3);
		g.noStroke();
		g.rect(4,4,110,110);
		if(skins[selectedPart] != null) {
			g.imageMode(CENTER);
			g.image(skins[selectedPart], 59, 59);
		}
		g.popMatrix();
	}

	/**
	 * Update the inspector visual based on the state of the shape. <br>
	 */
	private void update() {
		if(shape3d != null) {
			siGraphic.beginDraw();
			displayLHS(siGraphic);
			displayRHS(siGraphic);
			displaySkin(siGraphic);
			siGraphic.endDraw();
		}
	}

	/**
	 * Internal method to handle displaying shape attribute values.
	 * 
	 * @param g graphics context
	 * @param taX left hand side of text area
	 * @param taY top of text area
	 * @param taW text area width
	 * @param taH text area height
	 * @param text the text to display
	 */
	private void displayValue(PGraphics g, int taX, int taY, int taW, int taH, String text) {
		g.pushMatrix();
		g.translate(taX, taY);
		g.stroke(col0);
		g.strokeWeight(1);
		g.fill(col2);
		g.rect(1, 1, taW-2, taH-2);
		g.noStroke();
		g.fill(col0);
		g.text(text, 0, 0, taW, taH);
		g.popMatrix();
	}

	/**
	 * Only display the inspector if it linked to a shape and the user has made it visible. 
	 * @param pg the graphics context
	 */
	public void draw(PGraphics pg){
		if(visible && shape3d != null) {
			pg.pushMatrix();
			pg.translate(x, y);
			pg.image(siGraphic, 0, 0);
			pg.popMatrix();
		}
	}

}
