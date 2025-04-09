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



import java.util.List;

import processing.core.PVector;
import shapes3d.utils.Triangulator;
import shapes3d.utils.UV;

/**
 * Defines an irregular polygon for the cross-section of an extruded shape. <br>
 * 
 * The user supplied coordinates may represent an open or closed polygon in CW or CCW 
 * order but will be stored internally as a closed polygon in CCW order.
 * 
 * @author Peter Lager
 *
 */
public final class Polygon extends Contour {

	protected PVector[] coords;
	protected UV[] uvNorm;
	protected float[] vNorm;
	protected float contour_length = 0;
	protected int[] tr = null;


	/**
	 * Create a irregular polygon from the  supplied vertices.<br>
	 * 
	 * The contour coordinates should be XY plane when Z=0 and viewed from [0,0,1] <br>
	 * 
	 * <pre>
	 *                     *v1
	 * 
	 *           *v2                   *v0
	 *                   _____________________ +X
	 *                  /|
	 *             *v3 / |
	 *                /  |            *v6
	 *               /   |
	 *              /    |      *v5
	 *             / *v4 |
	 *            /      |
	 *          +Z       |
	 *                   +Y 
	 * </pre>
	 * The vertices are shown in CCW order. Note that the contour is open because
	 * the first and last vertex are different positions. <br>
	 * 
	 * @param verts the vertices in order
	 * @param dir direction of supplied vertices, CW or CCW
	 * @param open true if the vertices form an open polygon or false for a closed polygon.
	 */
	public Polygon(PVector[] verts, int dir, boolean open) {
		// Normalise the coordinates so we have a closed polygon 
		// in the CCW direction
		if(open) {
			coords = new PVector[verts.length + 1];
			coords[coords.length - 1] = verts[0].copy();
		} else {
			coords = new PVector[verts.length];
		}
		for(int i = 0; i < verts.length ; i++) {
			coords[i] = verts[i].copy();
		}
		if(dir == CW) { // Reverse order to make it CCW
			for(int i = 0; i < coords.length/2; i++) {
				PVector temp = coords[coords.length - 1 - i];
				coords[coords.length - 1 - i] = coords[i];
				coords[i] = temp;
			}
		}
		nbrSegs = coords.length - 1; // closed loop so -1
		// Calculate the triangles needed to cover the end
		tr = Triangulator.asPrimatives(Triangulator.triangulate(coords, false));
		// Calculate uv coordinates
		calcUV();
		calcV();
	}

	public Polygon(List<PVector> verts, int dir, boolean open) {
		this((PVector[]) verts.toArray(new PVector[verts.size()]), dir, open);
	}

	/**
	 * @return the Polygon that is a mirror of this one.
	 */
	public Polygon mirror() {
		PVector[] c = new PVector[coords.length];
		for(int i = 0; i < c.length; i++) {
			c[i] = new PVector(-coords[i].x, coords[i].y);
		}
		return new Polygon(c, CCW, false);
	}

	/**
	 * Calculate the v texture coordinate for each vertex. Used to texture 
	 * the body of the shape.
	 */
	private void calcV() {
		vNorm = new float[coords.length];
		contour_length = 0;
		// Calculate the cumulative distance around contour
		vNorm[0] = 0;
		for(int i = 1 ; i < coords.length; i++) {
			vNorm[i] = vNorm[i-1] + PVector.dist(coords[i-1],  coords[i]);
		}
		// Normalise the distances 0-1 incl
		contour_length = vNorm[vNorm.length - 1];
		for(int i = 1 ; i < coords.length; i++) {
			vNorm[i] /= contour_length;
		}
	}

	/**
	 * Used to calculate the uv coordinates for the end cap coordinates
	 */
	private void calcUV() {
		float minX, maxX, minY, maxY;
		minX = maxX = coords[0].x;
		minY = maxY = coords[0].y;
		for(int i = 1; i < coords.length; i++) {
			PVector c = coords[i];
			if(minX > c.x ) {
				minX = c.x;
			}
			else if(maxX < c.x) {
				maxX = c.x;
			}
			if(minY > c.y ) {
				minY = c.y;
			}
			else if(maxY < c.y) {
				maxY = c.y;
			}
		}
		float rangeX = maxX - minX;
		float rangeY = maxY - minY;	
		uvNorm = new UV[coords.length];
		for(int i = 0; i < coords.length; i++) {
			uvNorm[i] = new UV( 1 - (coords[i].x - minX) / rangeX, (coords[i].y - minY) / rangeY);
		}		
	}

	/**
	 * @return the [x, y, 0] coordinates for the vertices defining this polygon
	 */
	public PVector[] coords() {
		return coords;
	}

	/**
	 * @return the normalized texture coordinates for this polygon
	 */
	public UV[] uv() {
		return uvNorm;
	}

	/**
	 * @return the v texture coordinates to be used when texturing the body of the shape
	 */
	public float[] v() {
		return vNorm;
	}

	/**
	 * @return the indices for the vertices for each triangle (grouped in threes)
	 * to render the end cap
	 */
	public int[] triangles() {
		return tr;
	}
}
