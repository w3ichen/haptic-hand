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

package shapes3d.path;

import java.util.List;

import processing.core.PApplet;
import processing.core.PVector;

/**
 * This class is used to represent a single Bezier curve of degree &ge; 2 in
 * 3D space. <br>
 * Note the degree of a Bezier curve equals the number of control points. <br>
 * Its primary purpose is to act as a convenience class to maintain a collection
 * Bezier controls points in 3 dimensions. <br>
 * 
 * In this library the P_Bezier3D object is used by the BezTube class to create
 * a tube that bends along  by rotating it about the Y axis [0,1,0]. <br>
 * <pre>
 * Degree	Shape					<br>
 *   2		straight line			<br>
 *   3		quadratic bezier		<br>
 *   4		cubic bezier			<br>
 *   and so on						<br>
 * </pre>
 * It can also be used as a path for an Extrusion. <br>
 * 
 * Based on source code found on the Internet and modified by the author to work
 * directly with Processing. The URL for the original code has been lost).
 * @author Peter Lager
 *
 */
public class BCurve3D extends AbstractPath {
	
	// Used to hold the control points
	private float[] px;
	private float[] py;
	private float[] pz;

	// Used to hold intermediate values when calculating
	// a point on the curve
	private float[] pxi;
	private float[] pyi;
	private float[] pzi;

	// degree = order + 1  i.e. degree = number of points
	// order = cubic : degree = 4
	private int degree;

	// Used to store intermediate values when calculating
	// the tangent or normal at a point
	private float[] b;

//	/**
//	 * Creates a Bezier object using an array of control point positions. 
//	 * The bezier curve will use all of the points in the array. <br>
//	 * 
//	 * @param points 2D array[point no.][x/y/z] of control point positions
//	 * @param nbrSlices the number of mesh sections along the path
//	 */
//	public BCurve3D(float[][] points) {
//		this(points, null);
//	}
//
//	/**
//	 * Creates a Bezier object using an array of control point positions. 
//	 * The bezier curve will use all of the points in the array. <br>
//	 * 
//	 * @param points 2D array[point no.][x/y/z] of control point positions
//	 * @param nbrSlices the number of mesh sections along the path
//	 * @param ortho the orthogonal calculator to use
//	 */
//	public BCurve3D(float[][] points, PathOrthogonal ortho) {
//		super();
//		degree = Math.min(points[0].length, points[1].length);
//		makeArrays();
//		for(int i = 0; i < degree; i++){
//			px[i] = points[i][0];
//			py[i] = points[i][1];
//			pz[i] = points[i][2];
//		}
//		orthoCalculator = ortho;
//	}
//
//	/**
//	 * Create a Bezier curve that passes through the specified positions
//	 * @param points array of PVectors defining the spline.
//	 * @param nbrSlices the number of slices along the length of the path
//	 */
//	public BCurve3D(List<PVector> points) {
//		this(points, null);
//	}
//	
//	/**
//	 * Create a Bezier curve that passes through the specified positions
//	 * @param points list of PVectors defining the spline.
//	 * @param nbrSlices the number of slices along the length of the path
//	 * @param ortho the orthogonal calculator to use
//	 */
//	public BCurve3D(List<PVector> points, PathOrthogonal ortho) {
//		this(points.toArray( new PVector[points.size()]), ortho);
//	}
//
//	/**
//	 * Creates a Bezier object using an array of control point positions. 
//	 * The bezier curve will use all of the points in the array. <br>
//	 * 
//	 * @param points array of vertices defining the hull for this Bezier curve
//	 * @param nbrSlices the number of mesh sections along the path
//	 */
//	public BCurve3D(PVector[] points){
//		this(points, null);
//	}
//	
//	/**
//	 * Creates a Bezier object using an array of control point positions. 
//	 * The bezier curve will use all of the points in the array. <br>
//	 * 
//	 * @param points array of vertices defining the hull for this Bezier curve
//	 * @param nbrSlices the number of mesh sections along the path
//	 * @param ortho the orthogonal calculator to use
//	 */
//	public BCurve3D(PVector[] points, PathOrthogonal ortho){
//		super();
//		degree = points.length;
//		makeArrays();
//		for(int i = 0; i < degree; i++){
//			px[i] = points[i].x;
//			py[i] = points[i].y;
//			pz[i] = points[i].z;
//		}
//		orthoCalculator = ortho;
//	}

	
	/**
	 * Creates a Bezier object using an array of control point positions. 
	 * The bezier curve will use all of the points in the array. <br>
	 * 
	 * @param points 2D array[point no.][x/y/z] of control point positions
	 * @param nbrSlices the number of mesh sections along the path
	 */
	public BCurve3D(float[][] points, int nbrSlices) {
		this(points, nbrSlices, null);
	}

	/**
	 * Creates a Bezier object using an array of control point positions. 
	 * The bezier curve will use all of the points in the array. <br>
	 * 
	 * @param points 2D array[point no.][x/y/z] of control point positions
	 * @param nbrSlices the number of mesh sections along the path
	 * @param ortho the orthogonal calculator to use
	 */
	public BCurve3D(float[][] points, int nbrSlices, PathOrthogonal ortho) {
		super(nbrSlices);
		degree = Math.min(points[0].length, points[1].length);
		makeArrays();
		for(int i = 0; i < degree; i++){
			px[i] = points[i][0];
			py[i] = points[i][1];
			pz[i] = points[i][2];
		}
		orthoCalculator = ortho;
	}

	/**
	 * Create a Bezier curve that passes through the specified positions
	 * @param points array of PVectors defining the spline.
	 * @param nbrSlices the number of slices along the length of the path
	 */
	public BCurve3D(List<PVector> points, int nbrSlices) {
		this(points, nbrSlices, null);
	}
	
	/**
	 * Create a Bezier curve that passes through the specified positions
	 * @param points list of PVectors defining the spline.
	 * @param nbrSlices the number of slices along the length of the path
	 * @param ortho the orthogonal calculator to use
	 */
	public BCurve3D(List<PVector> points, int nbrSlices, PathOrthogonal ortho) {
		this(points.toArray( new PVector[points.size()]), nbrSlices, ortho);
	}

	/**
	 * Creates a Bezier object using an array of control point positions. 
	 * The bezier curve will use all of the points in the array. <br>
	 * 
	 * @param points array of vertices defining the hull for this Bezier curve
	 * @param nbrSlices the number of mesh sections along the path
	 */
	public BCurve3D(PVector[] points, int nbrSlices){
		this(points, nbrSlices, null);
	}
	
	/**
	 * Creates a Bezier object using an array of control point positions. 
	 * The bezier curve will use all of the points in the array. <br>
	 * 
	 * @param points array of vertices defining the hull for this Bezier curve
	 * @param nbrSlices the number of mesh sections along the path
	 * @param ortho the orthogonal calculator to use
	 */
	public BCurve3D(PVector[] points, int nbrSlices, PathOrthogonal ortho){
		super(nbrSlices);
		degree = points.length;
		makeArrays();
		for(int i = 0; i < degree; i++){
			px[i] = points[i].x;
			py[i] = points[i].y;
			pz[i] = points[i].z;
		}
		orthoCalculator = ortho;
	}
	
	/**
	 * Used by the ctors
	 */
	private void makeArrays(){
		px = new float[degree];
		py = new float[degree];
		pz = new float[degree];
		pxi = new float[degree];
		pyi = new float[degree];
		pzi = new float[degree];
		b = new float[degree];
	}

	/* 
	 * #############################################################
	 * The following methods relate to the actual Bexzier curve
	 * #############################################################
	 */
	
	/**
	 * Calculate the point for a given parametric point 't' on the bezier curve. 
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return (x,y) position for given t value
	 */
	public PVector point(float t){
		float t1 = 1.0f - t;
		System.arraycopy(px, 0, pxi, 0, degree);
		System.arraycopy(py, 0, pyi, 0, degree);
		System.arraycopy(pz, 0, pzi, 0, degree);
		for(int j = degree-1; j > 0; j--){
			for(int i = 0; i < j; i++){
				pxi[i] = t1 * pxi[i] + t * pxi[i+1];
				pyi[i] = t1 * pyi[i] + t * pyi[i+1];
				pzi[i] = t1 * pzi[i] + t * pzi[i+1];
			}
		}
		return new PVector(pxi[0], pyi[0], pzi[0]);
	}
	
	/**
	 * Calculate the tangent vector for a point on the bezier curve
	 * 
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return the tangent vector (normalized)
	 */
	public PVector tangent(float t){
		PVector tangent;
		float tx, ty, tz;
		bCoefficients(t);
		tx = bezierTangent(px,t);
		ty = bezierTangent(py,t);
		tz = bezierTangent(pz,t);
		tangent = new PVector(-tx,-ty,-tz);
		tangent.normalize();
		return tangent;
	}

	/**
	 * Used internally in calculating normals and tangents
	 * @param p internal coefficients
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return the tangent at the 
	 */
	private float bezierTangent(float[] p, float t) {
		float v = 0.0f;
		for(int i = 1; i < degree; i++){
			v += (p[i-1] - p[i])*b[i];
		}
		return v;
	}

	/**
	 * Used internally in calculating normals and tangents
	 * @param t parametric value &ge;0.0 and &le;1.0
	 */
	private void bCoefficients(float t){
		for(int j = 0; j < degree; j++)
			b[j] = 0;
		b[1] = 1;
		for(int j = 1; j < degree-1; j++){
			for(int i = j+1; i > 0; i--){
				b[i] = (1-t)*b[i] + t*b[i-1];
			}
		}
	}

	/**
	 * Calculate the path length of a section of Bezier curve. <br>
	 * There is no formula for the exact length of a Bezier curve so any method
	 * will always be approximate. <br>
	 * This method will always 'underestimate' the actual path length. It works
	 * by subdividing the Bezier curve into a number of straight line segments
	 * and summing their lengths. <br>
	 * The number of subdivisions can be increased to the accuracy of the result 
	 * but at the cost of additional computation. <br>
	 * You may want to experiment but 100+ subdivisions normally give quite good 
	 * results. <br>
	 * 
	 * @param t0 start ( &ge;0.0 and  &lt;t1 )
	 * @param t1 end ( &gt;t0 and &le;1.0 )
	 * @param steps number of subdivisions
	 * @return length of the curve section
	 */
	public float length(float t0, float t1, int steps){
		t0 = PApplet.constrain(t0, 0.0f, 1.0f);
		t1 = PApplet.constrain(t1, 0.0f, 1.0f);
		float dist = (t0 == t1)? 0 : -1;
		if(steps > 1){
			if(t0 > t1){
				float temp = t0;
				t0 = t1;
				t1 = temp;
			}
			float t = t0, deltaT = 1.0f / (steps - 1);
			PVector[] points = new PVector[steps];
			for(int i = 0; i < steps; i++){
				points[i] = point(t);
				t += deltaT;
			}

			dist  = PVector.dist(points[0], points[1]);
			for(int i = 2; i < steps; i++)
				dist += PVector.dist(points[i-1], points[i]);
		}
		return dist;
	}
	
	/**
	 * Calculate the path length of the Bezier curve. <br>
	 * There is no formula for the exact length of a Bezier curve so any method
	 * will always be approximate. <br>
	 * This method will always 'underestimate' the actual path length. It works
	 * by subdividing the Bezier curve into a number of straight line segments
	 * and summing their lengths. <br>
	 * The number of subdivisions can be increased to the accuracy of the result 
	 * but at the cost of additional computation. <br>
	 * You may want to experiment but 100+ subdivisions normally give quite good 
	 * results. <br>
	 * 
	 * @param steps number of subdivisions
	 * @return length of the curve
	 */
	public float length(int steps){
		float dist = 0;
		if(steps > 1){
			float deltaT = 1.0f / (steps -1);
			PVector last_pos = point(0);
			for(int s = 1; s < steps; s++) {
				PVector pos = point(s * deltaT);
				dist += PVector.dist(last_pos, pos);
				last_pos = pos;
			}
		}
		return dist;
	}

}
