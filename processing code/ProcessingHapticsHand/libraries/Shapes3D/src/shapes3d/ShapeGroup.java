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

import java.util.LinkedList;

import processing.core.PGraphics;
import processing.core.PVector;

/**
 * Simple class to allow a collection of shapes to be moved and rotated as a group.
 * 
 * @author Peter Lager
 *
 */
public class ShapeGroup {

	// Current position and rotation for this shape.
	protected PVector pos = new PVector(0,0,0);	
	protected PVector rot = new PVector(0,0,0);

	// A list of child shapes
	protected LinkedList<Shape3D> children = new LinkedList<Shape3D>();
	protected PGraphics on_canvas;

	/**
	 * Add one or more shapes to the group
	 * @param sub_shapes the shapes to add, null values are not added
	 * @return this shape group
	 */
	public ShapeGroup addChild(Shape3D... sub_shapes) {
		if(sub_shapes != null && sub_shapes.length > 0) {
			for(Shape3D s : sub_shapes) {
				if(s != null){
					children.add(s);
				}
			}
		}
		return this;
	}

	/**
	 * Gets the shapes  making up the group
	 * @return an array of the shapes making up the group
	 */
	public Shape3D[] children() {
		return children.toArray(new Shape3D[children.size()]);
	}
	
	/**
	 * Get the shape at the given position. If the position is invalid, null is returned.
	 * @param n the position of the shape to return
	 * @return the shape or null if the position does not exist
	 */
	public Shape3D child(int n) {
		return (n < 0 || n >= children.size()) ? null : children.get(n);
	}
	
	/**
	 * Makes this shape group visible or invisible.
	 * 
	 * @param visible true if you want to see this shape
	 * @return this shape
	 */
	public ShapeGroup visible(boolean visible){
		for(Shape3D shape3d : children) {
			shape3d.visible(visible);
		}
		return this;
	}

	/**
	 * Sets the shape's current position.
	 * @param pos the new position
	 * @return this shape
	 */
	public ShapeGroup moveTo(PVector pos) {
		this.pos.x = pos.x;
		this.pos.y = pos.y;
		this.pos.z = pos.z;
		return this;
	}

	/**
	 * Sets the shape's current position.
	 * @param x x coordinate
	 * @param y y coordinate
	 * @param z z coordinate
	 * @return this shape
	 */
	public ShapeGroup moveTo(float x, float y, float z){
		pos.x = x;
		pos.y = y;
		pos.z = z;
		return this;
	}

	/**
	 * Sets the shape's current position. <br>
	 * Position is unchanged if the parameter array has less than 
	 * 3 elements.
	 * @param xyz the coordinates in an array
	 * @return this shape
	 */
	public ShapeGroup moveTo(float[] xyz){
		if(xyz.length >= 3){
			pos.x = xyz[0];
			pos.y = xyz[1];
			pos.z = xyz[2];
		}
		return this;
	}


	/**
	 * Get the current rotations as a PVector
	 */
	public PVector getRotVec() {
		return new PVector(rot.x, rot.y, rot.z);
	}

	/**
	 * @param target the PVector to fill, if null create a new PVector
	 * @return the current rotations as a PVector
	 */
	public PVector getRotVec(PVector target){
		if(target == null)
			target = new PVector();
		target.set(rot);
		return target;
	}

	/**
	 * @return the current rotations as an array.
	 */
	public float[] getRotArray(){
		return getRotArray(null);
	}

	/**
	 * If target is not null it is used to store the current position.
	 * @param target
	 * @return the current rotations as an array. <br>
	 */
	public float[] getRotArray(float[] target){
		if(target == null || target.length < 3)
			target = new float[3];
		target[0] = rot.x;
		target[1] = rot.y;
		target[2] = rot.z;
		return target;
	}

	/**
	 * Set the current rotations.
	 * @param angles a PVector containing the x/y/z rotations in radians.
	 * @return this shape
	 */
	public ShapeGroup rotateTo(PVector angles) {
		rot.set(angles);
		return this;
	}

	/**
	 * Set the current rotations.
	 * Ignored if the array has less than 3 elements.
	 * @param angles an array containing the x/y/z rotations in radians.
	 * @return this shape
	 */
	public ShapeGroup rotateTo(float[] angles){
		if(angles.length >= 3){
			rot.x = angles[0];
			rot.y = angles[1];
			rot.z = angles[2];
		}
		return this;
	}

	/**
	 * Set the current rotations.
	 * @param x rotation about x axis
	 * @param y rotation about y axis
	 * @param z rotation about z axis
	 * @return this shape
	 */
	public ShapeGroup rotateTo(float x, float y, float z) {
		rot.x = x;
		rot.y = y;
		rot.z = z;
		return this;
	}

	/**
	 * Set the rotation about the x axis
	 * @param x the angle in radians
	 * @return this shape
	 */
	public ShapeGroup rotateToX(float x){
		rot.x = x;
		return this;
	}

	/**
	 * Set the rotation about the y axis
	 * @param y the angle in radians
	 * @return this shape
	 */
	public ShapeGroup rotateToY(float y){
		rot.y = y;
		return this;
	}

	/**
	 * Set the rotation about the z axis
	 * @param z the angle in radians
	 * @return this shape
	 */
	public ShapeGroup rotateToZ(float z){
		rot.z = z;
		return this;
	}

	/**
	 * Rotate shape from its current rotation state by the specified angles (radians)<br>
	 * @param x add this angle to the current x rotation angle
	 * @param y add this angle to the current y rotation angle
	 * @param z add this angle to the current z rotation angle
	 * @return this shape
	 */
	public ShapeGroup rotateBy(float x, float y, float z){
		rot.x += x;
		rot.y += y;
		rot.z += z;
		return this;
	}

	/**
	 * Rotate shape from its current rotation state by the specified angles (radians)
	 * in the array.<br>
	 * Ignored if the array has less than 3 elements. 
	 * @param angle an array of relative angles
	 * @return this shape
	 */
	public ShapeGroup rotateBy(float[] angle){
		if(angle.length >= 3){
			rot.x += angle[0];
			rot.y += angle[1];
			rot.z += angle[2];
		}
		return this;
	}

	/**
	 * Rotate shape from its current rotation state by the specified angles (radians)
	 * in the PVector.<br>
	 * @param angles a PVector containing the XYZ relative angles
	 * @return this shape
	 */
	public ShapeGroup rotateBy(PVector angles){
		rot.add(angles);
		return this;
	}

	/**
	 * Change the rotation about the x axis by the specified amount.
	 * @param x the angle in radians
	 * @return this shape
	 */
	public ShapeGroup rotateByX(float x){
		rot.x += x;
		return this;
	}

	/**
	 * Change the rotation about the y axis by the specified amount.
	 * @param y the angle in radians
	 * @return this shape
	 */
	public ShapeGroup rotateByY(float y){
		rot.y += y;
		return this;
	}

	/**
	 * Change the rotation about the z axis by the specified amount.
	 * @param z the angle in radians
	 * @return this shape
	 */
	public ShapeGroup rotateByZ(float z){
		rot.z += z;
		return this;
	}

	public void draw(PGraphics pg) {
		on_canvas = pg;
		pg.pushMatrix();
		pg.pushStyle();

		pg.translate(pos.x, pos.y, pos.z);
		pg.rotateX(rot.x);
		pg.rotateY(rot.y);
		pg.rotateZ(rot.z);

		for(Shape3D shape3d : children) {
			shape3d.draw(pg);
		}

		pg.popStyle();
		pg.popMatrix();
	}

}
