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
 * 2D space. <br>
 * Note the degree of a Bezier curve equals the number of control points. <br>
 * Its primary purpose is to act as a convenience class to maintain a collection
 * bezier controls points in 2 dimensions. <br>
 * 
 * In this library the Bezier2D object is used by the BezierShape class to create
 * a 3D shape by rotating it about the Y axis [0,1,0]. <br>
 * <pre>
 * Degree	Shape					<br>
 *   2		straight line			<br>
 *   3		quadratic bezier		<br>
 *   4		cubic bezier			<br>
 *   and so on						<br>
 * </pre> <br>
 * 
 * Based on source code found on the Internet and modified by the author to work
 * directly with Processing. The URL for the original code has been lost).
 * @author Peter Lager
 *
 */
public class BCurve2D extends AbstractPath {

	// Used to hold the control points
	private float[] px;
	private float[] py;

	// Used to hold intermediate values when calculating
	// a point on the curve
	private float[] pxi;
	private float[] pyi;

	// degree = order + 1  i.e. degree = number of control points
	// order = cubic : degree = 4
	private int degree;

	// Used to store intermediate values when calculating
	// the tangent or normal at a point
	private float[] b;

//	/**
//	 * Creates a Bezier object using two arrays for the x and y positions
//	 * for each control points. <br>
//	 * If the arrays passed to this constructor differ in length the extra 
//	 * in the longer array are ignored. <br>
//	 * 
//	 * @param x array of the x values of the control point positions
//	 * @param y array of the y values of the control point positions
//	 * @param nbrSlices the number of slices along the curve's length
//	 */
//	public BCurve2D(float[] x, float[] y){
//		super();
//		degree = Math.min(x.length, y.length);
//		makeArrays();
//		for(int i = 0; i < degree; i++){
//			px[i] = x[i];
//			py[i] = y[i];
//		}
//	}
//
//	/**
//	 * Creates a Bezier object using an array of control point positions. 
//	 * The bezier curve will use all of the points in the array. <br>
//	 * 
//	 * @param points 2D array[point no.][x/y] of control point positions
//	 * @param nbrSlices the number of slices along the curve's length
//	 */
//	public BCurve2D(float[][] points){
//		super();
//		degree = points.length;
//		makeArrays();
//		for(int i = 0; i < degree; i++){
//			px[i] = points[i][0];
//			py[i] = points[i][1];
//		}
//	}
//
//	/**
//	 * Create a Bezier curve that passes through the specified positions
//	 * @param points array of PVectors defining the spline.
//	 * @param nbrSlices the number of slices along the length of the path
//	 */
//	public BCurve2D(List<PVector> points) {
//		this(points.toArray(new PVector[points.size()]));
//	}
//	
//	/**
//	 * Creates a Bezier object using an array of control point positions. 
//	 * The bezier curve will use all of the points in the array. <br>
//	 * 
//	 * @param points array of vertices defining the hull for this Bezier curve
//	 * @param nbrSlices the number os slices along the curve's length
//	 */
//	public BCurve2D(PVector[] points){
//		super();
//		this.degree = points.length;
//		makeArrays();
//		for(int i = 0; i < degree; i++){
//			px[i] = points[i].x;
//			py[i] = points[i].y;
//		}
//	}

	/**
	 * Creates a Bezier object using two arrays for the x and y positions
	 * for each control points. <br>
	 * If the arrays passed to this constructor differ in length the extra 
	 * in the longer array are ignored. <br>
	 * 
	 * @param x array of the x values of the control point positions
	 * @param y array of the y values of the control point positions
	 * @param nbrSlices the number of slices along the curve's length
	 */
	public BCurve2D(float[] x, float[] y, int nbrSlices){
		super(nbrSlices);
		degree = Math.min(x.length, y.length);
		makeArrays();
		for(int i = 0; i < degree; i++){
			px[i] = x[i];
			py[i] = y[i];
		}
	}

	/**
	 * Creates a Bezier object using an array of control point positions. 
	 * The bezier curve will use all of the points in the array. <br>
	 * 
	 * @param points 2D array[point no.][x/y] of control point positions
	 * @param nbrSlices the number of slices along the curve's length
	 */
	public BCurve2D(float[][] points, int nbrSlices){
		super(nbrSlices);
		degree = points.length;
		makeArrays();
		for(int i = 0; i < degree; i++){
			px[i] = points[i][0];
			py[i] = points[i][1];
		}
	}

	/**
	 * Create a Bezier curve that passes through the specified positions
	 * @param points array of PVectors defining the spline.
	 * @param nbrSlices the number of slices along the length of the path
	 */
	public BCurve2D(List<PVector> points, int nbrSlices) {
		this(points.toArray(new PVector[points.size()]), nbrSlices);
	}
	
	/**
	 * Creates a Bezier object using an array of control point positions. 
	 * The bezier curve will use all of the points in the array. <br>
	 * 
	 * @param points array of vertices defining the hull for this Bezier curve
	 * @param nbrSlices the number os slices along the curve's length
	 */
	public BCurve2D(PVector[] points, int nbrSlices){
		super(nbrSlices);
		this.degree = points.length;
		makeArrays();
		for(int i = 0; i < degree; i++){
			px[i] = points[i].x;
			py[i] = points[i].y;
		}
	}

	/**
	 * Used by the ctors
	 */
	private void makeArrays(){
		px = new float[degree];
		py = new float[degree];
		pxi = new float[degree];
		pyi = new float[degree];
		b = new float[degree];
	}

	/**
	 * Insert a number of points into the bezier curve.
	 * 
	 * @param pts a 2D array of point i.e. [x][y]
	 * @param nbrPts the number of points to insert
	 * @param pos the position to insert (&le;0 before first point; &ge; degree after last point)
	 */
	public void insertCtrlPoints(float[][] pts, int nbrPts, int pos){
		pos = PApplet.constrain(pos, 0, degree);

		int ndegree = degree + nbrPts;
		float[] npx = new float[ndegree];
		float[] npy = new float[ndegree];
		pxi = new float[ndegree];
		pyi = new float[ndegree];
		b = new float[ndegree];

		int src = 0, dst;
		// Copy original points up to pos
		for(dst = 0; dst < pos; dst++){
			npx[dst] = px[src];
			npy[dst] = py[src];
			src++;
		}
		// Copy new points
		for(int newp = 0; newp < nbrPts; newp++){
			npx[dst] = pts[newp][0];
			npy[dst] = pts[newp][1];	
			dst++;
		}
		// Copy any remaining original points
		for(int i = 0; i < degree - pos; i++){
			npx[dst] = px[src];
			npy[dst] = py[src];
			dst++;
			src++;			
		}
		px = npx;
		py = npy;
		degree = ndegree;
	}

	/**
	 * Insert a number of points into the bezier curve.
	 * 
	 * @param ptsX array of point x values
	 * @param ptsY array of point y values
	 * @param nbrPts the number of points to insert
	 * @param pos the position to insert (&le;0 before first point; &ge; degree after last point)
	 */
	public void insertCtrlPoints(float[] ptsX, float ptsY[], int nbrPts, int pos){
		int no = Math.min(nbrPts, Math.min(ptsX.length, ptsY.length));
		float[][] temp = new float[no][2];
		for(int i = 0; i < no; i++){
			temp[i][0] = ptsX[i];
			temp[i][1] = ptsY[i];
		}
		insertCtrlPoints(temp, no, pos);
	}

	/**
	 * Insert a number of points into the bezier curve.
	 * 
	 * Although using PVector only the x,y values of the vector are used.
	 * 
	 * @param points an array of PVector's 
	 * @param nbrPts the number of points to insert
	 * @param pos the position to insert (&le;0 before first point; &ge; degree after last point)
	 */
	public void insertCtrlPoints(PVector[] points, int nbrPts, int pos){
		int no = PApplet.constrain(nbrPts, 0, points.length);
		float[][] temp = new float[no][2];
		for(int i = 0; i < no; i++){
			temp[i][0] = points[i].x;
			temp[i][1] = points[i].y;			
		}
		insertCtrlPoints(temp, no, pos);
	}

	/**
	 * Insert a single points into the bezier curve.
	 * 
	 * @param point a single point 
	 * @param pos the position to insert (&le;0 before first point; &ge; degree after last point)
	 */
	public void insertCtrlPoint(PVector point, int pos){
		float[][] temp = new float[1][2];
		temp[0][0] = point.x;
		temp[0][1] = point.y;
		insertCtrlPoints(temp, 1, pos);
	}

	/**
	 * Insert a single points into the bezier curve.
	 * 
	 * @param x x coordinate of point
	 * @param y y coordinate of point
	 * @param pos the position to insert (&le;0 before first point; &ge; degree after last point)
	 */
	public void insertCtrlPoint(float x, float y, int pos){
		float[][] temp = new float[1][2];
		temp[0][0] = x;
		temp[0][1] = y;
		insertCtrlPoints(temp, 1, pos);
	}


	/**
	 * Remove control points from <b>first</b> to <b>last</b> inclusive. <br>
	 * Silently fails if first or last are outside array bounds or last &lt; first or if it means the
	 * number of points left would be &lt; 2
	 * 
	 * @param first the first point to be removed
	 * @param last the last point to be removed
	 * @return true if points are successfully removed
	 */
	public boolean removeCtrlPoints(int first, int last){
		if(last >= first && first >= 0 && last <= degree && (degree - 1 + first - last) >= 2){
			int ndegree = degree -1 + first - last;
			float[] npx = new float[ndegree];
			float[] npy = new float[ndegree];
			pxi = new float[ndegree];
			pyi = new float[ndegree];
			b = new float[ndegree];
			int dst, src;
			// Copy upto but not including 'first'
			for(dst = 0; dst < first; dst++){
				npx[dst] = px[dst];
				npy[dst] = py[dst];				
			}
			// Copy those after last
			for(src = last+1; src < degree; src++){
				npx[dst] = px[src];
				npy[dst] = py[src];				
				dst++;
			}
			px = npx;
			py = npy;
			degree = ndegree;
			return true;
		}
		return false;
	}

	/**
	 * Removes a single control point <br>
	 * Silently fails if point is outside array bounds or if it would leave
	 * less than 2 control points.
	 *  
	 * @param point control point to remove
	 * @return true if point successfully removed
	 */
	public boolean removeCtrlPoint(int point){
		return removeCtrlPoints(point, point);
	}

	/**
	 * Change the value stored in a point.
	 * 
	 * @param point the control oint to change
	 * @param pos constrained to array bounds
	 */
	public void updateCtrlPoint(PVector point, int pos){
		pos = PApplet.constrain(pos, 0, degree - 1);
		px[pos] = point.x;
		py[pos] = point.y;
	}

	/**
	 * Change the value stored in a point.
	 *  
	 * @param x the new x value
	 * @param y the new y value
	 * @param pos constrained to array bounds
	 */
	public void updateCtrlPoint(float x, float y, int pos){
		pos = PApplet.constrain(pos, 0, degree - 1);
		px[pos] = x;
		py[pos] = y;
	}

	/**
	 * Get a control point 
	 * @param pos constrained to array bounds
	 * @return the control point at specified position
	 */
	public PVector getCtrlPoint(int pos){
		pos = PApplet.constrain(pos, 0, degree - 1);
		return new PVector(px[pos], py[pos], 0);
	}

	/**
	 * List the points to console, used for debugging
	 */
	public void listCtrlPoints(){
		System.out.println("\n==========================================");
		for(int i = 0; i < degree; i++){
			System.out.println("" + i + ")\t[" + px[i] + " " + py[i]+ "]");
		}
	}

	/**
	 * Get the number of control points used to form the curve. <br>
	 * @return number of points
	 */
	public int getNbrCtrlPoints() {
		return degree;
	}

	/**
	 * Get the bezier control points
	 * @return an array of the control points
	 */
	public PVector[] getCtrlPointArray() {
		PVector[] ctrlPoint = new PVector[degree];
		for(int i = 0; i < degree; i++)
			ctrlPoint[i] = new PVector(px[i], py[i], 0);
		return ctrlPoint;
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
		for(int j = degree-1; j > 0; j--){
			for(int i = 0; i < j; i++){
				pxi[i] = t1 * pxi[i] + t* pxi[i+1];
				pyi[i] = t1 * pyi[i] + t* pyi[i+1];
			}
		}
		return new PVector(pxi[0], pyi[0], 0);
	}

	/**
	 * Calculate the tangent vector for a point on the bezier curve
	 * 
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return the tangent vector (normalised)
	 */
	public PVector tangent(float t){
		PVector tangent;
		float tx,ty;
		bCoefficients(t);
		tx = bezierTangent(px,t);
		ty = bezierTangent(py,t);
		tangent = new PVector(-tx,-ty,0);
		tangent.normalize();
		return tangent;
	}

	/**
	 * Calculate the normal vector for a point on the bezier curve
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return the normal vector (normalised)
	 */
	public PVector orthogonal(float t){
		PVector ortho;
		float tx,ty;
		bCoefficients(t);
		tx = bezierTangent(px,t);
		ty = bezierTangent(py,t);
		ortho = new PVector(-ty, tx, 0);
		ortho.normalize();
		return ortho;
	}

	/**
	 * Used internally in calculating normals and tangents
	 * @param p coefficient array
	 * @param t parametric value &ge;0.0 and &le;1.0
	 * @return
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
