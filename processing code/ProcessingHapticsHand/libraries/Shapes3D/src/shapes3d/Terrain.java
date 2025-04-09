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

import java.util.ArrayList;
import java.util.List;

import processing.core.PGraphics;
import processing.core.PVector;
import shapes3d.utils.Camera;
import shapes3d.utils.Heightmap;
import shapes3d.utils.UV;

/**
 * 
 * @author Peter Lager
 *
 */
public class Terrain extends Shape3D {

	private List<Shape3D> shapes = new ArrayList<Shape3D>();

	// The size of the terrain in 'real world' units
	private float worldSize;
	// The number of elements in each dimension of
	// the map array i.e. length
	private int mapSize;
	// the width of a map element in world dimensions
	private float mapScale;
	// This will not be needed once the terrain has been created
	private Heightmap hm;

	// Decides where and how much of the terrain to render
	private float worldX, worldZ, worldHorizon;

	private Camera<?> cam = null;
	
	// We keep a reference to the coordinate array so we can calculate the 
	// height at any point on the terrain 
	private PVector[][] coord;
	private PVector[][] normals;
	// We will release the reference to the texture coordinate array because
	// the rendering is done in the _TerrainMesh2D shape part
	private UV[][] uv01;

	public Terrain(Heightmap hm, float worldSize) {
		super();
		this.hm = hm;
		this.worldSize = worldSize;
		worldX = 0;
		worldZ = 0;
		worldHorizon = worldSize / 4;
		// Get map details
		mapSize = hm.gridSize();
		mapScale = this.worldSize / (mapSize - 1);
		calcShape();
		makeParts();
	}

	public Terrain getThis() {
		return this;
	}

	public void addShape(Shape3D shape) {
		shapes.add(shape);
	}

	/**
	 * 
	 */
	@Override
	public void draw(PGraphics pg) {
		draw(pg, worldX, worldZ, worldHorizon, null);
	}

	/**
	 * 
	 * @param pg the canvas
	 * @param lookAt the direction we are looking (normalised vector)
	 */
	public void draw(PGraphics pg, final Camera<?> cam) {
		draw(pg, worldX, worldZ, worldHorizon, cam);
	}

	/**
	 * Draw the terrain centered about px, py as far as view_distance
	 * @param pg the canvas
	 * @param px real world position on the terrain
	 * @param pz real world position on the terrain
	 * @param view_distance real world view distance
	 */
	public void draw(PGraphics pg, float px, float pz, float view_distance, Camera<?> cam) {
		// System.out.println("Terrain : " + "draw(PGraphics pg, float px, float pz, float vd)");
		this.cam = cam;
		on_canvas = pg;
		on_canvas_matrix = pg.getMatrix().get();
		pg.pushStyle();
		for(int ns = -1; ns <=1; ns++) {
			float nz = pz - ns * worldSize;
			for(int ew = -1; ew <=1; ew++) {
				float nx = px - ew * worldSize;
				float[] bounds = calcBounds(nx - view_distance, nz - view_distance, nx + view_distance, nz + view_distance);
				if(bounds.length > 0) { 
					int left = (int) (bounds[0] / mapScale);
					int top = (int) (bounds[1] / mapScale);
					int right = (int) (bounds[2] / mapScale);
					int bot = (int) (bounds[3] / mapScale);
					if(left < right && top < bot) {
						pg.pushMatrix();
						pg.translate(pos.x + ew * worldSize, pos.y, pos.z + ns * worldSize);
						pg.rotateX(rot.x);
						pg.rotateY(rot.y);
						pg.rotateZ(rot.z);
						pg.scale(shapeScale);
						((_TerrainMesh2D) shapeParts[0]).draw(pg, left, top, right, bot);
						// Is there a shape to draw in this region
						for(Shape3D shape : shapes) {
							float sx = shape.x() + ew * worldSize;
							float sz = shape.z() + ns * worldSize;
							if(Math.abs(px - sx) <= view_distance && Math.abs(pz - sz) <= view_distance) {
								if(cam == null) {
									shape.draw(pg);
								}
								else {
									// Get direction to this shape and normalise it
									PVector dir = new PVector(sx - nx, 0, sz - nz);
									dir.normalize();
									// Get lookat vector (always normalised)
									PVector lookat = cam.lookat();
									// calculate the dot product
									float dot = dir.x * lookat.x + dir.z * lookat.z;
									if(dot >= cam.perspective().fovLimit()) {
										shape.draw(pg);
									}
								}
							}
						}
						pg.popMatrix();
					}
				}
			}
		}
		pg.popStyle();
	}

	@Override
	public void drawPickBuffer(PGraphics pg) {
		drawPickBuffer(pg, worldX, worldZ, worldHorizon);
	}

	public void drawPickBuffer(PGraphics pg, float px, float pz, float view_distance) {
		int in_range = 0, in_view = 0;
		// System.out.println("Terrain : " + "drawPickBuffer(PGraphics pg, float px, float pz, float vd)");
		pg.setMatrix(on_canvas_matrix);
		pg.pushStyle();
		for(int ns = -1; ns <=1; ns++) {
			for(int ew = -1; ew <=1; ew++) {
				float nx = px - ew * worldSize;
				float nz = pz - ns * worldSize;
				float[] bounds = calcBounds(nx - view_distance, nz - view_distance, nx + view_distance, nz + view_distance);
				if(bounds.length > 0) { 
					int left = (int) (bounds[0] / mapScale);
					int top = (int) (bounds[1] / mapScale);
					int right = (int) (bounds[2] / mapScale);
					int bot = (int) (bounds[3] / mapScale);
					if(left < right && top < bot) {
						pg.pushMatrix();
						//pg.setMatrix(on_canvas_matrix);
						pg.noStroke();
						pg.translate(pos.x + ew * worldSize, pos.y, pos.z + ns * worldSize);
						pg.rotateX(rot.x);
						pg.rotateY(rot.y);
						pg.rotateZ(rot.z);
						pg.scale(shapeScale);
						((_TerrainMesh2D) shapeParts[0]).drawPickBuffer(pg, left, top, right, bot);
						// Is there a shape to draw in this region
						for(Shape3D shape : shapes) {
							float sx = shape.x() + ew * worldSize;
							float sz = shape.z() + ns * worldSize;
							if(Math.abs(px - sx) <= view_distance && Math.abs(pz - sz) <= view_distance) {
								in_range++;
								if(cam == null) {
									shape.drawPickBuffer(pg);
								}
								else {
									// Get direction to this shape and normalise it
									PVector dir = new PVector(sx - nx, 0, sz - nz);
									dir.normalize();
									// Get lookat vector (always normalised)
									PVector lookat = cam.lookat();
									// calculate the dot product
									float dot = dir.x * lookat.x + dir.z * lookat.z;
									if(dot >= cam.perspective().fovLimit()) {
										in_view++;
										shape.drawPickBuffer(pg);
									}
								}
							}
						}
						pg.popMatrix();
					}
				}
			}
		}
		System.out.println("In range: " + in_range + "\t\tInview: " + in_view);
		pg.popStyle();
	}

	/**
	 * If you use this method to enable modifications to the map then you do
	 * so at your own risk
	 * @return the terrain map with the {x,y,z] coordinates
	 */
	public PVector[][] map(){
		return coord;
	}

	/**
	 * @return the worldHorizon
	 */
	public float worldHorizon() {
		return worldHorizon;
	}

	/**
	 * The world horizon controls how much of the terrain is rendered at any one time.
	 * @param worldHorizon the worldHorizon to set
	 * @return this shape
	 */
	public Terrain worldHorizon(float worldHorizon) {
		this.worldHorizon = worldHorizon;
		return getThis();
	}

	/**
	 * @return the worldX
	 */
	public float worldX() {
		return worldX;
	}

	/**
	 * @return the worldZ
	 */
	public float worldZ() {
		return worldZ;
	}

	/**
	 * Specify the center of the terrain rendering. This will usually be called from
	 * a camera which ensures [x, z] is over the terrain, otherwise the user is 
	 * responsible for doing this.
	 * 
	 * @param x x position
	 * @param z z position
	 * @return this shape
	 */
	public Terrain worldPosition(float x, float z) {
		worldX = x;
		worldZ = z;
		return getThis();
	}

	public Terrain worldPosition(PVector pos) {
		worldPosition(pos.x, pos.y);
		return getThis();
	}

	/**
	 * @return the worldSize
	 */
	public float worldSize() {
		return worldSize;
	}

	/**
	 * @return the mapSize
	 */
	public int mapSize() {
		return mapSize;
	}

	/**
	 * @return the mapScale
	 */
	public float mapScale() {
		return mapScale;
	}

	/**
	 * Retrieve the terrain height for any position  on the terrain
	 * @param x any valid X position coordinate
	 * @param z any valid Z position coordinate
	 * @return the terrain height at [x, z]
	 */
	public float height(float x, float z) {
		float px = x / mapScale;
		float pz = z / mapScale;

		int col0 = (int) px;
		int row0 = (int) pz;
		int col1 = (col0 + 1) % mapSize;
		int row1 = (row0 + 1) % mapSize;

		// calculate the position px,pz relative to the cell
		// tx & tz are in range >=0 and <= 1
		float tx = px - col0;
		float tz = pz - row0;
		float txtz = tx * tz;

		float h00 = coord[col0][row0].y;
		float h01 = coord[col0][row1].y;
		float h10 = coord[col1][row0].y;
		float h11 = coord[col1][row1].y;

		// Depending on which triangle pX, pZ is in correct the height
		// at the 'opposite' corner to make a flat square before
		// bilinear interpolation
		if (tz < 1 - tx)
			h11 = h00 + 2*((h10 + h01)/2 - h00);
		else
			h00 = h11 + 2*((h10 + h01)/2 - h11);

		// the final step is to perform a bilinear interpolation
		// to compute the height of the terrain directly below
		// the object.
		float height = h00 * (1.0f - tz - tx + txtz)
				+ h10 * (tx - txtz)
				+ h11 * txtz
				+ h01 * (tz - txtz);
		return height;
	}

	@Override
	protected void calcShape() {
		float deltaUV = 1.0f / (mapSize - 1);
		// Create map and texture coordinate arrays the 
		// same size as the heightmap
		PVector[][] c = new PVector[mapSize][mapSize];
		PVector[][] n = new PVector[mapSize][mapSize];
		uv01 = new UV[mapSize][mapSize];
		float[][] grid = hm.grid();
		for(int z = 0; z < mapSize; z++) {
			float mapZ = z * mapScale;
			float uvZ = z * deltaUV;
			for(int x = 0; x < mapSize; x++) {
				c[x][z] = new PVector(x * mapScale, grid[x][z], mapZ);
				uv01[x][z] = new UV(x * deltaUV, uvZ);
			}
		}
		// Calculate normals
		for(int row = 0; row < mapSize; row++) {
			int row_next = row < mapSize - 1 ? row + 1 : 1;
			for(int col = 0; col < mapSize; col++) {
				int col_next = col < mapSize - 1 ? col + 1 : 1;
				PVector v0 = PVector.sub(c[col_next][row], c[col][row] );
				PVector v1 = PVector.sub(c[col][row], c[col][row_next] );
				n[col][row] = PVector.cross(v0, v1, null);
				if(n[col][row].y < 0) {
					n[col][row].mult(-1);
				}
				n[col][row].normalize();
			}
		}
		coord = c;
		normals = n;
	}

	@Override
	protected void makeParts() {
		shapeParts = new _ShapePart[1];
		shapeParts[0] = new _TerrainMesh2D(pickColor + 0, coord, normals, uv01);
		shapeParts[0].tag = "Terrain map";
	}

	@Override
	protected void releaseMemory() {
		// Do not null coord need this to have access to terrain coordinates
		normals = null;
		uv01 = null;
		hm = null;
	}

	public void print() {
		for(int z = 0; z < mapSize; z++) {
			for(int x = 0; x < mapSize; x++) {
				System.out.print(coord[x][z]);
			}
			System.out.println();
		}
		System.out.println("---------------------------------------------------------------------");
	}

	/**
	 * If two boxes overlap then the overlap region is another box. This method is used to 
	 * calculate the coordinates of the overlap. <br>
	 * The boxes are represented by the top-left and bottom-right corner coordinates. 
	 * If the returned array has a length:
	 * 0 then they do not overlap <br>
	 * 4 then these are the coordinates of the top-left and bottom-right corners of the overlap region.
	 *  
	 * @param bx0 top-left corner of rectangle B
	 * @param by0 top-left corner of rectangle B
	 * @param bx1 bottom-right corner of rectangle B
	 * @param by1 bottom-right corner of rectangle B
	 * @return an array with the overlap box coordinates (if any)
	 */
	protected float[] calcBounds(float bx0, float by0, float bx1, float by1){
		float topA = 0;
		float botA = worldSize;
		float leftA = 0;
		float rightA = worldSize;
		float topB = Math.min(by0, by1);
		float botB = Math.max(by0, by1);
		float leftB = Math.min(bx0, bx1);
		float rightB = Math.max(bx0, bx1);

		if(botA <= topB  || botB <= topA || rightA <= leftB || rightB <= leftA)
			return new float[0];

		float leftO = (leftA < leftB) ? leftB : leftA;
		float rightO = (rightA > rightB) ? rightB : rightA;
		float botO = (botA > botB) ? botB : botA;
		float topO = (topA < topB) ? topB : topA;
		return  new float[] {leftO, topO, rightO, botO};
	}



}
