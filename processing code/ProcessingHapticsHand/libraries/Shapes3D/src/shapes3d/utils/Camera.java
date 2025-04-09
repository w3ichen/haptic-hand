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

import processing.core.PConstants;
import processing.core.PGraphics;
import processing.core.PVector;

/**
 * Base class for all cameras.
 * 
 * @author Peter Lager
 *
 * @param <T> Camera or class that extends Camera
 */
public abstract class Camera <T extends Camera<T>> implements PConstants {

	protected Perspective perspective = null;;

	protected PVector pos = new PVector();

	protected PVector up = new PVector(0,1,0);

	// Direction the camera is facing relative to its current position
	protected PVector lookat = new PVector(0,0,1); // keep normalized

	// The direction the camera wants to move
	protected PVector target = new PVector(0,0,1); // keep normalized

	// The direction the camera is moving
	protected PVector velocity = new PVector();

	public Camera() {}

	public abstract T getThis();

	/**
	 * Move the camera based on its velocity.
	 * 
	 * @param deltaTime the elapsed time (s)
	 */
	public void update(float deltaTime) {
		// Update velocity so it slerps towards the target
//		float a = PVector.angleBetween(velocity.copy().normalize(), target);
//		if(a > 0.0175f) {
//			velocity = Util.slerp(velocity, target, (PI - a)/ PI, velocity.mag());
//		}
//		else if(a > 0) {
//			velocity.set(PVector.mult(target, velocity.mag()));
//		}
		// Now set
		pos.set(
				pos.x + velocity.x * deltaTime,
				pos.y + velocity.y * deltaTime,
				pos.z + velocity.z * deltaTime);
		if(velocity.magSq() > 0){
			lookat.set(velocity);
			lookat.normalize();	
		}
	}

	/**
	 * Apply any perspective used by this camera to the specified graphics context.
	 * 
	 * @param pg the graphics to apply perspective to
	 * @return this camera
	 */
	public T apply(PGraphics pg) {
		if(perspective != null) {
			perspective.apply(pg);
		}
		pg.camera(pos.x, pos.y, pos.z, pos.x + lookat.x, pos.y + lookat.y, pos.z + lookat.z, up.x, up.y, up.z);
		return getThis();
	}

	/**
	 * Set the perspective to be used by this camera.
	 * 
	 * @param p the perspective for this camera
	 * @return
	 */
	public T perspective(Perspective p) {
		this.perspective = p;
		return getThis();
	}

	public Perspective perspective() {
		return perspective;
	}

	public PVector pos() {
		return pos.copy();
	}

	public T pos(PVector pos) {
		this.pos.set(pos);
		return getThis();
	}

	public PVector up() {
		return up.copy();
	}

	public T up(PVector up) {
		this.up.set(up);
		return getThis();
	}

	public PVector lookat() {
		return lookat.copy();
	}

	public T lookat(PVector lookat) {
		this.lookat.set(lookat);
		return getThis();
	}

	public PVector heading() {
		return target.copy();
	}

	public T heading(PVector heading) {
		this.target.set(heading).normalize();
		return getThis();
	}

	public PVector velocity() {
		return velocity.copy();
	}

	public T velocity(PVector velocity) {
		this.velocity.set(velocity);
		return getThis();
	}

	public float speed() {
		return velocity.mag();
	}

	public T speed(float speed) {
		velocity.normalize().mult(speed);
		return getThis();
	}
}
