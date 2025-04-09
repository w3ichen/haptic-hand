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
import shapes3d.contour.Oval;
import shapes3d.contour.Scale;
import shapes3d.org.apache.commons.math.geometry.Rotation;
import shapes3d.org.apache.commons.math.geometry.Vector3D;
import shapes3d.path.Path;
import shapes3d.utils.Orientation;
import shapes3d.utils.UV;
import shapes3d.utils.Util;

/**
 * The shape formed when an oval (circle or ellipse) travels along a path in 3D space
 * 
 * @author Peter Lager
 *
 */
public final class Tube extends Shape3D {

	protected PVector[] cap_center;
	protected PVector[][] coord;
	protected PVector[][] normals;
	protected UV[][] uv01;

	protected Path path = null;
	protected Oval xsection = null;
	protected Scale xsection_scale = null;
	protected Orientation orientation = null;
	protected int nbrSlices;
	protected int nbrSegs;

	/**
	 * Create a Tube
	 * 
	 * @param path the 3D path followed by the oval
	 * @param xsection the oval representing the cross-section of the tube
	 */
	public Tube(Path path, Oval xsection) {
		this(path, xsection, new FixedScale(), null);
	}

	/**
	 * Create a Tube
	 * 
	 * @param path the 3D path followed by the oval
	 * @param xsection the oval representing the cross-section of the tube
	 * @param scale controls the size of the cross-section along the length of the tube
	 */
	public Tube(Path path, Oval xsection, Scale scale) {
		this(path, xsection, scale, null);
	}

	/**
	 * Create a Tube
	 * 
	 * @param path the 3D path followed by the oval
	 * @param xsection the oval representing the cross-section of the tube
	 * @param orientation the orientation to use for this shape
	 */
	public Tube(Path path, Oval xsection, Orientation orientation) {
		this(path, xsection, new FixedScale(), orientation);
	}

	/**
	 * Create a Tube
	 * 
	 * @param path the 3D path followed by the oval
	 * @param xsection the oval representing the cross-section of the tube
	 * @param scale controls the size of the cross-section along the length of the tube
	 * @param orientation the orientation to use for this shape
	 */
	public Tube(Path path, Oval xsection, Scale scale, Orientation orientation) {
		super();
		this.path = path;
		this.xsection = xsection;
		this.xsection_scale = scale;
		this.orientation = orientation;
		this.nbrSlices = this.path.nbrSlices();
		this.nbrSegs = this.xsection.nbrSegs();
		calcShape();
		makeParts();
	}

	public Tube getThis() {
		return this;
	}

	@Override
	protected void calcShape() {
		// get vertices from contour for slice 0 
		PVector[] xs = xsection.coords();
		Vector3D[][] c = new Vector3D[nbrSlices + 1][nbrSegs + 1];
		Vector3D[][] n = new Vector3D[nbrSlices + 1][nbrSegs + 1];
		uv01 = new UV[nbrSlices + 1][nbrSegs + 1];
		float deltaU = 1.0f / nbrSlices;
		float deltaV = 1.0f / nbrSegs;
		float deltaT = 1.0f / nbrSlices;
		for(int col = 0; col <= nbrSlices; col++) { // Moving along path
			float t = col * deltaT;
			float scaleX =  xsection_scale.scaleX(t);
			float scaleY =  xsection_scale.scaleY(t);
			// Get current position on path
			Vector3D pos = Util.convert(path.point(t));
			// Calculate rotation
			Vector3D tan = Util.convert(path.tangent(t));
			Vector3D ortho = Util.convert(path.orthogonal(t));
			// Calculate rotation for this column
			Rotation rot = new Rotation(Vector3D.plusK, Vector3D.plusJ, tan, ortho);
			for(int row = 0; row <= nbrSegs; row++) { // moving round tube surface
				// Calculate {XY] contour coordinate and apply any scale
				c[col][row] = new Vector3D(xs[row].x * scaleX, xs[row].y * scaleY, 0);
				// Apply rotation to {XY} contour coordinate due to path tangent
				c[col][row] = rot.applyTo(c[col][row]);
				// Add position on path
				c[col][row] = c[col][row].add(pos);
				n[col][row] = new Vector3D(xs[row].x * scaleX, xs[row].y * scaleY, 0);
				n[col][row] = rot.applyTo(n[col][row]);
				n[col][row] = n[col][row]; // .normalize();
				// Calculate texture coordinates
				uv01[col][row] = new UV(col * deltaU, row * deltaV);
			}
		}	
		Vector3D[] eca = new Vector3D[] { 
				Util.convert(path.point(0)), 
				Util.convert(path.point(1)), 
		}; 
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
			for(int i = 0; i < eca.length; i++) {
				eca[i] = orientation.rotation().applyTo(eca[i]);
				eca[i] = eca[i].add(orientation.origin());
			}
		}
		coord = Util.convert(c);
		normals = Util.convert(n);
		cap_center = Util.convert(eca);
	}

	@Override
	protected void makeParts() {
		// If the path is open then create the end caps
		if(path.isOpenPath()) {
			shapeParts = new _ShapePart[3];
			// #########################  Start cap
			// Start of tube get verts in CCW order
			PVector[] startCoords = new PVector[nbrSegs + 2];
			// First point is the center of the oval and the triangle_fan
			startCoords[0] = cap_center[0];
			for(int seg = 0; seg <= nbrSegs; seg++) {
				startCoords[seg + 1] = coord[0][seg]; // set the coordinates of the oval circumference
			}
			// Now calculate the normal for this oval end
			PVector normal = PVector.cross(PVector.sub(startCoords[1], startCoords[0]), PVector.sub(startCoords[2], startCoords[0]), null);
			normal.setMag(10);
			shapeParts[1] = new _Oval(pickColor + 1, startCoords, normal, xsection.uv(), "Start cap");
			// #########################  End cap
			// End of tube get verts in CCW order
			PVector[] endCoords = new PVector[nbrSegs + 2];
			// First point is the center of the triangle_fan
			endCoords[0] = cap_center[1];
			for(int seg = 0; seg <= nbrSegs; seg++) {
				endCoords[seg + 1] = coord[nbrSlices][seg];
			}
			// Now calculate the normal for this oval end
			normal = PVector.cross(PVector.sub(endCoords[0], endCoords[1]), PVector.sub(endCoords[2], endCoords[0]), null);
			normal.setMag(10);
			Oval mirror = xsection.mirror();
			shapeParts[2] = new _Oval(pickColor + 2, endCoords, normal, mirror.uv(), "End cap");
		}
		else {
			shapeParts = new _ShapePart[1];
		}
		shapeParts[0] = new _Mesh2D(pickColor + 0, coord, normals, uv01, ""); 
	}

	@Override
	protected void releaseMemory() {
		coord = null;
		uv01 = null;
		path = null;
		xsection = null;
		xsection_scale = null;
		orientation = null;
	}
}
