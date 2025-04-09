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

import shapes3d.Shape3D;
import shapes3d.Terrain;

/**
 * This camera can be used with the Terrain and Box classes to producea 
 * FP view.
 * 
 * @author Peter Lager
 *
 */
public class TerrainCamera extends Camera<TerrainCamera> {

	protected Terrain terrain = null;
	protected float worldSize = 0;
	protected Shape3D skyBox = null;
	
	protected float hoverHeight = 10;
	
	protected boolean hugTerrain = true;

	/**
	 * Create a Terrain camera for a predefined Terrain and SkyBox
	 * @param terrain the terrain to be viewed with this camera
	 * @param sky_scene the skybox to surround this camera
	 */
	public TerrainCamera(Terrain terrain, Shape3D sky_scene) {
		super();
		this.terrain = terrain;
		worldSize = this.terrain.worldSize();
		this.skyBox = sky_scene;
	}
	
	/**
	 * Call the parent method to move the camera based on its velocity. <br>
	 * This this update will modify the camera height based on the 
	 * terrain height.
	 * 
	 * @param deltaTime the elapsed time (s)
	 */
	public void update(float deltaTime) {
		// Update XZ position on terrain
		super.update(deltaTime);
		// Make sure the camera position is over the terrain
		while(pos.x < 0) { pos.x += worldSize; }
		while(pos.z < 0) { pos.z += worldSize; }
		pos.x %= worldSize;
		pos.z %= worldSize;
		// Tell the terrain where to render from
		terrain.worldPosition(pos.x, pos.z);
		pos.y = hugTerrain ? terrain.height(pos.x, pos.z) + hoverHeight : hoverHeight;
		skyBox.moveTo(pos.x, 0, pos.z);
	}
	
	@Override
	public TerrainCamera getThis() {
		return this;
	}

	public TerrainCamera hoverHeight(float hh) {
		this.hoverHeight = hh;
		return getThis();
	}
	
	public float hoverHeight() {
		return hoverHeight;
	}
	
	
}
