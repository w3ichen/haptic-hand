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

import processing.core.PVector;

public interface Path {


	/**
	 * Get the position along the path.
	 * 
	 * @param t &ge;0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates at a position t
	 */
	public PVector point(float t);

	/**
	 * Get the normalised tangent to the path.
	 * 
	 * @param t &ge;0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates of the tangent at position t
	 */
	public PVector tangent(float t);

	/**
	 * Get the best vector orthogonal to the path tangent.
	 * 
	 * @param t &ge;0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates of the tangent orthogonal at position t
	 */
	public PVector orthogonal(float t);

	/**
	 * 
	 * @return the number of slices to use in this path
	 */
	public int nbrSlices();

	/**
	 * The path may or may not be open. For most paths this will always be 
	 * false e.g. Spiral; for some it is always true e.g. Torus and for some
	 * it is a user option e.g. BSpline. <br>
	 * 
	 * @return false if the path forms a closed loop, else true
	 */
	public boolean isOpenPath();

}
