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

import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.LinkedHashSet;
import java.util.Map;

import processing.core.PApplet;
import processing.core.PImage;
import processing.video.Movie;
import shapes3d._ShapePart;

/**
 * This class is used to load bitmap files and create images. <br>
 * 
 * Although there maybe multiple requests for a particular bitmap file only
 * one PImage is created for each file.
 * 
 * @author Peter Lager
 *
 */
public final class Textures {

	private static Map<String, PImage> textures = null; //new HashMap<String, PImage>();

	private static Map<Movie, LinkedHashSet<_ShapePart>> movies = new LinkedHashMap<Movie, LinkedHashSet<_ShapePart>>();

	private static Textures instance = null;
	private static PApplet app = null;


	/**
	 * Add a movie that is going to be used as a texture.
	 * 
	 * @param pApplet the underly PApplet
	 * @param movie the movie to add
	 * @param shapePart the part to be textured with this movie
	 */
	public static void addMovie(PApplet pApplet, PImage movie, _ShapePart shapePart) {
		// If this is the first movie then start initialise
		// movie updater
		if(instance == null) {
			app = pApplet;
			movies = new LinkedHashMap<Movie, LinkedHashSet<_ShapePart>>();
			instance = new Textures(app);
		}
		LinkedHashSet<_ShapePart> parts = movies.get(movie);
		if(parts == null) {
			// Create new movie entry
			parts = new LinkedHashSet<_ShapePart>();
			parts.add(shapePart);
			movies.put((Movie)movie, parts);
		}
		else {
			// Add to existing movie entry
			parts.add(shapePart);
		}	
	}

	/**
	 * This method is called when the movie-texture for a shape part is
	 * being replaced by another movie or an image.
	 * 
	 * @param movie the current movie-texture
	 * @param shapePart the associated shape part
	 */
	public static void removeMovie(Movie movie, _ShapePart shapePart) {
		LinkedHashSet<_ShapePart> parts = movies.get(movie);
		if(parts == null) {
			// This should not be possible!
			System.out.println("Attempted to remove non-existant movie");
			return;
		}
		// Remove shape part
		parts.remove(shapePart);
		if(parts.isEmpty()) {
			// If this movie is no longer used remove it
			System.out.println("Removing shape part from movie movie");
			movies.remove(movie);
		}
		if(movies.isEmpty()) {
			System.out.println("No movies left");
			app.unregisterMethod("pre",  instance);
			instance = null;
		}
	}

	/**
	 * Load an bitmap file return a reference to the PImage created.
	 * 
	 * @param app the PApplet to be used to load the image
	 * @param filename the image filename
	 * @return null if the file does not exist else the PImage object
	 */
	public static PImage loadImage(PApplet app, String filename){
		if(textures == null) {
			textures = new HashMap<String, PImage>();
		}
		if(textures.containsKey(filename)){
			return textures.get(filename);
		}
		PImage image = app.loadImage(filename);
		if(image != null){
			textures.put(filename, image);
		}
		else
			PApplet.println("Unable to load image from file '" + filename+"'");
		return image;
	}

	/**
	 * Load images from multiple files
	 * @param app the PApplet to be used to load the image
	 * @param filename an array of filenames
	 * @return an array of images
	 */
	public static PImage[] loadImage(PApplet app, String[] filename){
		if(textures == null) {
			textures = new HashMap<String, PImage>();
		}
		PImage[] images = new PImage[filename.length];
		for(int i = 0; i < images.length; i++)
			images[i] = loadImage(app, filename[i]);
		return images;
	}

	/**
	 * Make multiple images from a given image.
	 * 
	 * @param app  the PApplet to be used to create the image tiles
	 * @param img the tiled image
	 * @param nCols number of tiles across
	 * @param nRows number of tiles down
	 * @return an array of images (tiles)
	 */
	public static PImage[][] makeTiles(PApplet app, PImage img, int nCols, int nRows){
		PImage[][] imageTiles = new PImage[nCols][nRows];
		int tileW = img.width / nCols;
		int tileH = img.height / nRows;
		for(int y = 0; y < nRows; y++){
			for(int x = 0; x < nCols; x++){
				imageTiles[x][y] = app.createImage(tileW, tileH, PApplet.ARGB);
				imageTiles[x][y].copy(img, x * tileW, y * tileH, tileW, tileH, 0, 0, tileW, tileH);
			}
		}
		return imageTiles;
	}

	/**
	 * Will print a list of movies and the shape parts using them. Useful when debugging
	 * library code.
	 */
	public static void printMovieUsage() {
		// Iterate through movies and update textures
		System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++");
		for (Map.Entry<Movie, LinkedHashSet<_ShapePart>> entry : movies.entrySet()) {
			Movie m = entry.getKey();
			LinkedHashSet<_ShapePart> p = entry.getValue();
			System.out.println("MOVIE   " + m.toString());
			if(m.available()) {
				m.read();
				for(_ShapePart sp : p) {
					System.out.println("   SHAPE PART   " + sp);
				}
			}
			System.out.println("++++++++++++++++++++++++++++++++++++++++++++++++++");
		}		
	}
	
	// ###############################################################################
	// Create an instance of Textures and register the pre() method so that
	// movies are updated and the latest frame is used as a texture.
	// ###############################################################################
	private Textures(PApplet pApplet) {
		app.registerMethod("pre", this);
	}

	public void pre() {
		// Iterate through movies and get available frames
		for (Map.Entry<Movie, LinkedHashSet<_ShapePart>> entry : movies.entrySet()) {
			Movie m = entry.getKey();
			if(m.available()) {
				m.read();
			}
		}
	}


}
