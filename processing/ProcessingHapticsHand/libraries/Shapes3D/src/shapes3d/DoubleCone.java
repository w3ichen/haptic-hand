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
import shapes3d.org.apache.commons.math.geometry.Rotation;
import shapes3d.org.apache.commons.math.geometry.Vector3D;
import shapes3d.utils.Orientation;
import shapes3d.utils.UV;
import shapes3d.utils.Util;

/**
 * Imagine two cones joined at their wide end with their central axis aligned with the y 
 * axis then have the DoubleCone.
 * 
 * @author Peter Lager
 *
 */
public class DoubleCone extends Shape3D {

	protected float radX, radZ, h1, h2;
	protected int nbrSegs;
	protected Orientation orientation;

	protected PVector[] coord1, coord2;
	protected PVector[] normals1, normals2;
	protected UV[] uv01;

	/**
	 * Create a double cone of given size and detail.
	 * 
	 * @param radius1 the first radius of the wide end 
	 * @param radius2 the second (orthogonal to the first) radius of the wide end.
	 * @param height1 the height of the first cone
	 * @param height2 the height of the second cone
	 * @param detail the number of segments round the central axis.
	 */	
	public DoubleCone(float radius1, float radius2, float height1, float height2, int detail) {
		this(radius1, radius2, height1, height2, detail, null);
	}

	/**
	 * Create a double cone of given size, detail and orientation.
	 * 
	 * @param radius1 the first radius of the wide end 
	 * @param radius2 the second (orthogonal to the first) radius of the wide end.
	 * @param height1 the height of the first cone
	 * @param height2 the height of the second cone
	 * @param detail the number of segments round the central axis.
	 * @param orientation the orientation to use
	 */
	public DoubleCone(float radius1, float radius2, float height1, float height2, int detail, Orientation orientation) {
		super();
		radX = radius1;
		radZ = radius2;
		h1 = height1;
		h2 = height2;
		nbrSegs = detail;
		this.orientation = orientation;
		uv01 = new UV[nbrSegs + 2];

		calcShape();
		makeParts();
		releaseMemory();
	}

	public DoubleCone getThis() {
		return this;
	}

	protected void calcShape() {
		// Arrays for top half-cone coordinates and normals
		Vector3D[] c2 = new Vector3D[nbrSegs + 2];
		Vector3D[] n2 = new Vector3D[nbrSegs + 2];
		c2[0] = new Vector3D(0, h2, 0);			// Top peak vertex		
		n2[0] = new Vector3D(0, -1, 0);			// Top peak normal		
		// Arrays for bottom half-cone coordinates and normals
		Vector3D[] c1 = new Vector3D[nbrSegs + 2];
		Vector3D[] n1 = new Vector3D[nbrSegs + 2];
		c1[0] = new Vector3D(0, h1, 0);			// Bottom peak vertex
		n1[0] = new Vector3D(0, 1, 0);			// Bottom peak normal
		uv01[0] = new UV(0.5f, 0.5f);
		double deltaA = 2 * Math.PI / nbrSegs;
		for(int s = 1; s <= nbrSegs +1; s++) {
			double angle = (s - 1) * deltaA;
			double cosA = Math.cos(2 * Math.PI - angle);
			double sinA = Math.sin(2 * Math.PI - angle);
			// Top vertex and bottom vertices
			c2[s] = new Vector3D(radX * cosA, 0, + radZ * sinA);
			c1[s] = new Vector3D(radX * cosA, 0, - radZ * sinA);
			// Normalised UV coordinates
			uv01[s] = new UV((1 + (float)cosA)/2, (1 + (float)sinA)/2);
		}
		// Calculate surface normals, these will be unit length vectors
		Rotation rot;
		for(int s = 1; s <= nbrSegs +1; s++) {
			rot = new Rotation(new Vector3D(c1[s].getX(), h1, c1[s].getZ()), new Vector3D(c1[s].getX(), 0, c1[s].getZ()));
			n1[s] = rot.applyTo(Vector3D.plusJ);
			rot = new Rotation(new Vector3D(c2[s].getX(), h2, c2[s].getZ()), new Vector3D(c2[s].getX(), 0, c2[s].getZ()));
			n2[s] = rot.applyTo(Vector3D.minusJ);
		}
		// Apply orientation to coordinates and normals
		if(orientation != null) {
			for(int s = 0; s < c1.length; s++) {
//				c1[s] = orientation.rotation().applyTo(c1[s]);
//				c1[s] = c1[s].add(orientation.origin());
//				n1[s] = orientation.rotation().applyTo(n1[s]);
				c1[s] = orientation.applyRTto(c1[s]);
				n1[s] = orientation.applyRto(n1[s]).normalize();
				
				//coord1[s] = Util.convert(c1[s]);
//				c2[s] = orientation.rotation().applyTo(c2[s]);
//				c2[s] = c2[s].add(orientation.origin());
//				n2[s] = orientation.rotation().applyTo(n2[s]);
				c2[s] = orientation.applyRTto(c2[s]);
				n2[s] = orientation.applyRto(n2[s]).normalize();
			}
		}
		// Convert coordinates and normal arrays to PVector(s)
		coord1 = Util.convert(c1);
		normals1 = Util.convert(n1);
		coord2 = Util.convert(c2);
		normals2 = Util.convert(n2);
	}

	protected void makeParts() {
		shapeParts = new _ShapePart[2];
		shapeParts[0] = new _HalfCone(pickColor + 0, coord1, normals1, uv01, "Botton half cone");
		shapeParts[0].fill(BLUE).stroke(YELLOW).strokeWeight(2).drawMode(S3D.SOLID | S3D.WIRE);
		shapeParts[1] = new _HalfCone(pickColor + 1, coord2, normals2, Util.deepCopy(uv01), "Top half cone");
		shapeParts[1].fill(GREEN).stroke(YELLOW).strokeWeight(2).drawMode(S3D.SOLID | S3D.WIRE);
	}

	@Override
	protected void releaseMemory() {
		orientation = null;
		coord1 = null;
		coord2 = null;
		normals1 = null;
		normals2 = null;
		uv01 = null;
	}

}
