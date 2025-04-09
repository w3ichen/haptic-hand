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

import processing.core.PVector;
import shapes3d.org.apache.commons.math.geometry.Rotation;
import shapes3d.org.apache.commons.math.geometry.Vector3D;
import shapes3d.utils.Messages;
import shapes3d.utils.SConstants;
import shapes3d.utils.Util;

/**
 * At any point along the s continuous curve in 2D space there is a 
 * single curve tangent line and two curve normals (orthogonals).
 * In 3D space it is slightly more complicated, although there is a 
 * single tangent at any point along the curve there RE an infinite 
 * number of orthogonals. To create the shapes this library needs to 
 * know the orthogonal at any point along the curve. <br>
 * 
 * A bad choice of orthogonal can cause unwanted rotations and/or 
 * twists in the cross-section. If the user does not choose an 
 * orthogonal Shapes3D will choose what it thinks best from four 
 * different algorithms. Even so it is still possible to get unwanted 
 * rotations/twists in which case the user can provide their own
 * orthogonal calculator.
 * 
 * @author Peter Lager
 *
 */
public abstract class PathOrthogonal implements SConstants {

	public static PathOrthogonal getBest(Path p, int n) {
		// The tangent to path in contour space
		Vector3D vtContour = new Vector3D(0, 0, 1);
		// Any orthogonal vector to the tangent
		// i.e. any line in XY space with Z=0
		Vector3D voContour = new Vector3D(1, 1, 0);
		Vector3D ctrPoint = new Vector3D(0,1,0);
		float deltaT = 1f / (n - 1);
		PathOrthogonal[] calculators = new PathOrthogonal[] {
				ORTHO_X, ORTHO_Y, ORTHO_Z, ORTHO_A			
		};
		float[] sum = new float[calculators.length];
		PVector[] prevNorm = new PVector[calculators.length];
		for(int i = 0; i < prevNorm.length; i++) {
			prevNorm[i] = new PVector();
		}
		for(int pathPos = 0; pathPos < n; pathPos++) {
			float t = pathPos * deltaT;
			PVector tan = p.tangent(t);
			for(int cn = 0; cn < calculators.length; cn++) {
				PVector ortho = calculators[cn].getOrthogonal(tan);
				Rotation rot = new Rotation(
						vtContour, 
						voContour, 
						Util.convert(tan), 
						Util.convert(ortho));
				PVector currNorm = Util.convert(rot.applyTo(ctrPoint));
				if(pathPos > 0) {
					sum[cn] += PVector.angleBetween(prevNorm[cn], currNorm);
					prevNorm[cn].set(currNorm);
				}
			}
		}
//		for(int i = 0; i < calculators.length; i++) {
//			System.out.println(i + "  " + calculators[i].toString() + "\t: " +sum[i] );
//		}
		float bestScore = Float.MAX_VALUE;
		PathOrthogonal best = null;
		for(int i = 0; i < calculators.length; i++) {
			if(!Float.isNaN(sum[i]) && sum[i] < bestScore) {
				bestScore = sum[i];
				best = calculators[i];
			}
		}
//		System.out.println("\nBest is " + best.toString());
		return best;
	}

	/**
	 * Calculate the orthogonal to use for a particular path.
	 * 
	 * @param tan the tangent
	 * @return the orthogonal to the tangent
	 */
	public abstract PVector getOrthogonal(PVector tan); 
	
	// ======================================================================
	// Concrete child classes representing the 4 possible algorithms
	// ======================================================================
	


	/**
	 * Use the dot-product algorithm for the X axis
	 * 
	 * @author Peter Lager
	 */
	public static class PathNormalX extends PathOrthogonal {

		@Override
		public PVector getOrthogonal(PVector tan) {
			return new PVector(-(tan.y + tan.z), tan.x, tan.x);
		}

		public String toString() {
			return "ORTHO_X";
		}
	}

	/**
	 * Use the dot-product algorithm for the Y axis
	 * 
	 * @author Peter Lager
	 */
	public static class PathNormalY extends PathOrthogonal {

		@Override
		public PVector getOrthogonal(PVector tan) {
			return new PVector(tan.y, -(tan.x + tan.z), tan.y);
		}

		public String toString() {
			return "ORTHO_Y";
		}
	}

	/**
	 * Use the dot-product algorithm for the Z axis
	 * 
	 * @author Peter Lager
	 */
	public static class PathNormalZ extends PathOrthogonal {

		@Override
		public PVector getOrthogonal(PVector tan) {
			return new PVector(tan.z, tan.z, -(tan.x + tan.y));
		}
		
		public String toString() {
			return "ORTHO_Z";
		}
	}

	/**
	 * This implementation came from the Apache Maths Commons project. <br>
	 * I have modified the implementation to use Processing's PVector class
	 * and not to return null if tan has a zero magnitude.
	 */
	public static class PathNormalAMC extends PathOrthogonal {

		@Override
		public PVector getOrthogonal(PVector tan) {
			float threshold, inverse;
			threshold = 0.6f * tan.mag();
			if (threshold == 0) {
				System.out.println(Messages.build("Vector {0} has zero magnitude", tan));
				return new PVector(Float.NaN, Float.NaN, Float.NaN);
			}
			if ((tan.x >= -threshold) && (tan.x <= threshold)) {
				inverse  = 1 / (float)Math.sqrt(tan.y * tan.y + tan.z * tan.z);
				return new PVector(0, inverse * tan.z, -inverse * tan.y);
			} 
			else if ((tan.y >= -threshold) && (tan.y <= threshold)) {
				inverse  = 1 / (float)Math.sqrt(tan.x * tan.x + tan.z * tan.z);
				return new PVector(-inverse * tan.z, 0, inverse * tan.x);
			}
			inverse  = 1 / (float)Math.sqrt(tan.x * tan.x + tan.y * tan.y);
			return new PVector(inverse * tan.y, -inverse * tan.x, 0);		
		}
		
		public String toString() {
			return "ORTHO_A";
		}
	}




}


