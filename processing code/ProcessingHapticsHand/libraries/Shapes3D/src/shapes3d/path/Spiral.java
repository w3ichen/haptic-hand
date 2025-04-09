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

package shapes3d.path;

import processing.core.PApplet;
import processing.core.PVector;

/**
 * This class represents a spiral or helical path. The spiral can 
 * be of any length and the path can be either circular or elliptical.
 * 
 * @author Peter Lager
 *
 */
public class Spiral extends AbstractPath {

	protected float nbrTwirls = 1;
	protected float twirlPitch = 10;
	protected float radX, radZ;
	
	// Calculated form ctor
	protected float startY;
	
	protected float spiralAngle;
	protected float spiralPitch;
	
	/**
	 * Hide default constructor
	 */
	protected Spiral() {}
	
	/**
	 * Create an circular path
	 * 
	 * @param radius the spiral radius
	 * @param nbr_twirls number times the path does a full 360&deg;
	 * @param twirl_pitch the distance between adjacent twirls.
	 * @param nbrSlices the number of slices along spiral length	 
	 */
	public Spiral(float radius, float nbr_twirls, float twirl_pitch, int nbrSlices) {
		this(radius, radius, nbr_twirls, twirl_pitch, nbrSlices);
	}
	
	/**
	 * Create an elliptical path
	 * 
	 * @param radiusX the spiral radius in X direction
	 * @param radiusZ the spiral radius in Z direction
	 * @param nbr_twirls number times the path does a full 360&deg;
	 * @param twirl_pitch the distance between adjacent twirls.
	 * @param nbrSlices the number of slices along spiral length	 
	 */
	public Spiral(float radiusX, float radiusZ, float nbr_twirls, float twirl_pitch, int nbrSlices) {
		super(nbrSlices);
		this.radX = radiusX;
		this.radZ = radiusZ;
		this.nbrTwirls = nbr_twirls;
		this.twirlPitch = twirl_pitch;
		
		startY = -nbrTwirls * twirlPitch / 2;
		spiralAngle = nbrTwirls * TWO_PI;
		spiralPitch = nbrTwirls * twirlPitch;
		pathIsOpen = true;
	}

	/**
	 * Get the position along the path.
	 * 
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates at a position t
	 */
	@Override
	public PVector point(float t) {
		return new PVector(
				radX * PApplet.cos(t * spiralAngle),
				t * spiralPitch + startY,
				radZ * PApplet.sin(t * spiralAngle)
				);
	}

	/**
	 * Get the normalised tangent to the path.
	 * 
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates of the tangent at position t
	 */
	@Override
	public PVector tangent(float t) {
		return (PVector.sub(point(t + ONE_DEG_T), point(t - ONE_DEG_T))).normalize();
	}

	/**
	 * Get the orthogonal for any point along the spiral's length
	 * @return the orthogonal vector
	 */
	@Override
	public PVector orthogonal(float t) {
		PVector tangent = tangent(t);
		return new PVector(-tangent.z, 0, tangent.x);
	}

}
