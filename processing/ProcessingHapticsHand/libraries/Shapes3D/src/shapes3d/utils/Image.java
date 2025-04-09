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

import processing.core.PImage;

/**
 * Small collection of methods to create mirrored or rotated images 
 * from an original image.
 * 
 * In all methods the original is unchanged.
 * 
 * @author Peter Lager
 *
 */
public class Image {

	/**
	 * Using the provided image create a copy that is flipped along 
	 * the vertical axis.
	 * 
	 * @param src the original image
	 * @return the flipped image
	 */
	public static PImage flipV(PImage src) {
		int sh = src.height;
		int sw = src.width;
		int s = sw * sh;
		PImage dest = new PImage(sw, sh);
		src.loadPixels();
		int[] sp = src.pixels, dp = dest.pixels;
		int n = 0;
		for (int r = 0; r < sh; r++) {
			for (int c = 0; c < sw; c++) {
				dp[n++] = sp[ (s - sw) + c - r * sw];
			}
		}
		dest.updatePixels();
		return dest;
	}

	/**
	 * Using the provided image create a copy that is flipped along 
	 * the horizontal axis.
	 * 
	 * @param src the original image
	 * @return the flipped image
	 */
	public static PImage flipH(PImage src) {
		int h = src.height;
		int w = src.width;
		PImage dest = new PImage(w, h);
		src.loadPixels();
		int[] sp = src.pixels, dp = dest.pixels;
		int n = 0;
		for (int r = 0; r < h; r++) {
			for (int c = 0; c < w; c++) {
				dp[n++] = sp[ (w - 1) - c + r * w];
			}
		}
		dest.updatePixels();
		return dest;
	}

	/**
	 * Using the provided image create a copy that is rotated right (counter-clockwise)  
	 * by 90&deg; 
	 * 
	 * @param src the original image
	 * @return the rotated image
	 */
	public static PImage rotateCW(PImage src) {
		int h = src.height;
		int w = src.width;
		PImage dest = new PImage(h, w);
		src.loadPixels();
		int[] sp = src.pixels, dp = dest.pixels;
		int n = 0;
		for (int r = 0; r < w; r++) {
			for (int c = 0; c < h; c++) {
				dp[n++] = sp[ (w - 1) + w * c - r];
			}
		}
		dest.updatePixels();
		return dest;
	}

	/**
	 * Using the provided image create a copy that is rotated left (clockwise)  
	 * by 90&deg; 
	 * 
	 * @param src the original image
	 * @return the rotated image
	 */
	public static PImage rotateCCW(PImage src) {
		int h = src.height;
		int w = src.width;
		int s = w * h;
		PImage dest = new PImage(h, w);
		src.loadPixels();
		int[] sp = src.pixels, dp = dest.pixels;
		int n = 0;
		for (int r = 0; r < w; r++) {
			for (int c = 0; c < h; c++) {
				dp[n++] = sp[ (s - w ) - w * c + r];
			}
		}
		dest.updatePixels();
		return dest;
	}
	
	/**
	 * Private to ensure this class can't be instantiated.
	 */
	private Image() {}
}
