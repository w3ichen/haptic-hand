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
 * A path through 3D space based on the Lissajous curve. <br>
 * 
 * It is unlikely that you would want to use this path except 
 * for demonstration purposes.
 * 
 * @author Peter Lager
 *
 */
public final class Lissajous extends AbstractPath {

	private int xCoef, yCoef, zCoef;

	/**
	 * Define the detail level for a Lissajous curve with coefficients 1, 3, 5. <br>
	 * 
	 * Best result comes from using a large number of slices.
	 * 
	 * @param nbrSlices number of slices along the path length
	 */
	public Lissajous(int nbrSlices) {
		this(1, 3, 5, nbrSlices);
	}

	/**
	 * Define the 3 Lissajous coefficients and detail level. <br>
	 * 
	 * Best result comes from using small prime numbers for the coefficients, also using a large
	 * number of slices.
	 * 
	 * @param xCoef x coefficient
	 * @param yCoef y coefficient
	 * @param zCoef z coefficient
	 * @param nbrSlices number of slices along the path length
	 */
	public Lissajous(int xCoef, int yCoef, int zCoef, int nbrSlices) {
		this(xCoef, yCoef, zCoef, nbrSlices, null);
	}

	/**
	 * Define the 3 Lissajous coefficients, detail level and othogonal calculator. <br>
	 * 
	 * Best result comes from using small prime numbers for the coefficients, also using a large
	 * number of slices.
	 * 
	 * @param xCoef x coefficient
	 * @param yCoef y coefficient
	 * @param zCoef z coefficient
	 * @param nbrSlices number of slices along the path length
	 * @param ortho the orthogonal calculator to use
	 */
	public Lissajous(int xCoef, int yCoef, int zCoef, int nbrSlices, PathOrthogonal ortho) {
		super(nbrSlices);
		this.xCoef = xCoef;
		this.yCoef = yCoef;
		this.zCoef = zCoef;
		pathIsOpen = false;
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
		return new PVector(
				300 * PApplet.sin(xCoef * t * PApplet.TWO_PI),
				300 * PApplet.sin(yCoef * t * PApplet.TWO_PI + PApplet.PI/2),
				300 * PApplet.sin(zCoef * t * PApplet.TWO_PI)
				);
	}

}
