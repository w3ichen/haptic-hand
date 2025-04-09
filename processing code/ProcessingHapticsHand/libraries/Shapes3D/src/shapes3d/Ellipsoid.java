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

package shapes3d;

import processing.core.PVector;
import shapes3d.org.apache.commons.math.geometry.Vector3D;
import shapes3d.utils.Orientation;
import shapes3d.utils.UV;
import shapes3d.utils.Util;

/**
 * Class to represent an axis aligned ellipsoid.
 * 
 * @author Peter Lager
 *
 */
public class Ellipsoid extends Shape3D {

	protected PVector[][] coord;
	protected PVector[][] normals;
	protected UV[][] uv01;

	protected int nbrSlices;
	protected int nbrSegs;
	protected float radX, radY, radZ;
	protected Orientation orientation;

	/**
	 * Create a sphere of the given size and detail.
	 * @param rad the radius
	 * @param nbrSegs number of segments in EW direction
	 * @param nbrSlices number of slices in NS direction
	 */
	public Ellipsoid(float rad, int nbrSegs, int nbrSlices) {
		this(rad, rad, rad, nbrSegs, nbrSlices, null);
	}

	/**
	 * Create a 3D ellipsoid of given size and detail.
	 * 
	 * @param radX the x axis radius
	 * @param radY the y axis radius
	 * @param radZ the z axis radius
	 * @param nbrSegs number of segments in EW direction
	 * @param nbrSlices number of slices in NS direction
	 */	
	public Ellipsoid(float radX, float radY, float radZ, int nbrSegs, int nbrSlices) {
		this(radX, radY, radZ, nbrSegs, nbrSlices, null);
	}

	/**
	 * Create a 3D ellipsoid of given size, detail and orientation.
	 * 
	 * @param radX the x axis radius
	 * @param radY the y axis radius
	 * @param radZ the z axis radius
	 * @param nbrSegs number of segments in EW direction
	 * @param nbrSlices number of slices in NS direction
	 * @param orientation the orientation to use
	 */
	public Ellipsoid(float radX, float radY, float radZ, int nbrSegs, int nbrSlices, Orientation orientation) {
		super();
		this.radX = radX;
		this.radY = radY;
		this.radZ = radZ;
		this.orientation = orientation;
		this.nbrSlices = nbrSlices;
		this.nbrSegs = nbrSegs;
		calcShape();
		makeParts();
		releaseMemory();
	}

	public Ellipsoid getThis() {
		return this;
	}

	protected void calcShape() {
		Vector3D[][] c = new Vector3D[nbrSegs + 1][nbrSlices + 1];
		Vector3D[][] n = new Vector3D[nbrSegs + 1][nbrSlices + 1];
		uv01 = new UV[nbrSegs + 1][nbrSlices + 1];
		double dAngleEW = -2 * Math.PI / nbrSegs;
		double dAngleNS = Math.PI / nbrSlices;
		for(int row = 0 ; row <= nbrSlices; row++) {
			double angleNS = row * dAngleNS;
			double sinNS = Math.sin(angleNS);
			double cosNS = Math.cos(angleNS);
			float v = row / (nbrSlices + 1.0f); 
			for(int col = 0 ; col <= nbrSegs; col++) {
				double angleEW = col * dAngleEW;
				double sinEW = Math.sin(angleEW);
				double cosEW = Math.cos(angleEW);
				c[col][row] = new Vector3D( 
						radX * sinNS * cosEW,	// x
						-radY * cosNS,			// y
						radZ * sinNS * sinEW	// z
						);
				float u = col / (nbrSegs + 1.0f); 
				uv01[col][row] = new UV(u, v);
			}
		}
		// Calculate normals
		// North [row = 0] and south[row == nbrSlices] pole are fixed
		for(int col = 0 ; col <= nbrSegs; col++) {
			n[col][0] = Vector3D.minusJ;
			n[col][nbrSlices] = Vector3D.plusJ;
		}
		for(int row = 1 ; row < nbrSlices; row++) {
			for(int col = 0 ; col <= nbrSegs; col++) {
				int col_prev = col == 0 ? nbrSegs-1 : col - 1;
				int col_next = col == nbrSegs ? 1 : col + 1;
				Vector3D v0 = c[col_next][row].subtract(c[col_prev][row]);
				Vector3D v1 = c[col][row+1].subtract(c[col][row-1]);
				n[col][row] = Vector3D.crossProduct(v0, v1);
				n[col][row] = n[col][row].normalize();
			}
		}
		// Orientation
		if(orientation != null) {
			for(int row = 0 ; row <= nbrSlices; row++) {
				for(int col = 0 ; col <= nbrSegs; col++) {
//					n[col][row] = orientation.rotation().applyTo(n[col][row]);
//					c[col][row] = orientation.rotation().applyTo(c[col][row]);
//					c[col][row] = c[col][row].add(orientation.origin()).normalize();
					
					c[col][row] = orientation.applyRTto(c[col][row]);
					n[col][row] = orientation.applyRto(n[col][row]).normalize();
					
				}
			}
		}
		// Convert coordinate and normals to PVectors
		coord = Util.convert(c);
		normals = Util.convert(n);
	}

	protected void makeParts() {
		shapeParts = new _ShapePart[1];
		shapeParts[0] = new _Mesh2D(pickColor + 0, coord, normals, uv01, "Ellipsoid surface");
	}

	@Override
	protected void releaseMemory() {
		coord = null;
		normals = null;
		uv01 = null;
		orientation = null;
	}

}