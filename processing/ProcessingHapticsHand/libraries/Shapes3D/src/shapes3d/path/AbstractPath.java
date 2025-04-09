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

import processing.core.PConstants;
import processing.core.PVector;
import shapes3d.utils.SConstants;

/**
 * Defines the path that a tubular or extruded shape follows in 3D space. <br>
 * The parametric parameter 't' defines a position along the path where t=0 is 
 * the start and t=1 the end of the shape. <br>
 * 
 * Values of outside the range &ge;0 and &le;1 are not on the path and need not
 * be defined in any class implementing this interface.<br>
 * 
 * The attribute <code>nbrSlices</code> does not affect the shape or the path, 
 * it only affects the level of detail in shapes using the path. <br>
 * 
 * @author Peter Lager
 *
 */
public abstract class AbstractPath implements Path, SConstants, PConstants {

	public PathOrthogonal orthoCalculator = null;

	protected final int DEFAULT_NBR_SLICES = 100;
	protected final int nbrSlices;

	protected boolean pathIsOpen = true;

	/**
	 * 
	 * @param nbrSlices
	 */
	protected AbstractPath() {
		this.nbrSlices = DEFAULT_NBR_SLICES;
	}

	/**
	 * 
	 * @param nbrSlices
	 */
	protected AbstractPath(int nbrSlices) {
		this.nbrSlices = nbrSlices;
	}

	/**
	 * 
	 * @return the number of slices to use in this path
	 */
	public int nbrSlices() {
		return nbrSlices;
	}

	/**
	 * Get the position along the path.
	 * 
	 * @param t &ge;0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates at a position t
	 */
	public abstract PVector point(float t);

	/**
	 * Get the normalised tangent to the path.
	 * 
	 * @param t &ge;0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates of the tangent at position t
	 */
	public PVector tangent(float t) {
		return (PVector.sub(point(t + ONE_DEG_T), point(t - ONE_DEG_T))).normalize();
	}

	/**
	 * If you don't provide an implementation in the child class this version
	 * will attempt to find a solution that minimizes twist along the path.
	 * 
	 * @param t &ge;0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates of the tangent orthogonal at position t
	 */
	public PVector orthogonal(float t){
		if(orthoCalculator == null) {
			orthoCalculator = PathOrthogonal.getBest(this, nbrSlices);
		}
		return orthoCalculator.getOrthogonal(tangent(t));
	}

	/**
	 * 
	 * @return false if the path forms a closed loop, else true
	 */
	public boolean isOpenPath() {
		return pathIsOpen;
	}

}
