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

import processing.core.PVector;
import shapes3d.utils.Util;

/**
 * This class defines a Bezier spline in 2D space that passes through a set of given 
 * points (called knots). All z values for the knots are set to 0, this will affect 
 * all PVector objects used to construct a spline knots.<br>
 * 
 * The curve between each pair of points is a cubic Bezier curve and the controls 
 * points are calculated to give a smooth transition along the spline. <br>
 * 
 * The position along the spline can be found using a parametric variable in the 
 * range &ge;0 and &le;1 <br>
 * 
 * 
 * Based on source code found on the Internet and modified by the author to work
 * directly with Processing. The URL for the original code has been lost).
 * 
 * @author Peter Lager
 *
 */
public class BSpline2D extends AbstractPath {

	protected BCurve2D[] bcurve3d;
	protected float[] tMax;
	protected float[] tLength;
	
//	/**
//	 * Creates a Bezier spline using two arrays for the x and y positions
//	 * for each control point (z = 0).<br>
//	 * If the arrays passed to this constructor differ in length the extra 
//	 * in the longer array are ignored. <br>
//	 * 
//	 * @param x array of the x values of the control point positions
//	 * @param y array of the y values of the control point positions
//	 * @param nbrSlices the number of slices along the curve's length
//	 */
//	public BSpline2D(float[] x, float[] y){
//		this(Util.makePVectorArray(x, y));
//	}
//
//
//	/**
//	 * Create a Bezier spline that passes through the specified positions
//	 * @param knots list of PVectors defining the spline.
//	 * @param nbrSlices the number of slices along the length of the path
//	 * @param ortho the orthogonal calculator to use
//	 */
//	public BSpline2D(List<PVector> knots) {
//		this(knots, null);
//	}
//
//	/**
//	 * Create a Bezier spline that passes through the specified positions
//	 * @param knots list of PVectors defining the spline.
//	 * @param nbrSlices the number of slices along the length of the path
//	 * @param ortho the orthogonal calculator to use
//	 */
//	public BSpline2D(List<PVector> knots, PathOrthogonal ortho) {
//		this(knots.toArray(new PVector[knots.size()]), ortho);
//	}
//
//	/**
//	 * Create a Bezier spline that passes through the specified positions
//	 * @param knots array of PVectors defining the spline.
//	 * @param nbrSlices the number of slices along the length of the path
//	 */
//	public BSpline2D(PVector[] knots) {
//		this(knots, null);
//	}
//
//	/**
//	 * Create a Bezier spline that passes through the specified positions
//	 * @param knots array of PVectors defining the spline.
//	 * @param nbrSlices the number of slices along the length of the path
//	 * @param ortho the orthogonal calculator to use
//	 */
//	public BSpline2D(PVector[] knots, PathOrthogonal ortho) {
//		super();
//		for(PVector knot : knots) {
//			knot.z = 0;
//		}
//		calculateSpline(knots);
//		orthoCalculator = ortho;
//	}

	/**
	 * Creates a Bezier spline using two arrays for the x and y positions
	 * for each control point (z = 0).<br>
	 * If the arrays passed to this constructor differ in length the extra 
	 * in the longer array are ignored. <br>
	 * 
	 * @param x array of the x values of the control point positions
	 * @param y array of the y values of the control point positions
	 * @param nbrSlices the number of slices along the curve's length
	 */
	public BSpline2D(float[] x, float[] y, int nbrSlices){
		this(Util.makePVectorArray(x, y), nbrSlices);
	}


	/**
	 * Create a Bezier spline that passes through the specified positions
	 * @param knots list of PVectors defining the spline.
	 * @param nbrSlices the number of slices along the length of the path
	 * @param ortho the orthogonal calculator to use
	 */
	public BSpline2D(List<PVector> knots, int nbrSlices) {
		this(knots, nbrSlices, null);
	}

	/**
	 * Create a Bezier spline that passes through the specified positions
	 * @param knots list of PVectors defining the spline.
	 * @param nbrSlices the number of slices along the length of the path
	 * @param ortho the orthogonal calculator to use
	 */
	public BSpline2D(List<PVector> knots, int nbrSlices, PathOrthogonal ortho) {
		this(knots.toArray(new PVector[knots.size()]), nbrSlices, ortho);
	}

	/**
	 * Create a Bezier spline that passes through the specified positions
	 * @param knots array of PVectors defining the spline.
	 * @param nbrSlices the number of slices along the length of the path
	 */
	public BSpline2D(PVector[] knots, int nbrSlices) {
		this(knots, nbrSlices, null);
	}

	/**
	 * Create a Bezier spline that passes through the specified positions
	 * @param knots array of PVectors defining the spline.
	 * @param nbrSlices the number of slices along the length of the path
	 * @param ortho the orthogonal calculator to use
	 */
	public BSpline2D(PVector[] knots, int nbrSlices, PathOrthogonal ortho) {
		super(nbrSlices);
		for(PVector knot : knots) {
			knot.z = 0;
		}
		calculateSpline(knots);
		orthoCalculator = ortho;
	}

	/**
	 * Method defines the function V = pos(t) where t is in the range &ge;0.0 and &le;1.0
	 * 
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates at a position t
	 */
	public PVector point(float t) {
		int bc = 0;
		while(bc < tMax.length-1 && t > tMax[bc])
			bc++;
		float nt = (bc == 0) ? t/tLength[0] : (t - tMax[bc-1])/tLength[bc];
		return bcurve3d[bc].point(nt);
	}

	/**
	 * Method defines the function V = tangent(t) where t is in the range&ge;0.0 and &le;1.0
	 * 
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return a PVector giving the x,y,z coordinates of the tangent at position t
	 */
	@Override
	public PVector tangent(float t) {
		int bc = 0;
		while(bc < tMax.length-1 && t > tMax[bc])
			bc++;
		float nt = (bc == 0) ? t/tLength[0] : (t - tMax[bc-1])/tLength[bc];
		return bcurve3d[bc].tangent(nt);
	}

	/**
	 * Used internally to calculate the controls points.
	 * 
	 * @param knots number of vertices defining the curve
	 */
	private void calculateSpline(PVector[] knots){
		int nbrKnots = knots.length;
		int n = nbrKnots - 1;
		PVector[] p2, p1, r;
		float[] a, b, c;
		// Init arrays
		a = new float[n];
		b = new float[n];
		c = new float[n];
		p1 = new PVector[n];
		p2 = new PVector[n];
		r = new PVector[n];
		// Left segment
		a[0] = 0;
		b[0] = 2;
		c[0] = 1;
		r[0] = PVector.add(knots[0], PVector.mult(knots[1], 2));
		// Internal segments
		for(int i = 1; i < n-1; i++){
			a[i] = 1;
			b[i] = 4;
			c[i] = 1;
			r[i] = PVector.add(PVector.mult(knots[i], 4), PVector.mult(knots[i+1], 2));
		}
		// Right segment
		a[n-1] = 2;
		b[n-1] = 7;
		c[n-1] = 0;
		r[n-1] = PVector.add(PVector.mult(knots[n-1], 8), knots[n]);
		// Solves Ax = b with Thomas algorithm
		for(int i = 1; i < n; i++){
			float m = a[i]/b[i-1];
			b[i] = b[i] - m * c[i-1];
			r[i].sub(PVector.mult(r[i-1], m));
		}
		// Calculate p1 for elements  [0 .. n-1] element [n] required
		p1[n-1] = PVector.div(r[n-1], b[n-1]);
		for(int i = n - 2; i >= 0; --i){
			p1[i] = PVector.sub(r[i], PVector.mult(p1[i+1], c[i]));
			p1[i].div(b[i]);
		}
		// Calculate p2 for elements  [1 .. n] element [0] required
		for(int i = 0; i < n-1; i++){
			p2[i] = PVector.mult(knots[i+1], 2);
			p2[i].sub(p1[i+1]);
		}
		p2[n-1] = PVector.mult(PVector.add(knots[n], p1[n-1]), 0.5f);

		// Build the spline for BCurve3D segments and estimate the overall
		// length of the spline
		float splineLength = 0;
		bcurve3d = new BCurve2D[n];
		float[] bcurveLength = new float[n];
		for(int i = 0; i < n; i++){
			bcurve3d[i] = new BCurve2D( new PVector[] {knots[i], p1[i], p2[i], knots[i+1] }, 4);
			bcurveLength[i] = bcurve3d[i].length(100);
			splineLength += bcurveLength[i];
		}
		// Calculate the 't' values for each knot so that each BCurve3D has
		// a 't' range proportional to its length.
		tMax = new float[n];
		tLength = new float[n];
		for(int i = 0; i < bcurve3d.length; i++){
			tLength[i] = bcurveLength[i] / splineLength;
			tMax[i] = tLength[i];
			if(i > 0)
				tMax[i] += tMax[i-1];
		}
	}


}
