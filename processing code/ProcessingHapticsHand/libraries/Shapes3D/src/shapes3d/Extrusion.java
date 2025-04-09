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
import shapes3d.contour.FixedScale;
import shapes3d.contour.Polygon;
import shapes3d.contour.Scale;
import shapes3d.org.apache.commons.math.geometry.Rotation;
import shapes3d.org.apache.commons.math.geometry.Vector3D;
import shapes3d.path.Path;
import shapes3d.utils.Orientation;
import shapes3d.utils.UV;
import shapes3d.utils.Util;

/**
 * The shape formed when a polygon travels along a path in 3D space
 * 
 * @author Peter Lager
 *
 */
public class Extrusion extends Shape3D {

	protected PVector[][] coord;
	protected PVector[][] normals;
	protected UV[][] uv01;

	protected Path path = null;
	protected Polygon xsection = null;
	protected Scale c_scale = null;
	protected Orientation orientation = null;
	protected int nbrSlices;
	protected int nbrSegs;

	/**
	 * Create an Extrusion
	 * 
	 * @param path the 3D path followed by the polygon
	 * @param xsection the polygon representing the cross-section of the extrusion
	 */
	public Extrusion(Path path, Polygon xsection) {
		this(path, xsection, new FixedScale(), null);
	}

	/**
	 * Create an Extrusion
	 * 
	 * @param path the 3D path followed by the polygon
	 * @param xsection the polygon representing the cross-section of the extrusion
	 * @param scale controls the size of the cross-section along the length of the extrusion
	 */
	public Extrusion(Path path, Polygon xsection, Scale scale) {
		this(path, xsection, scale, null);
	}

	/**
	 * Create an Extrusion
	 * 
	 * @param path the 3D path followed by the polygon
	 * @param xsection the polygon representing the cross-section of the extrusion
	 * @param orientation the orientation to use for this shape
	 */
	public Extrusion(Path path, Polygon xsection, Orientation orientation) {
		this(path, xsection, new FixedScale(), orientation);
	}

	/**
	 * Create an Extrusion
	 * 
	 * @param path the 3D path followed by the polygon
	 * @param xsection the polygon representing the cross-section of the extrusion
	 * @param scale controls the size of the cross-section along the length of the extrusion
	 * @param orientation the orientation to use for this shape
	 */
	public Extrusion(Path path, Polygon xsection, Scale scale, Orientation orientation) {
		super();
		this.path = path;
		this.xsection = xsection;
		this.c_scale = scale;
		this.orientation = orientation;
		this.nbrSlices = this.path.nbrSlices();
		this.nbrSegs = xsection.nbrSegs();
		calcShape();
		makeParts();
		releaseMemory();
	}

	public Extrusion getThis() {
		return this;
	}

	@Override
	protected void calcShape() {
		// get vertices from contour for slice 0 
		PVector[] c_v = xsection.coords();
		float[] v = xsection.v();

		Vector3D[][] c = new Vector3D[nbrSlices + 1][nbrSegs + 1];
		Vector3D[][] n = new Vector3D[nbrSlices + 1][nbrSegs + 1];
		uv01 = new UV[nbrSlices + 1][nbrSegs + 1];
		float deltaU = 1.0f / nbrSlices;
		float deltaT = 1.0f / nbrSlices;

		for(int col = 0; col <= nbrSlices; col++) {
			float t = col * deltaT;
			// Get current position on path
			Vector3D pos = Util.convert(path.point(t));
			// Calculate rotation
			Vector3D tan = Util.convert(path.tangent(t));
			Vector3D ortho = Util.convert(path.orthogonal(t));
			// Calculate rotation for this column
			Rotation rot = new Rotation(Vector3D.plusK, Vector3D.plusJ, tan, ortho);
			for(int row = 0; row <= nbrSegs; row++) {
				// Calculate {XY] contour coordinate and apply any scale
				c[col][row] = new Vector3D(c_v[row].x * c_scale.scaleX(t), c_v[row].y * c_scale.scaleY(t), 0);
				// Apply rotation to {XY} contour coordinate due to path tangent
				c[col][row] = rot.applyTo(c[col][row]);
				// Add position on path
				c[col][row] = c[col][row].add(pos);
				// Calculate texture coordinates
				uv01[col][row] = new UV(col * deltaU, v[row]);
			}
		}
		// Calculate normals
		// North [row = 0] and south[row == nbrSlices] pole are fixed
		for(int row = 0 ; row <= nbrSegs; row++) {
			int row_next = row < nbrSegs ? row + 1 : 1;		
			for(int col = 0 ; col <= nbrSlices; col++) {
				int col_next = col < nbrSlices ? col + 1 : col - 1;
				Vector3D v0 = c[col][row].subtract(c[col_next][row]);
				Vector3D v1 = c[col][row_next].subtract(c[col][row]);
				n[col][row] = Vector3D.crossProduct(v0, v1); //.normalize();
				if(col == nbrSlices){
					n[col][row] = n[col][row].negate();
				}
				n[col][row] = n[col][row].normalize();
			}
		}
		// Apply any change in orientation
		if(orientation != null) {
			for(int col = 0; col <= nbrSlices; col++) {
				for(int row = 0; row <= nbrSegs; row++) {
//					c[col][row] = orientation.rotation().applyTo(c[col][row]);
//					c[col][row] = c[col][row].add(orientation.origin());
//					n[col][row] = orientation.rotation().applyTo(n[col][row]).normalize();
					c[col][row] = orientation.applyRTto(c[col][row]);
					n[col][row] = orientation.applyRto(n[col][row]).normalize();
				}
			}
		}
		coord = Util.convert(c);
		normals = Util.convert(n);
	}

	@Override
	protected void makeParts() {
		// If the path is open then create the end caps
		if(path.isOpenPath()) {
			shapeParts = new _ShapePart[3];
			// ############## Start Cap
			// Start of extrusion get verts in CCW order
			PVector[] startCoords = new PVector[nbrSegs + 1];
			for(int seg = 0; seg <= nbrSegs; seg++) {
				startCoords[seg] = coord[0][seg].copy();
			}
			// Now calculate the normal for this xsection polygon end
			PVector normal = PVector.cross(PVector.sub(startCoords[0], startCoords[1]), PVector.sub(startCoords[2], startCoords[0]), null);
			normal.normalize();
			shapeParts[1] = new _Polygon(pickColor + 1, startCoords, normal, xsection.triangles(), xsection.uv(), "Start cap");
			// ############## End Cap
			// End of extrusion get verts in CCW order
			PVector[] endCoords = new PVector[nbrSegs + 1];
			for(int seg = 0; seg <= nbrSegs; seg++) {
				endCoords[seg] = coord[nbrSlices][seg].copy();
			}
			// Now calculate the normal for this xsection polygon end
			normal = PVector.cross(PVector.sub(endCoords[1], endCoords[0]), PVector.sub(endCoords[2], endCoords[0]), null);
			normal.normalize();
			Polygon mirror = xsection.mirror();
			shapeParts[2] = new _Polygon(pickColor + 2, endCoords, normal, mirror.triangles(), mirror.uv(), "End cap");
		}
		else {
			shapeParts = new _ShapePart[1];
		}
		shapeParts[0] = new _Mesh2D(pickColor + 0, coord, normals, uv01, "Extruson body"); 
	}

	@Override
	protected void releaseMemory() {
		coord = null;
		uv01 = null;
		path = null;
		xsection = null;
		c_scale = null;
		orientation = null;
	}

}
