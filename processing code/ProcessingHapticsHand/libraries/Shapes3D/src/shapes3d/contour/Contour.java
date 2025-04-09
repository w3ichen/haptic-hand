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
import processing.core.PVector;
import shapes3d.utils.SConstants;

/**
 * The base class for all contours.i.e. LatheSurface, Polygon and Oval <br>
 * 
 * It provides some utility methods for manipulating the vertices.
 * 
 * @author Peter Lager
 *
 */
public class Contour implements SConstants, PConstants {
	
	protected int nbrSegs;
	
	/**
	 * The contour detail level.
	 * 
	 * @return number of segments
	 */
	public int nbrSegs() {
		return nbrSegs;
	}
	
	/**
	 * Utility method to rotate an array of PVectors that 
	 * represent a 2D contour in the XY plane. <br>
	 * Rotates each vector 90&deg; clockwise.
	 * 
	 * @param vectors the vectors to be used in the contour
	 * @return the modified array.
	 */
	public static PVector[] rotateCW(PVector[] vectors) {
		for(PVector v : vectors) {
			float nx = v.y;
			float ny = -v.x;
			v.x = nx;
			v.y = ny;
		}
		return vectors;
	}
	
	/**
	 * Utility method to rotate an array of PVectors that 
	 * represent a 2D contour in the XY plane. <br>
	 * Rotates each vector 90&deg; counter-clockwise.
	 * 
	 * @param vectors the vectors to be used in the contour
	 * @return the modified array.
	 */
	public static PVector[] rotateCCW(PVector[] vectors) {
		for(PVector v : vectors) {
			float nx = -v.y;
			float ny = v.x;
			v.x = nx;
			v.y = ny;
		}
		return vectors;
	}
	
	/**
	 * Utility method to vertically flip an array of PVectors 
	 * that represent a 2D contour in the XY plane. <br>
	 * 
	 * @param vectors the vectors to be used in the contour
	 * @return the modified array.
	 */
	public static PVector[] flipV(PVector[] vectors) {
		for(PVector v : vectors) {
			v.y = -v.y;
		}
		return vectors;
	}
	
	/**
	 * Utility method to horizontally flip an array of PVectors 
	 * that represent a 2D contour in the XY plane. <br>
	 * 
	 * @param vectors the vectors to be used in the contour
	 * @return the modified array.
	 */
	public static PVector[] flipH(PVector[] vectors) {
		for(PVector v : vectors) {
			v.x = -v.x;
		}
		return vectors;
	}
	
	
}
