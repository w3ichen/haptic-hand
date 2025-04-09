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

import processing.core.PApplet;
import processing.core.PImage;
import processing.core.PVector;
import shapes3d.utils.Orientation;
import shapes3d.utils.Textures;

/**
 * A box where all the sides are of equal length that can be textured to give the
 * appearance of continuous sky. <br>
 * 
 * The shape's orientation has been changed so that the positive Y axis represents the UP direction. 
 * This is the default for OpenGL but the opposite of the UP vector set by Processing. This should
 * make working with the terrain class more intuitive since the vertical axis now represents height.
 * 
 * @author Peter Lager
 *
 */
public class SkyBox extends Box {

	/**
	 * Create a skybox of the specified size. The mid-height position will correspond 
	 * with a terrain height of zero.
	 * 
	 * The horizon will correspond to 
	 * @param size the length of the box sides
	 */
	public SkyBox(float size) {
		this(size, 0);
	}

	/**
	 * Unless you specify otherwise the mid-height position on the sky box will correspond
	 * to a terrain height of zero. You can change this by passing a non-zero value in
	 * the zero_pos parameter. This value is <i>proportional</i> to the size of the skybox so
	 * will be in the range -0.5 to +0.5 <br>
	 * You may need to experiment with different values for zero_pos for your sketch.
	 * 
	 * @param size the length of the box sides
	 * @param zero_pos controls the level on the box height corresponding to a terrain height = 0 (zero)
	 */
	public SkyBox(float size, float zero_pos) {
		super(size, size, size, new Orientation( new PVector(0, zero_pos, 0),
				new PVector(0, -1, 0)));
		drawMode(TEXTURE);
	}

	public SkyBox getThis() {
		return this;
	}

	/**
	 * The image is a composite of all sides sides laid out like <br>
	 * <pre>
	 *     | T |
	 * | L | F | R | B |
	 *     | Bo|
	 * </pre>
	 * <b>T</b>op, <b>L</b>eft, <b>F</b>ront, <b>R</b>ight, <b>B</b>ack and <b>Bo</b>ttom. <br>
	 *  
	 * @param app the enclosing PApplet object
	 * @param filename the filename of the image containing the composite picture
	 * @return this shape
	 */
	public SkyBox texture(PApplet app, String filename){
		return texture(Textures.loadImage(app, filename));
	}

	/**
	 * The image is a composite of all sides sides laid out like <br>
	 * <pre>
	 *     | T |
	 * | L | F | R | B |
	 *     | Bo|
	 * </pre>
	 * <b>T</b>op, <b>L</b>eft, <b>F</b>ront, <b>R</b>ight, <b>B</b>ack and <b>Bo</b>ttom. <br>
	 *  
	 * @param texture the image filename containing the composite picture
	 * @return this shape
	 */
	public SkyBox texture(PImage texture){
		int dw = texture.width / 4;
		int dh = texture.height / 3;
		texture(texture.get(dw, 0, dw, dh), TOP);
		texture(texture.get(0, dh, dw, dh), LEFT);
		texture(texture.get(dw, dh, dw, dh), FRONT);
		texture(texture.get(2 * dw, dh, dw, dh), RIGHT);
		texture(texture.get(3 * dw, dh, dw, dh), BACK);
		texture(texture.get(dw, 2 * dh, dw, dh), BOTTOM);
		return getThis();
	}

}
