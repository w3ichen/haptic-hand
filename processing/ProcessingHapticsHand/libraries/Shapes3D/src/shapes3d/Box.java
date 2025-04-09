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
 * A regular axis aligned 3D box shape with 6 sides that can have 
 * different visual attributes.
 * 
 * @author Peter Lager
 *
 */
public class Box extends Shape3D {

	protected float w;
	protected float h;
	protected float d;

	protected PVector[] coord;
	protected PVector[] normals;
	protected Orientation orientation;

	/**
	 * Create a box of given size.
	 * 
	 * @param w width (x axis)
	 * @param h height (y axis)
	 * @param d depth (z axis)
	 */
	public Box(float w, float h, float d) {
		this(w, h, d, null);
	}

	/**
	 * Create a box of given size and orientation.
	 * 
	 * @param w width (x axis)
	 * @param h height (y axis)
	 * @param d depth (z axis)
	 * @param orientation the orientation to use
	 */
	public Box(float w, float h, float d, Orientation orientation) {
		super();
		coord = new PVector[8];
		this.w = w;
		this.h = h;
		this.d = d;
		this.orientation = orientation;
		calcShape();
		makeParts();
		releaseMemory();
	}

	public Box getThis() {
		return this;
	}

	protected void calcShape() {
		float w2 = w / 2;
		float h2 = h / 2;
		float d2 = d / 2;
		// Calculate vertex coordinates
		Vector3D[] c = new Vector3D[8];
		c[0] = new Vector3D(-w2, -h2, -d2);
		c[1] = new Vector3D(-w2, -h2, +d2);
		c[2] = new Vector3D(-w2, +h2, -d2);
		c[3] = new Vector3D(-w2, +h2, +d2);
		c[4] = new Vector3D(+w2, -h2, -d2);
		c[5] = new Vector3D(+w2, -h2, +d2);
		c[6] = new Vector3D(+w2, +h2, -d2);
		c[7] = new Vector3D(+w2, +h2, +d2);
		
		Vector3D[] n = new Vector3D[6];
		n[0] = Vector3D.plusJ;	// BOTTOM
		n[1] = Vector3D.minusJ;	// TOP
		n[2] = Vector3D.plusK;	// FRONT
		n[3] = Vector3D.minusK;	// BACK
		n[4] = Vector3D.minusI;	// LEFT
		n[5] = Vector3D.plusI;	// RIGHT
		// Adjust orientation if needed
		if(orientation != null) {
			// Adjust corner coordinates
			for(int i = 0; i < c.length; i++) {
//				c[i] = orientation.rotation().applyTo(c[i]);
//				c[i] = c[i].add(orientation.origin());
				c[i] = orientation.applyRTto(c[i]);
			}
			for(int i = 0; i < n.length; i++) {
//				n[i] = orientation.rotation().applyTo(n[i]);
				n[i] = orientation.applyRto(n[i]);
			}	
		}
		coord = Util.convert(c);
		normals = Util.convert(n);
	}

	protected void makeParts() {
		// Create the 6 sides of the box
		shapeParts = new _ShapePart[6];
		PVector[][] quad_coords;
		UV[][] uv = new UV[][] { {new UV(0, 0), new UV(0, 1)}, {new UV(1, 0), new UV(1, 1)}};
		// 0 Bottom face
		quad_coords = new PVector[][] { {coord[3], coord[2]},{coord[7], coord[6]}};
		shapeParts[0] = new _FlatMesh2D(pickColor + 0, quad_coords, normals[0], uv);
		shapeParts[0].fill(PURPLE).tag = "Bottom Face";
		// 1 Top face
		quad_coords = new PVector[][] { {coord[0], coord[1]},{coord[4], coord[5]}};
		shapeParts[1] = new _FlatMesh2D(pickColor + 1, quad_coords, normals[1], uv);
		shapeParts[1].fill(GREEN).tag = "Top Face";
		// 2 Front face
		quad_coords = new PVector[][] { {coord[1], coord[3]},{coord[5], coord[7]}};
		shapeParts[2] = new _FlatMesh2D(pickColor + 2, quad_coords, normals[2], uv);
		shapeParts[2].fill(ORANGE).tag = "Front Face";
		// 3 Back face
		quad_coords = new PVector[][] { {coord[4], coord[6]},{coord[0], coord[2]}};
		shapeParts[3] = new _FlatMesh2D(pickColor + 3, quad_coords, normals[3], uv);
		shapeParts[3].fill(RED).tag = "Back Face";
		// 4 Left face
		quad_coords = new PVector[][] { {coord[0], coord[2]},{coord[1], coord[3]}};
		shapeParts[4] = new _FlatMesh2D(pickColor + 4, quad_coords, normals[4], uv);
		shapeParts[4].fill(YELLOW).tag = "Left Face";
		// 5 Right face
		quad_coords = new PVector[][] { {coord[5], coord[7]},{coord[4], coord[6]}};
		shapeParts[5] = new _FlatMesh2D(pickColor + 5, quad_coords, normals[5], uv);
		shapeParts[5].fill(BLUE).tag = "Right Face";
	}

	@Override
	protected void releaseMemory() {
		coord = null;
		normals = null;
		orientation = null;		
	}

}
