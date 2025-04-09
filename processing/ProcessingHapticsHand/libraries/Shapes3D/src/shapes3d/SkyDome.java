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

import processing.core.PVector;
import shapes3d.utils.Orientation;

/**
 * A circular dome of user defined height that can be textured to give the
 * appearance of continuous sky. <br>
 * 
 * The shape's orientation has been changed so that the positive Y axis represents the UP direction. 
 * This is the default for OpenGL but the opposite of the UP vector set by Processing. This should
 * make working with the terrain class more intuitive since the vertical axis now represents height.
 * 
 * @author Peter Lager
 *
 */
public class SkyDome extends Dome {

	public SkyDome(float radius, float height, int nbrSegs, int nbrSlices) {
		this(radius, height, nbrSegs, nbrSlices, 0);
	}
	
	public SkyDome(float radius, float height, int nbrSegs, int nbrSlices, float zero_pos) {
		super(radius, height, radius, nbrSegs, nbrSlices, new Orientation( new PVector(0, zero_pos, 0),
				new PVector(0, -1, 0)));
		drawMode(TEXTURE);
	}

	public SkyDome getThis() {
		return this;
	}

}
