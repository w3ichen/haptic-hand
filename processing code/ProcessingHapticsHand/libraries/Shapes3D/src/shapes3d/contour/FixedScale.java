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

/**
 * Defines the scale to be applied to the cross-section at various points 
 * along the shape's path.
 * 
 * @author Peter Lager
 *
 */
public final class FixedScale implements Scale {
	
	private final float sx, sy; 
	
	/**
	 * Apply a 1:1 scale so effectively does nothing.
	 */
	public FixedScale() {
		this(1, 1);
	}
	
	/**
	 * Apply a constant scale along along the path of the shape.
	 * @param sx scale to be applied on one axis
	 * @param sy scale to be applied on the other axis
	 */
	public FixedScale(float sx, float sy) {
		super();
		this.sx = sx;
		this.sy = sy;
	}

	/**
	 * @return the x axis scale
	 */
	@Override
	public float scaleX(float t) {
		return sx;
	}

	/**
	 * @return the y axis scale
	 */
	@Override
	public float scaleY(float t) {
		return sy;
	}

}
