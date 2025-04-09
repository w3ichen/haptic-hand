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
import processing.core.PConstants;
import processing.core.PVector;

/**
 * Create a circular or elliptical path.
 * 
 * @author Peter Lager
 *
 */
public class Ring extends AbstractPath implements PConstants {

	protected float radX, radZ;

	/**
	 * Create a circular path
	 * 
	 * @param radius the ring radius
	 * @param nbrSlices the number of slices along ring circumference
	 */
	public Ring(float radius, int nbrSlices) {
		this(radius, radius, nbrSlices);
	}
	
	/**
	 * Create an elliptical path
	 * 
	 * @param radiusX the ring radius in X direction
	 * @param radiusZ the ring radius in Z direction
	 * @param nbrSlices the number of slices along ring circumference
	 */
	public Ring(float radiusX, float radiusZ, int nbrSlices) {
		super(nbrSlices);
		this.radX = radiusX;
		this.radZ = radiusZ;
		pathIsOpen = false;
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
				radX * PApplet.cos(t * TWO_PI),
				0,
				radZ * PApplet.sin(t * TWO_PI)
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
	 * Get the orthogonal for any point along the ring's circumference
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return the orthogonal vector
	 */
	@Override
	public PVector orthogonal(float t) {
		PVector tangent = tangent(t);
		return new PVector(-tangent.z, 0, tangent.x);
	}

}
