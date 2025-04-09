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
 * Simple class to hold texture coordinates. <br>
 * Only used by Cone class and Mesh2DCoreWithCaps.EndCap classes
 * to hold 'circular' coordinates on a rectangular image.  
 * 
 * @author Peter Lager
 *
 */
public class UV {

	public float u;
	public float v;
	
	/**
	 * Create a UV object with coordinates [0,0]
	 */
	public UV() {
		u = 0.0f;
		v = 0.0f;
	}

	/**
	 * Create a UV object with user defined coordinates
	 * @param u the horizontal coordinate
	 * @param v the vertical coordinate
	 */
	public UV(float u, float v) {
		this.u = u;
		this.v = v;
	}
	
	/**
	 * Set the texture coordinates
	 * @param u the horizontal coordinate
	 * @param v the vertical coordinate
	 */
	public void set(float u, float v) {
		this.u = u;
		this.v = v;
	}
	
	/**
	 * Set the texture coordinates from an existing UV object.
	 * @param uv copy the uv coordinates from here
	 */
	public void set(UV uv) {
		this.u = uv.u;
		this.v = uv.v;
	}
	
	/**
	 * Get a deep copy (new instance) of the object.
	 * @return the deep copy
	 */
	public UV copy() {
		return new UV(u, v);
	}
	
	/**
	 * Creates a string representing UV coordinates stored in the object.
	 */
	public String toString(){
		return"[UV " + u + ", "+v +"]";
	}

}
