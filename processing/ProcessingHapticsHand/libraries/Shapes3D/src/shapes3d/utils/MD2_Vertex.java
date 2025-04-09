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

/**
 * For each point in the model we store the texture coordinates and an 
 * index pointer to an array of PVector that hold the XYZ coordinates.
 * 
 * Texture coordinates are normalized i.e. in the range 0.0 to 1.0 inclusive.
 *
 * @author Peter Lager
 *
 */
public class MD2_Vertex {
	public float s;
	public float t;
	public int idx;

	/**
	 * Parameter ctor
	 * @param s horizontal texture coordinate
	 * @param t vertical texture coordinate
	 * @param idx the index to the vertex array
	 */
	public MD2_Vertex(float s, float t, int idx) {
		this.s = s;
		this.t = t;
		this.idx = idx;
	}

	public String toString(){
		return (""+idx+"\t"+s+"\t"+t);
	}
}
