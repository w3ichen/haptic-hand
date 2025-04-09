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
import processing.core.PImage;

public abstract class Heightmap implements PConstants {

	protected float[][] grid;
	protected int gridSize;
	
	protected float min_height = Float.MAX_VALUE;
	protected float max_height = Float.MIN_VALUE;

	public Heightmap(int size) {
		gridSize = size;
		grid = new float[gridSize][gridSize];
	}
	
	abstract protected void calcHeightmap();
	
	public PImage getMapImage(PApplet app) {
		PImage img = app.createImage(gridSize, gridSize, RGB);
		img.loadPixels();
		float factor = 256 / (max_height - min_height);
		int p = 0;
		for (int y = 0; y < gridSize; y++) {
			for (int x = 0; x < gridSize; x++) {
				int v = (int) ( factor * ( grid[x][y] - min_height));
				img.pixels[p++] = 0xFF000000 | (v << 16) | (v << 8) | v;
			}
		}
		img.updatePixels();
		return img;
	}
	
	public float[][] grid() {
		return grid;
	}

	public int gridSize() {
		return gridSize;
	}

	public float minHeight() {
		return min_height;
	}

	public float maxHeight() {
		return max_height;
	}

	public void adjustHeights(float low, float high) {
		for(int z = 0; z < gridSize; z++) {
			for(int x = 0; x < gridSize; x++) {
				grid[z][x] = PApplet.map(grid[z][x], min_height, max_height, low, high);
			}
		}
		 min_height = low;
		 max_height = high;
	}
	
	public void printMap() {
		for(int z = 0; z < grid.length; z++) {
			for(int x = 0; x < grid[z].length; x++) {
				System.out.print("["+ grid[z][x] + "]\t");
			}
			System.out.println();
		}
		System.out.println("Min: " + min_height);
		System.out.println("Msx: " + max_height);
		System.out.println();
	}

}
