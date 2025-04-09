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

import processing.core.PApplet;
import processing.core.PVector;
import shapes3d.org.apache.commons.math.geometry.Vector3D;

/**
 * A variety of utility methods used by the library. Including <br> 
 * <ul>
 * <li>Some simple methods to covert vectors between Processing and Apache Commons Maths
 * implementations. </li>
 * <li>array copy methods for PVector and Util classes. </li>
 * </ul>
 * @author Peter Lager
 *
 */
public class Util {

	/**
	 * Create an array of PVectors form 2 array holding x and y values. <br>
	 * If the arrays passed to this method differ in length the extra 
	 * in the longer array are ignored. <br>
	 * 
	 * @param x array of x values
	 * @param y array of y values
	 * @return an array of PVectors
	 */
	public static PVector[] makePVectorArray(float[] x, float[] y) {
		PVector[] v = new PVector[Math.min(x.length,  y.length)];
		for(int i = 0; i < v.length; i++) {
			v[i] = new PVector(x[i], y[i]);
		}
		return v;
	}

	/**
	 * Create an array of PVectors from 3 arrays holding x, y and z values. <br>
	 * If the arrays passed to this method differ in length the extra 
	 * in the longer arrays are ignored. <br>
	 * 
	 * @param x array of x values
	 * @param y array of y values
	 * @param y array of z values
	 * @return an array of PVectors
	 */
	public static PVector[] makePVectorArray(float[] x, float[] y, float[] z) {
		PVector[] v = new PVector[Math.min(Math.min(x.length,  y.length), z.length)];
		for(int i = 0; i < v.length; i++) {
			v[i] = new PVector(x[i], y[i], z[i]);
		}
		return v;
	}

	/**
	 * Convert from Processing to AMC vector implementation
	 * @param pv the PVector to convert
	 * @return the Vector3D result
	 */
	public static Vector3D convert(PVector pv){
		return new Vector3D(pv.x, pv.y, pv.z);
	}

	/**
	 * Convert from AMC to Processing vector implementation
	 * @param v3d the Vector3D to convert
	 * @return the PVector result
	 */
	public static PVector convert(Vector3D v3d){
		return new PVector((float) v3d.getX(),(float)  v3d.getY(), (float) v3d.getZ());
	}

	/**
	 * Convert from AMC to Processing vector implementation
	 * @param v3d the array of Vector3D to convert
	 * @return the PVector array result
	 */
	public static PVector[] convert(Vector3D[] v3d){
		PVector[] target = new PVector[v3d.length];
		for(int i = 0; i < target.length; i++) {
			target[i] = convert(v3d[i]);
		}
		return target;
	}

	/**
	 * Convert from AMC to Processing vector implementation
	 * @param v3d the 2D array of Vector3D to convert
	 * @return the PVector 2D array result
	 */
	public static PVector[][] convert(Vector3D[][] v3d){
		PVector[][] target = new PVector[v3d.length][];
		for(int i = 0; i < target.length; i++) {
			target[i] = new PVector[v3d[i].length];
			for(int j = 0; j < target[i].length; j++) {
				target[i][j] = convert(v3d[i][j]);
			}
		}
		return target;
	}

	/**
	 * Perform a spherical linear interpolation between 2 vectors. <br>
	 * The magnitude of the returned vector will also be interpolated.
	 * @param start the start vector (t == 0)
	 * @param end the end vector (t == 1)
	 * @param t parametric constrained to the range &ge; 0 and &le; 1
	 * @return the interpolated vector
	 */
	public static PVector slerp(final PVector start, final PVector end, float t) {
		float a = PVector.angleBetween(start, end);
		t = (t < 0) ? 0 : (t > 1) ? 1 : t;
		float sinA = PApplet.sin(a);
		float coef0 = PApplet.sin((1 - t) * a) / sinA;
		float coef1 = PApplet.sin(t * a) / sinA;
		return PVector.add(PVector.mult(start,  coef0), PVector.mult(end, coef1));
	}

	/**
	 * Perform a spherical linear interpolation between 2 vectors. <br>
	 * If required the returned vector will be normalized (i.e. a unit vector)
	 * 
	 * @param start the start vector (t == 0)
	 * @param end the end vector (t == 1)
	 * @param t parametric constrained to the range &ge; 0 and &le; 1
	 * @param norm if true will normalize the interpolated vector
	 * @return the interpolated vector
	 */
	public static PVector slerp(final PVector start, final PVector end, float t, boolean norm) {
		PVector sv = slerp(start, end, t);
		return norm ? sv.normalize() : sv;
	}

	/**
	 * Perform a spherical linear interpolation between 2 vectors. <br>
	 * The size of the returned vector will be set by the last parameter.
	 * 
	 * @param start the start vector (t == 0)
	 * @param end the end vector (t == 1)
	 * @param t parametric constrained to the range &ge; 0 and &le; 1
	 * @param mag the required size of the interpolated vector
	 * @return the interpolated vector
	 */
	public static PVector slerp(final PVector start, final PVector end, float t, float mag) {
		PVector sv = slerp(start, end, t);
		return sv.normalize().mult(mag);
	}

	/**
	 * Create and return a deep copy of a 1D array of PVectors
	 * @param array the PVector array to duplicate
	 * @return a copy of the original array
	 */
	public static PVector[] deepCopy(PVector[] array) {
		PVector[] v = new PVector[array.length];
		for(int i = 0; i < v.length; i++) {
			v[i] = array[i].copy();
		}
		return v;
	}

	/**
	 * Create and return a deep copy of a 2D array of PVectors
	 * @param array the PVector array to duplicate
	 * @return a copy of the original array
	 */
	public static PVector[][] deepCopy(PVector[][] array) {
		PVector[][] v = new PVector[array.length][];
		for(int i = 0; i < v.length; i++) {
			v[i] = new PVector[array[i].length];
			for(int j = 0; j < array[i].length; j++) {
				v[i][j] = array[i][j].copy();
			}
		}
		return v;
	}

	/**
	 * Create and return a deep copy of a 1D array of UVs
	 * @param array the UV array to duplicate
	 * @return a copy of the original array
	 */
	public static UV[] deepCopy(UV[] array) {
		UV[] v = new UV[array.length];
		for(int i = 0; i < v.length; i++) {
			v[i] = array[i].copy();
		}
		return v;
	}

	/**
	 * Create and return a deep copy of a 2D array of UVs
	 * @param array the UV array to duplicate
	 * @return a copy of the original array
	 */
	public static UV[][] deepCopy(UV[][] array) {
		UV[][] v = new UV[array.length][];
		for(int i = 0; i < v.length; i++) {
			int len = array[i].length;
			v[i] = new UV[len];
			for(int j = 0; j < len; j++) {
				v[i][j] = array[i][j].copy();
			}
		}
		return v;
	}

	/**
	 * Create and return a deep copy of a 1D int array
	 * @param array the int array to duplicate
	 * @return a copy of the original array
	 */
	public static int[] deepCopy(int[] array) {
		int[] a = new int[array.length];
		System.arraycopy(array, 0, a, 0, a.length);
		return a;
	}

	/**
	 * Reverse the elements in an the array of objects.
	 * @param <T> the type of element in the array
	 * @param array the array to be reversed
	 * @return the reversed array
	 */
	public static <T> T[] reverse(T[] array) {
		for(int i = 0; i < array.length/2; i++) {
			T temp = array[array.length - 1 - i];
			array[array.length - 1 - i] = array[i];
			array[i] = temp;
		}
		return array;
	}

	/**
	 * Reverse the elements (integer primitive type) 
	 * in an array.
	 * @param array the array to be reversed
	 * @return the reversed array
	 */
	public static int[] reverse(int[] array) {
		for(int i = 0; i < array.length/2; i++) {
			int temp = array[array.length - 1 - i];
			array[array.length - 1 - i] = array[i];
			array[i] = temp;
		}
		return array;
	}

	/**
	 * If two boxes overlap then the overlap region is another box. This method is used to 
	 * calculate the coordinates of the overlap. <br>
	 * The boxes are represented by the top-left and bottom-right corner coordinates. 
	 * If the returned array has a length:
	 * 0 then they do not overlap <br>
	 * 4 then these are the coordinates of the top-left and bottom-right corners of the overlap region.
	 *  
	 * @param ax0 top-left corner of rectangle A
	 * @param ay0 top-left corner of rectangle A
	 * @param ax1 bottom-right corner of rectangle A
	 * @param ay1 bottom-right corner of rectangle A
	 * @param bx0 top-left corner of rectangle B
	 * @param by0 top-left corner of rectangle B
	 * @param bx1 bottom-right corner of rectangle B
	 * @param by1 bottom-right corner of rectangle B
	 * @return an array with the overlap box coordinates (if any)
	 */
	public static int[] box_box_p(int ax0, int ay0, int ax1, int ay1, int bx0, int by0, int bx1, int by1) {
	  int[] result = new int[0];
	  int topA = Math.min(ay0, ay1);
	  int botA = Math.max(ay0, ay1);
	  int leftA = Math.min(ax0, ax1);
	  int rightA = Math.max(ax0, ax1);
	  int topB = Math.min(by0, by1);
	  int botB = Math.max(by0, by1);
	  int leftB = Math.min(bx0, bx1);
	  int rightB = Math.max(bx0, bx1);

	  if (botA <= topB  || botB <= topA || rightA <= leftB || rightB <= leftA)
	    return result;

	  int leftO = (leftA < leftB) ? leftB : leftA;
	  int rightO = (rightA > rightB) ? rightB : rightA;
	  int botO = (botA > botB) ? botB : botA;
	  int topO = (topA < topB) ? topB : topA;
	  result =  new int[] {leftO, topO, rightO, botO};
	  return result;
	}

}
