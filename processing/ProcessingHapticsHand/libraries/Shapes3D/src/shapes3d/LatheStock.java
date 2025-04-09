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
import shapes3d.contour.LatheSurface;
import shapes3d.org.apache.commons.math.geometry.Vector3D;
import shapes3d.path.Path;
import shapes3d.utils.Orientation;
import shapes3d.utils.UV;
import shapes3d.utils.Util;

/**
 * A shape that might have been created on a lathe. The shape is created by rotating a 2D path round the Y axis.
 * 
 * @author Peter Lager
 *
 */
public class LatheStock extends Shape3D {

	protected PVector[] cap_center;
	protected PVector[][] coord;
	protected PVector[][] normals;
	protected UV[][] uv01;

	protected LatheSurface surface;
	protected Orientation orientation = null;
	protected int nbrSlices;
	protected int nbrSegs; // nbr coordinates


	/**
	 * Create a LatheStock shape.
	 * 
	 * @param surface the contour, radial extent and level of detail to be used
	 */
	public LatheStock(LatheSurface surface) {
		this(surface, null);
	}

	/**
	 * Create a LatheStock shape.
	 * 
	 * @param surface the contour, radial extent and level of detail to be used
	 * @param orientation the orientation to be used.
	 */
	public LatheStock(LatheSurface surface, Orientation orientation) {
		super();
		this.surface = surface;
		this.orientation = orientation;
		this.nbrSlices = surface.path().nbrSlices();
		this.nbrSegs = this.surface.nbrSegs();
		calcShape();
		makeParts();	
		releaseMemory();
	}

	public LatheStock getThis() {
		return this;
	}

	@Override
	protected void calcShape() {
		Path path = surface.path();
		// get vertices from contour for slice 0 
		Vector3D[][] c = new Vector3D[nbrSlices + 1][nbrSegs + 1];
		Vector3D[][] n = new Vector3D[nbrSlices + 1][nbrSegs + 1];
		uv01 = new UV[nbrSlices + 1][nbrSegs + 1];
		float deltaU = 1.0f / nbrSlices;
		float deltaV = 1.0f / nbrSegs;
		float deltaT = 1.0f / nbrSlices;
		float deltaA = surface.deltaAngle();
		float startA = surface.startAngle();
		for(int col = 0; col <= nbrSlices; col++) {
			float t = col * deltaT;
			// Get current position and normal on surface path
			Vector3D pos = Util.convert(path.point(t));
			Vector3D norm = Util.convert(path.orthogonal(t));
			// Now for each position calculate the points
			for(int row = 0; row <= nbrSegs; row++) {
				// Calculate {XY] contour coordinate 
				double angle = startA + row * deltaA;
				c[col][row] = new Vector3D(pos.getX() * Math.cos(angle), pos.getY(), pos.getX() * Math.sin(angle));
				n[col][row] = new Vector3D(-norm.getX() * Math.cos(angle), -norm.getY(), -norm.getX() * Math.sin(angle));
				n[col][row] = n[col][row].normalize();
				// Calculate texture coordinates
				uv01[col][row] = new UV( 1- col * deltaU, row * deltaV);
			}
		}
		Vector3D[] eca = new Vector3D[] { 
				new Vector3D(0, path.point(0).y, 0), 
				new Vector3D(0, path.point(1).y, 0) 
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
		shapeParts = new _ShapePart[3];
		shapeParts[0] = new _Mesh2D(pickColor + 0, coord, normals, uv01, ""); 
		// #######################  Lathe Start Cap ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		PVector[] startCoords = new PVector[nbrSegs+2]; // get verts in CCW order
		// First point is the center of the triangle_fan
		startCoords[0] = cap_center[0];
		for(int seg = 0; seg <= nbrSegs; seg++) {
			startCoords[seg + 1] = coord[0][seg].copy();
		}
		// Now calculate the normal for this oval end
		PVector normal = PVector.cross(PVector.sub(startCoords[0], startCoords[1]), PVector.sub(startCoords[2], startCoords[0]), null);
		normal.normalize();
		shapeParts[1] = new _LatheCap(pickColor + 1, startCoords, normal, surface.startAngle(), surface.endAngle(), "Bottom cap");
		// #########################  Lathe End Cap ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
		PVector[] endCoords = new PVector[nbrSegs+2]; // get verts in CCW order
		// First point is the center of the triangle_fan
		endCoords[0] = cap_center[1];
		for(int seg = 0; seg <= nbrSegs; seg++) {
			endCoords[seg + 1] = coord[nbrSlices][nbrSegs - seg].copy();
		}
		// Now calculate the normal for this oval end
		normal = PVector.cross(PVector.sub(endCoords[0], endCoords[1]), PVector.sub(endCoords[2], endCoords[0]), null);
		normal.normalize();
		shapeParts[2] = new _LatheCap(pickColor + 1, endCoords, normal, surface.startAngle(), surface.endAngle(), "Top cap");
	}

	@Override
	protected void releaseMemory() {
		cap_center = null;
		coord = null;
		uv01 = null;
		surface = null;
		orientation = null;
	}

}
