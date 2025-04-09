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

package shapes3d.contour;

import processing.core.PApplet;
import shapes3d.path.Path;

/**
 * 
 * Use a BCurve2D or BSpline2D (or any curve that implements the 
 * Path interface)to define the shape of the scale curve.
 * 
 * @author Peter Lager
 *
 */
public class PathScale implements Scale {

	private Path x_curve = null;
	private Path y_curve = null;
	
	/**
	 * @param x_curve
	 * @param y_curve
	 */
	public PathScale(Path x_curve, Path y_curve) {
		this.x_curve = x_curve;
		this.y_curve = y_curve;
	}


	@Override
	public float scaleX(float t) {
		t = PApplet.constrain(t, 0, 1);
		return x_curve.point(t).y;
	}

	@Override
	public float scaleY(float t) {
		t = PApplet.constrain(t, 0, 1);
		return y_curve.point(t).y;
	}

	
}
