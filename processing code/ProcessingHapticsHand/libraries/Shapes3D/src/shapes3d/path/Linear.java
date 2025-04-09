/*
§ * Copyright (c) 2020 Peter Lager
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

/**
 * Defines a straight line path between any 2 points in 2D space.
 * 
 * @author Peter Lager
 *
 */
public class Linear extends AbstractPath {

	private final PVector s;
	private final PVector e;
	private final PVector delta;
	private final PVector tangent;
	private PVector orthogonal;
	
	
	/**
	 * Define the position and detail level. <br>
	 * The start and end positions must not be coincident.
	 * 
	 * @param start start position (t = 0)
	 * @param end the end position (t = 1)
	 * @param nbrSlices the number of slices along the paths length (must be &ge; 1)
	 */
	public Linear(PVector start, PVector end, int nbrSlices) {
		this(start, end, nbrSlices, null);
	}
	
	/**
	 * Define the position, detail level and orthogonal calculator to use. <br>
	 * The start and end positions must not be co-incident.
	 * 
	 * @param start start position (t = 0)
	 * @param end the end position (t = 1)
	 * @param nbrSlices the number of slices along the paths length (must be &ge; 1)
	 * @param ortho the orthogonal calculator
	 */
	public Linear(PVector start, PVector end, int nbrSlices, PathOrthogonal ortho) {
		super(nbrSlices);
		s = start.copy();
		e = end.copy();
		delta = PVector.sub(e, s);
		tangent = delta.normalize(new PVector());
		orthoCalculator = ortho;
	}
	
	/**
	 * Get the position along the path.
	 * 
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates at a position t
	 */
	@Override
	public PVector point(float t) {
		PVector vt = PVector.mult(delta, t);
		vt.add(s);
		return vt;
	}

	/**
	 * Get the normalised tangent to the path.
	 * 
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates of the tangent at position t
	 */
	@Override
	public PVector tangent(float t) {
		return tangent;
	}

	/**
	 * If you don't provide an implementation in the child class this version
	 * will attempt to find a solution that minimizes twist along the path.
	 * 
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates of the tangent orthogonal at position t
	 */
	@Override
	public PVector orthogonal(float t) {
		if(orthoCalculator == null) {
			orthoCalculator = PathOrthogonal.getBest(this, 2);
		}
		orthogonal = orthoCalculator.getOrthogonal(tangent);
		return orthogonal;
	}	
	
	public String toString() {
		String d = "###### Linear Path ######\n";
		d += "From " + s + "  to  " + e +"\n";
		d += "Range    " + delta + "\n";
		d += "Tangent  " + tangent + "\n";
		d += "#########################";		
		return d;
	}


}
