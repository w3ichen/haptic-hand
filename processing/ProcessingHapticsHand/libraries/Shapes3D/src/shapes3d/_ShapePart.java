/*
 * Copyright (c) 2019 Peter Lager
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

package shapes3d;

import processing.core.PApplet;
import processing.core.PConstants;
import processing.core.PGraphics;
import processing.core.PImage;
import processing.video.Movie;
import shapes3d.utils.SConstants;
import shapes3d.utils.Textures;
import shapes3d.utils.TransformUV;

/**
 * Some shapes can't be drawn with a single mesh, so these shapes 
 * have multiple parts. For instance a Tube has 3 parts the main 
 * curved body and the two end caps. <br>
 * This class represents a single shape part. It is the parent 
 * class for all shape parts. <br>
 * 
 * @author Peter Lager
 *
 */
public abstract class _ShapePart implements SConstants, PConstants {

	protected int fillColor			= BLUE;
	protected int strokeColor		= YELLOW;
	protected float strokeWeight	= 2.0f;
	protected int drawMode			= SOLID | WIRE;
	protected boolean visible 		= true;

	protected boolean useSolid;
	protected boolean useWire;
	protected boolean useTexture;
	protected PImage skin			= null;
	
	// Texture coordinates
	protected TransformUV transformer = TransformUV.ROT0;
	protected float u0 = 0;
	protected float u1 = 1;
	protected float v0 = 0;
	protected float v1 = 1;
	protected int wrap = REPEAT;
	protected final int partPickColor;

	public String tag;
	
	/**
	 * Base ctor for all shape parts
	 * @param ppCol the pick color
	 */
	protected _ShapePart(int ppCol) {
		partPickColor = ppCol;
	}

	/**
	 * Base ctor for all parts
	 * @param ppCol the pick color
	 * @param tag user defined identifier.
	 */
	protected _ShapePart(int ppCol, String tag) {
		partPickColor = ppCol;
		this.tag = tag;
	}

	/**
	 * Apply image as texture
	 * @param image the image to set
	 */
	public void texture(PImage image) {
		if(skin instanceof Movie) {
			Textures.removeMovie((Movie) skin, this);
		}
		skin = image;
	}

	/**
	 * Apply movie as texture.
	 * 
	 * @param pApplet gives access to Processing methods/functions
	 * @param movie the movie to use as the texture
	 */
	public void movie(PApplet pApplet, PImage movie) {
		if(skin != movie) {
			if(skin instanceof Movie) {
				Textures.removeMovie((Movie) skin, this);
			}
			if(movie instanceof Movie) { // Make sure its a movie
				Textures.addMovie(pApplet, movie, this);
			}
			skin = movie;
		}
	}

	/**
	 * Set the texture coordinates.
	 * 
	 * @param u0 horizontal left coordinate
	 * @param u1 horizontal right coordinate
	 * @param v0 vertical left coordinate
	 * @param v1 vertical right coordinate
	 * @return this shape part
	 */
	public _ShapePart uv(float u0, float u1, float v0, float v1) { 
		this.u0 = u0;
		this.u1 = u1;
		this.v0 = v0;
		this.v1 = v1;
		applyUV();
		return this;
	}

	// MAKE THIS ABSTRACT WHEN ALL SUB CLASSES FIXED
	protected abstract _ShapePart applyUV() ;
	
	/**
	 * This provides the default implementation for shape parts 
	 * which is do nothing.
	 * @param nbrColSlices number of slices in x direction
	 * @param nbrRowSlices  number of slices in direction orthogonal to x
	 * @return this shape part
	 */
	public _ShapePart mesh(int nbrColSlices, int nbrRowSlices) {
		return this;
	}
	
	/**
	 * Transform the texture [uv] coordinates
	 * @param transformer the uv transformer object
	 * @return this shape part
	 */
	public _ShapePart uvt(TransformUV transformer){
		this.transformer = transformer;
		applyUV();
		return this;
	};

	/**
	 * set the texture wrap attribute. The parameter must be either 
	 * REPEAT or CLAMP, any other value will be ignored. 
	 * @param wrap REPEAT or CLAMP
	 * @return this shape part
	 */
	public _ShapePart uvwrap(int wrap) {
		if(wrap == REPEAT || wrap == CLAMP) {
		this.wrap = wrap;
		}
		return this;
	}
	
	// *************************************************
	
	/**
	 * Sets the visibility of this shape part
	 * @param visible the visible to set
	 */
	public void visible(boolean visible) {
		this.visible = visible;
	}

	/**
	 * Sets the fill color of this shape part
	 * @param fillColor the fillColor to set
	 * @return this shape part
	 */
	public _ShapePart fill(int fillColor) {
		this.fillColor = fillColor;
		return this;
	}

	/**
	 * Sets the stroke color of this shape part
	 * @param col the strokeColor to set
	 * @return this shape part
	 */
	public _ShapePart stroke(int col) {
		this.strokeColor = col;
		return this;
	}

	/**
	 * Sets the stroke weight of this shape part
	 * @param weight the strokeWeight to set
	 * @return this shape part
	 */
	public _ShapePart strokeWeight(float weight) {
		this.strokeWeight = weight;
		return this;
	}

	/**
	 * Sets the draw mode of this shape part
	 * @param mode the drawMode to set
	 * @return this shape part
	 */
	public _ShapePart drawMode(int mode) {
		this.drawMode = mode;
		return this;
	}

	/**
	 * Used internally to convert drawmode into 3 boolean values for the
	 * three draw modes.
	 */
	protected void drawWhat(){
		useSolid = ((drawMode & SOLID) == SOLID);
		useWire = ((drawMode & WIRE) == WIRE);
		useTexture = ((drawMode & TEXTURE) == TEXTURE && skin != null);
	}

	/**
	 * Used internally to check the validity of an integer value
	 * as a draw mode
	 * @return true if mode is a valid draw mode.
	 */
	protected boolean isValidDrawMode(int mode) {
		mode &= DRAWALL; // Clear all unused bits
		boolean validMode = ((mode & WIRE) == WIRE);
		validMode |= ((mode & SOLID) == SOLID);
		validMode |= ((mode & TEXTURE) == TEXTURE && skin != null);
		return validMode;
	}

	/**
	 * Draw this part on to a graphics context
	 * @param pg the graphics context
	 */
	public abstract void draw(PGraphics pg);

	/**
	 * Draw this part on to a graphics context
	 * @param pg the pick buffer graphics context
	 */
	public abstract void drawPickBuffer(PGraphics pg);

	/**
	 * @return true if visible
	 */
	public boolean isVisible() {
		return visible;
	}

	/**
	 * @return the strokeWeight
	 */
	public float strokeWeight() {
		return strokeWeight;
	}

	/**
	 * @return the fillColor
	 */
	public int fill() {
		return fillColor;
	}

	/**
	 * @return the strokeColor
	 */
	public int stroke() {
		return strokeColor;
	}

	/**
	 * @return the drawMode
	 */
	public int drawMode() {
		return drawMode;
	}

	/**
	 * @return the texture image
	 */
	public PImage texture() {
		return skin;
	}

}
