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

public final class LinearScale implements Scale {

	private final float sx0, sy0;
	private final float rangeX, rangeY;
	

	/**
	 * This provides a 1:1 scaler in both X &amp; Y axes. Effectively it does nothing.
	 */
	public LinearScale() {
		this(1, 1, 1, 1);
	}
	
	/**
	 * Apply a linear scale to the cross-section along the path of the shape.
	 * 
	 * @param sx0 start scale along x axis (t = 0)
	 * @param sx1 end scale along x axis (t = 1)
	 * @param sy0 start scale along y axis (t = 0)
	 * @param sy1 end scale along y axis (t = 1)
	 */
	public LinearScale(float sx0, float sx1, float sy0, float sy1) {
		super();
		this.sx0 = sx0;
		this.sy0 = sy0;
		this.rangeX = sx1 - sx0;
		this.rangeY = sy1 - sy0;
	}

	/**
	 * 
	 * @param t in the range &ge;0 and &le;1
	 * @return returns the scale factor in the x direction
	 */
	@Override
	public float scaleX(float t) {
		return sx0 + t * rangeX;
	}

	/**
	 * 
	 * @param t in the range &ge;0 and &le;1
	 * @return returns the scale factor in the y direction
	 */
	@Override
	public float scaleY(float t) {
		return sy0 + t * rangeY;
	}
	
	
}
