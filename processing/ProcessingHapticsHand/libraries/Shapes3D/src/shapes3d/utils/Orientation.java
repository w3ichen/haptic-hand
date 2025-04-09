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

package shapes3d.utils;

import processing.core.PVector;
import shapes3d.org.apache.commons.math.geometry.Rotation;
import shapes3d.org.apache.commons.math.geometry.Vector3D;

/**
 * Objects of this class can be used to change the origin [0,0,0] and UP 
 * vector for the model-view coordinates.
 * 
 * @author Peter Lager
 *
 */
public final class Orientation implements SConstants {

	// Center of rotation
	protected Vector3D origin = null;
	// Rotation for this orientation
	protected Rotation rotation = null;

	/**
	 * Specify a new origin and a new UP vector for the model view 
	 * coordinate system. <br>
	 * if either is unchanged then pass null as the parameter e.g. <br>
	 * <pre> ... new Orientation(null, new PVector(0,1,1));</pre> <br>
	 * would change the UP vector but leave the origin unchanged and <br>
	 * <pre> ... new Orientation(new PVector(50, -10, 25), null);</pre> <br>
	 * would change the MV origin but leave the UP vector unchanged. <br>
	 * Note: The original origin was [0,0,0] and the original UP vector 
	 * was [0,1,0] <br>
	 *
	 * @param origin new origin for model-view coordinates.
	 * @param up new UP vector.
	 */
	public Orientation(PVector origin, PVector up) {
		this.origin = (origin == null) ? Vector3D.zero : Util.convert(origin);
		rotation = up == null ? ROTATION_ZERO : new Rotation(Vector3D.plusJ, Util.convert(up));  
	}

	/**
	 * Specify a new origin and a new orientation for the model view 
	 * coordinate system. <br>
	 * If you do not wish to alter the model-view origin pass null as the first parameter.<br>
	 * Rotate the model coordinates such that a vector v0 will now be v1. You must not pass
	 * null for either of these vectors. <br>
	 * Note: The origin center of rotation was [0,0,0] 
	 * @param origin new origin for model-view coordinates. 
	 * @param v0 original vector in model coordinates
	 * @param v1 the desired vector after rotation 
	 */
	public Orientation(PVector origin, PVector v0, PVector v1) {
		this.origin = origin == null ? Vector3D.zero : Util.convert(origin);
		rotation = new Rotation(Util.convert(v0), Util.convert(v1));  
	}

	/**
	 * A unit orientation leaving the coordinates unchanged.
	 */
	public Orientation() {
		origin = Vector3D.zero;
		rotation = ROTATION_ZERO;
	}

	/**
	 * Get the center of rotation
	 * @return the new origin for this orientation
	 */
	public Vector3D origin() {
		return origin;
	}

	/**
	 * Get the rotation to be applied to the model coordinates
	 * @return the rotation for this orientation
	 */
	public Rotation rotation() {
		return rotation;
	}
	
	/**
	 * Apply rotation followed by translation to a vector.
	 * 
	 * @param vector the vector to transform
	 * @return the transformed vector
	 */
	public Vector3D applyRTto(final Vector3D vector) {
		return rotation.applyTo(vector).add(origin);
	}

	/**
	 * Apply translation followed by rotation to a vector.
	 * 
	 * @param vector the vector to transform
	 * @return the transformed vector
	 */
	public Vector3D applyTRto(final Vector3D vector) {
		return rotation.applyTo(vector.add(origin));
	}

	/**
	 * Apply a rotation to a vector.
	 * 
	 * @param vector the vector to transform
	 * @return the transformed vector
	 */
	public Vector3D applyRto(final Vector3D vector) {
		return rotation.applyTo(vector);
	}
	
	/**
	 * Apply a translation to a vector.
	 * 
	 * @param vector the vector to transform
	 * @return the transformed vector
	 */
	public Vector3D applyTto(final Vector3D vector) {
		return vector.add(origin);
	}
	
	/**
	 * Apply rotation followed by translation to a vector.
	 * 
	 * @param vector the vector to transform
	 * @return the transformed vector
	 */
	public PVector applyRTto(final PVector vector) {
		return Util.convert(applyRTto(Util.convert(vector)));
	}
	
	/**
	 * Apply translation followed by rotation to a vector.
	 * 
	 * @param vector the vector to transform
	 * @return the transformed vector
	 */
	public PVector applyTRto(final PVector vector) {
		return Util.convert(applyTRto(Util.convert(vector)));
	}

	/**
	 * Apply a rotation to a vector.
	 * 
	 * @param vector the vector to transform
	 * @return the transformed vector
	 */
	public PVector applyRto(final PVector vector) {
		return Util.convert(applyRto(Util.convert(vector)));
	}

	/**
	 * Apply a translation to a vector.
	 * 
	 * @param vector the vector to transform
	 * @return the transformed vector
	 */
	public PVector applyTto(final PVector vector) {
		return Util.convert(applyTto(Util.convert(vector)));
	}
}
