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

package shapes3d.contour;

import processing.core.PApplet;
import processing.core.PVector;
import shapes3d.utils.UV;

/**
 * This class represents a circular or elliptical cross-section for a Tube shape.
 * 
 * @author Peter Lager
 *
 */
public final class Oval extends Contour {

	protected PVector[] coords;
	protected UV[] uvNorm;

	protected float radiusX, radiusY;
	
	/**
	 * Prevent use of the default constructor so user must
	 * provide the details.
	 */
	@SuppressWarnings("unused")
	private Oval() {}

	/**
	 * Create a circular cross-section. <br>
	 * The more segments you choose the smoother the tube surface.
	 * 
	 * @param radius the circle radius
	 * @param nbrSegs number of segments
	 */
	public Oval(float radius, int nbrSegs) {
		this(radius, radius, nbrSegs);
	}
	
	/**
	 * Create a elliptical cross-section. <br>
	 * The more segments you choose the smoother the tube surface.
	 * 
	 * @param radiusX radius for one axis of the ellipse
	 * @param radiusY radius for the other axis of the ellipse
	 * @param nbrSegs the number of segments making up the Oval
	 */
	public Oval(float radiusX, float radiusY, int nbrSegs) {
		super();
		this.nbrSegs = nbrSegs;
		this.radiusX = radiusX;
		this.radiusY = radiusY;
		calcSection();
	}
	
	/** 
	 * @return  the [x, y, 0] coordinates for the vertices defining this oval
	 */
	public PVector[] coords() {
		return coords;
	}
	
	/**
	 * Create un-transformed coordinates for the Oval
	 * [0] oval center
	 * [1] &gt; [nbrSegs] closed loop in CCW order
	 */
	public void calcSection() {
		coords = new PVector[nbrSegs + 1];
		UV[] uvTemp = new UV[nbrSegs + 1];
		float deltaAngle = TWO_PI / nbrSegs;
		for(int s = 0; s < nbrSegs; s++) {
			float a = - s * deltaAngle;
			coords[s] = new PVector(radiusX * PApplet.cos(a), radiusY * PApplet.sin(a), 0);
			uvTemp[s] = new UV((1 - PApplet.cos(a))/2, (1 + PApplet.sin(a))/2);
		}
		coords[nbrSegs] = coords[0].copy();
		uvTemp[nbrSegs] = uvTemp[0].copy();
		uvNorm = new UV[uvTemp.length + 1];
		System.arraycopy(uvTemp, 0, uvNorm, 1, uvTemp.length);
		uvNorm[0] = new UV(0.5f, 0.5f);		
	}
	
	/**
	 * @return the texture coordinates for this Oval
	 */
	public UV[] uv() {
		return uvNorm;
	}
	
	/**
	 * @return the Oval that is a mirror of this one.
	 */
	public Oval mirror() {
		Oval mirror = new Oval(radiusX, radiusY, nbrSegs);
		for(int i = 0; i < uvNorm.length; i++) {
			mirror.uvNorm[i].u = 1 - mirror.uvNorm[i].u;
		}
		return mirror;
	}

}
