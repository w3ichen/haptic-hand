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

public class HeightmapOSN extends Heightmap {

	protected OpenSimplexNoise noise = null;

	protected double fNoiseScale;

	protected double fRds;

	/**
	 * Create a square tileable heightmap using Open Simplex noise. <br>
	 * 
	 * A 2D float array is used to hold the height map values. The amount of RAM 
	 * needed to store the array is 4*size*size bytes so a map size of 1000 would 
	 * require about 4Mb. <br>
	 * 
	 * rad_factors in the range 500 - 1000 (default = 500) and noise_scale values
	 *  in the range 0.002 - 0.008 (default = 0.005)
	 *  
	 * @param size the size of the 2D square array 
	 * @param rad_factor try values 500 - 1000
	 * @param noise_scale try values 0.002 - 0.008
	 */
	public HeightmapOSN(int size, double rad_factor, double noise_scale) {
		super(size);
		this.fNoiseScale = noise_scale;
		this.fRds = rad_factor;
		noise = new OpenSimplexNoise(); // add seed value for final release
		calcHeightmap();
	}

	/**
	 * Create a square tileable heightmap using Open Simplex noise. <br>
	 * 
	 * @param size the size of the 2D square array 
	 */
	public HeightmapOSN(int size) {
		this(size, 200, 0.005);
	}

	@Override
	protected void calcHeightmap() {
		double TAU = 2 * Math.PI;
		double delta =  1.0 / (gridSize - 1);
		for (int row = 0; row < gridSize; row++) {
			double y = row * delta;
			double fRdy = y * TAU;
			double c = fRds*Math.sin(fRdy);
			double d = fRds*Math.cos(fRdy);
			for (int col = 0; col < gridSize; col++) {
				double x = col * delta;
				double fRdx = x * TAU;
				double a = fRds*Math.sin(fRdx);
				double b = fRds*Math.cos(fRdx);
				float n = (float) noise.eval(
						a*fNoiseScale,
						b*fNoiseScale,
						c*fNoiseScale,
						d*fNoiseScale);
				grid[col][row] = n;
				if(n < min_height) min_height = n;
				if(n > max_height) max_height = n;
			}
		}
//		System.out.println(min_height + "   " + max_height);
	}
}
