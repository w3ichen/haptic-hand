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
import shapes3d.contour.Oval;
import shapes3d.path.Linear;
import shapes3d.utils.Orientation;

/**
 * Creates a 3D set of XYZ axis to show the current orientation of the 3D graphics context.
 * Each axis has its own colour X - red, Y - green and Z - blue.
 * 
 * @author Peter Lager
 *
 */
public final class GraphAxes extends ShapeGroup {

	private Shape3D[] axis = new Shape3D[3], arrow = new Shape3D[3], end = new Shape3D[3];

	/**
	 * Create the axis
	 * @param neg_length distance in the negative direction for axis
	 * @param length distance in the positive direction for axis
	 * @param arm_radius the radius of the axis arm.
	 */
	public GraphAxes(float neg_length, float length, float arm_radius) {
		int nbrSlices = 20, nbrSegs = 9;
		float coneR = 3 * arm_radius, coneL = 4 * arm_radius;
		
		// X axis
		axis[0] = new Tube(
				new Linear(new PVector(neg_length,0,0), new PVector(length,0,0), nbrSlices),
				new Oval(arm_radius, arm_radius, 12));
		axis[0].fill(0xFFFF0000).drawMode(S3D.SOLID).tag = "X Axis";
		arrow[0] = new DoubleCone(coneR, coneR, 0, coneL, nbrSegs, new Orientation(new PVector(length, 0, 0), new PVector(1,0,0))); 
		arrow[0].fill(0xFFFF0000).stroke(0xFFFF8888).strokeWeight(2).drawMode(S3D.WIRE | S3D.SOLID).tag = "X Axis Arrow";
		end[0] = new Ellipsoid(arm_radius, arm_radius, arm_radius, nbrSegs, nbrSlices, new Orientation(new PVector(neg_length,0,0),new PVector(1,0,0)));
		end[0].fill(0xFFFF0000).drawMode(S3D.SOLID).tag = "X Axis End";
		addChild(axis[0], arrow[0], end[0]);
		
		// Y axis
		axis[1] = new Tube(
				new Linear(new PVector(0,neg_length,0), new PVector(0,length,0), nbrSlices),
				new Oval(arm_radius, arm_radius, nbrSegs));
		axis[1].fill(0xFF00CC00).drawMode(S3D.SOLID).tag = "Y Axis";
		arrow[1] = new DoubleCone(coneR, coneR, 0, coneL, nbrSegs, new Orientation(new PVector(0, length, 0), new PVector(0,1,0))); 
		arrow[1].fill(0xFF00CC00).stroke(0xFFCCFFCC).strokeWeight(2).drawMode(S3D.WIRE | S3D.SOLID).tag = "Y Axis Arrow";
		end[1] = new Ellipsoid(arm_radius, arm_radius, arm_radius, nbrSegs, nbrSlices, new Orientation(new PVector(0, neg_length,0),new PVector(0, 1, 0)));
		end[1].fill(0xFF00FF00).drawMode(S3D.SOLID).tag = "Y Axis End";
		addChild(axis[1], arrow[1], end[1]);
		
		// Z axis
		axis[2] = new Tube(
				new Linear(new PVector(0,0,neg_length), new PVector(0, 0, length), nbrSlices),
				new Oval(arm_radius, arm_radius, nbrSegs));
		axis[2].fill(0xFF0000FF).drawMode(S3D.SOLID).tag = "Z Axis";
		arrow[2] = new DoubleCone(coneR, coneR, 0, coneL, nbrSegs, new Orientation(new PVector(0, 0, length), new PVector(0,0,1))); 
		arrow[2].fill(0xFF0000FF).stroke(0xFF8888FF).strokeWeight(2).drawMode(S3D.WIRE | S3D.SOLID).tag = "Z Axis Arrow";
		end[2] = new Ellipsoid(arm_radius, arm_radius, arm_radius, nbrSegs, nbrSlices, new Orientation(new PVector(0, 0, neg_length), new PVector(0,0,1))).fill(0xFF0000FF).drawMode(S3D.SOLID);
		end[2].tag = "Z Axis End";
		addChild(axis[2], arrow[2], end[2]);
	}
	
}
