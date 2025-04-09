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

import processing.core.PApplet;
import processing.core.PConstants;
import processing.core.PGraphics;

/**
 * This class holds the details for a perspective that can be applied to 
 * a PGraphics3D object.
 * 
 * @author Peter Lager
 *
 */
public final class Perspective implements PConstants {
	
	private float fov;
	private float aspectRatio;
	private float nearZ;
	private float farZ;
	
	private float cosFov2;
	
	/**
	 * Create a perspective suitable for a graphics object with the specified
	 * width and height in pixels 
	 * @param width the width in pixels
	 * @param height the height in pixels
	 */
	public Perspective(float width, float height) {
		fov = PI / 3;
		cosFov2 = (float) Math.cos(0.55 * fov);
		float cameraZ = (height / 2.0f) / PApplet.tan(fov / 2);
		nearZ = cameraZ / 10;
		farZ = cameraZ * 10;
		aspectRatio = width / height;
	}
	
	/**
	 * Create a perspective suitable for the specified graphics object.
	 * 
	 * @param pg the PGraphics3D object
	 */
	public Perspective(PGraphics pg) {
		this(pg.width, pg.height);
	}

	/**
	 * Apply this perspective to the graphics context.
	 * 
	 * @param pg the PGraphics3D object
	 */
	public void apply(PGraphics pg) {
		pg.perspective(fov, aspectRatio, nearZ, farZ);
	}
	
	/**
	 * Get the field of view
	 * @return the field of view
	 */
	public float fov() {
		return fov;
	}

	/**
	 * Set the field of view angle (radians)
	 * @param fov the fov to set
	 * @return this perspective
	 */
	public Perspective fov(float fov) {
		this.fov = fov;
		cosFov2 = (float) Math.cos(0.55 * fov);
		return this;
	}

	/**
	 * This can be used to determine whether a shape is within
	 * the field of view.
	 * 
	 * @return field of view limit value
	 */
	public float fovLimit() {
		return cosFov2;
	}
	
	/**
	 * Get the aspect ratio i.e. width/height
	 * @return the aspectRatio
	 */
	public float aspectRatio() {
		return aspectRatio;
	}

	/**
	 * Set the aspect ratio for this perspective
	 * @param aspectRatio the aspectRatio to set
	 * @return this perspective
	 */
	public Perspective aspectRatio(float aspectRatio) {
		this.aspectRatio = aspectRatio;
		return this;
	}

	/**
	 * Get the near zone distance
	 * @return the nearZ
	 */
	public float nearZ() {
		return nearZ;
	}

	/**
	 * Set the near zone distance
	 * @param nearZ the nearZ to set
	 * @return this perspective
	 */
	public Perspective nearZ(float nearZ) {
		this.nearZ = nearZ;
		return this;
	}

	/**
	 * Get the far zone distance
	 * @return the farZ
	 */
	public float farZ() {
		return farZ;
	}

	/**
	 * Set the far zone distance
	 * @param farZ the farZ to set
	 * @return this perspective
	 */
	public Perspective farZ(float farZ) {
		this.farZ = farZ;
		return this;
	}
	
	public String toString() {
		StringBuilder sb = (new StringBuilder("======  Perspective  ============\n"))
		.append("FOV      : ").append(fov).append("\n")
		.append("Aspect   : ").append(aspectRatio).append("\n")
		.append("Near Z   : ").append(nearZ).append("\n")
		.append("Far Z    : ").append(farZ).append("\n");
		return sb.toString();
	}
}
