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

import processing.core.PConstants;
import shapes3d.path.Path;

/**
 * This class defines the shape and radial extent of a LatheStock object.
 * 
 * @author Peter Lager
 *
 */
public final class LatheSurface extends Contour implements PConstants {


	protected Path path = null;

	protected final float startAngle, endAngle, deltaAngle;
	

	/**
	 * A full 360&deg; surface
	 * 
	 * @param path the surface contour (in the XY plane)
	 * @param nbrSegs number of radial segments to use
	 */
	public LatheSurface(Path path, int nbrSegs) {
		this(path, nbrSegs, 0f, TWO_PI);
	}
	
	/**
	 * A part surface where the start and end angles are specified in the
	 * parameters. <br>
	 * The end angle must be greater than the start angle and the difference
	 * between them must be &lt; 2&pi;. If the supplied angle values are do not
	 * meet these conditions they are modified so that they do.
	 * 
	 * @param path the surface contour (in the XY plane)
	 * @param nbrSegs nbrSegs number of radial segments to use
	 * @param startAngle the radial start of the surface
	 * @param endAngle the radial start of the surface
	 */
	public LatheSurface(Path path, int nbrSegs, float startAngle, float endAngle) {
		super();
		this.path = path;
		this.nbrSegs = nbrSegs;
		startAngle = fixAngle(startAngle);
		endAngle = fixAngle(endAngle);
		if(startAngle >= endAngle) {
			endAngle += TWO_PI;
		}
		this.startAngle = startAngle;
		this.endAngle = endAngle;
		this.deltaAngle = (endAngle - startAngle) / this.nbrSegs;
	}
	
	/**
	 * 
	 * @return the path representing the curved surface
	 */
	public Path path() {
		return path;
	}
		
	/**
	 * @return the radial start angle 
	 */
	public float startAngle() {
		return startAngle;
	}

	/**
	 * @return the radial end angle
	 */
	public float endAngle() {
		return endAngle;
	}

	/**
	 * @return the radial size of the shape in radians
	 */
	public float deltaAngle() {
		return deltaAngle;
	}

	
	/**
	 * Forces the angle into the range 0-2&pi; by repeatably adding or 
	 * subtracting 2&pi; until its fixed!
	 */
	private float fixAngle(float a) {
		while(a < 0) {
			a += TWO_PI;			
		}
		while( a > TWO_PI) {
			a -= TWO_PI;
		}
		return a;
	}
}
