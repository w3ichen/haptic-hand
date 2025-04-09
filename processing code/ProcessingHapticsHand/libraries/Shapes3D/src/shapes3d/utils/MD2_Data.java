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
import processing.core.PVector;

/**
 * This class is a simple structure to store MD2 data loaded from a file using
 * the MD2 class. <br>
 * This data would then be used to create the actual 3D model (MD2_Model class) 
 * to be used in your program. <br>
 * NOTE: this structure can be safely shared by multiple models.
 * 
 * @author Peter Lager
 *
 */
public class MD2_Data {
	
	public int numFrames;				// number of frames
	public int numXYZ;					// number of vertices
	public PVector[] point;				// vertex list

	public PVector modOffset;			// values to subtract to center model
	public PVector modSize;				// size of model in 3 dimensions

	public int[] glComannd;				// Type (FAN or STRIP and number of vertices to render
	public MD2_Vertex[] glVertex;		// vertices to render in FAN or STRIP

	public MD2_AnimState[] anim_state; 	// Array of different model states

	public PImage skin;
	
	public MD2_Data(){	}

	public MD2_Data(int numFrames, int numXYZ, int framesize,
			PVector[] points, PVector modOffset, PVector modSize,
			int[] glCommand, MD2_Vertex[] glVertex, PImage skin,
			MD2_AnimState[] state) {
		this.numFrames = numFrames;
		this.numXYZ = numXYZ;
		this.point = points;
		this.modOffset = modOffset;
		this.modSize = modSize;
		this.glComannd = glCommand;
		this.glVertex = glVertex;
		this.skin = skin;
		this.anim_state = state;
	}
	
	/**
	 * Centers the model so it evenly spaced over (0,0,0)
	 * Note: this will change all the XYZ points in the model
	 */
	public void centreModel(){
		centreModel(modOffset);
	}

	/**
	 * Centers the model so it evenly spaced over a given offset
	 * useful if we have 2 linked models.
	 * Note: this will change all the XYZ points in the model
	 * @param offset the distance to move vertices
	 */
	public void centreModel(PVector offset){
		for(int i = 0; i < point.length; i++)
			point[i].sub(offset);
		modOffset = new PVector();
	}
	
	/**
	 * Scales the model
	 * Note: this will change all the XYZ points in the model
	 * @param scale the scale factor to apply to vertices
	 */
	public void scaleModel(float scale){
		for(int i = 0; i < point.length; i++)
			point[i].mult(scale);
		modSize.mult(scale);
	}
	
	/**
	 * Orients the model.
	 * @param orientation
	 */
	public void orientModel(Orientation orientation) {
		float minX, minY, minZ, maxX, maxY, maxZ;
		minX = minY = minZ = Float.MAX_VALUE;
		maxX = maxY = maxZ = -Float.MAX_VALUE;
		for(int i = 0; i < point.length; i++) {
			point[i] = orientation.applyTRto(point[i]);
			float x = point[i].x;
			float y = point[i].y;
			float z = point[i].z;
			if(x < minX) minX = x;
			if(y < minY) minY = y;
			if(z < minZ) minZ = z;
			if(x > maxX) maxX = x;
			if(y > maxY) maxY = y;
			if(z > maxZ) maxZ = z;			
		}
		modOffset.set((minX + maxX)/2, (minY + maxY)/2, (minZ + maxZ)/2);
		modSize.set(maxX-minX, maxY-minY, maxZ-minZ);
	}
	
	/**
	 * Display the model statistics and memory usage
	 */
	public String toString(){
		StringBuilder s = new StringBuilder("");
		s.append("\nMD2 Model details")
		.append("\tThere are " + numFrames + " key framess\n")
		.append("\tThere are "+ point.length + " points (XYZ coordinates)\n")
		.append("\tFor rendering there are " + glComannd.length + " triangle strips/fans\n")
		.append("\t and these have " + glVertex.length + " vertex definitions\n")
		.append("\tThere are " + anim_state.length + " animation sequences\n")
		.append("\tSize:    " + modSize + "\n")
		.append("\tOffset:   " + modOffset + "\n");
		return s.toString();
	}

}
