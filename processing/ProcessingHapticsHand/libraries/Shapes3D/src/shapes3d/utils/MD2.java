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

import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map;

import processing.core.PApplet;
import processing.core.PImage;
import processing.core.PVector;

/**
 * This class is used to load MD2 model data and skin texture from files
 * 
 * @author Peter Lager
 *
 */
final public class MD2 {
	// Maps the model filename to its data
	private static Map<String, MD2_Data> md2ModsData = new HashMap<String, MD2_Data>();

	// This is the maximum MD2 file size in bytes that can be converted
	// into a model. It should be big enough for most models, if not
	// make the number bigger!
	public static int MAX_FILE_SIZE = 1000000;

	// Used to hold the file contents while it is being used to 
	// create the model, after the model is created it is dummped.
	private static ByteBuffer buf;

	private static String ident;		// identifies a MD2 file "IDP2"
	private static int version;	 		// mine is 8
	private static int skinwidth;		// width of texture
	private static int skinheight;		// height of texture
	private static int framesize;		// number of bytes per frame
	private static int numSkins;		// number of textures
	private static int numXYZ;			// number of points
	private static int numST;			// number of texture
	private static int numTris;			// number of triangles
	private static int numGLcmds;		// number of gl commands and vetices
	private static int numFrames;		// total number of frames
	private static int offsetSkins;		// offset to skin names (64 bytes each)
	private static int offsetST;		// offset of texture s-t values
	private static int offsetTris;		// offset of triangle mesh
	private static int offsetFrames;	// offset of frame data (points)
	private static int offsetGLcmds;	// type of OpenGL commands to use
	private static int offsetEnd;		// end of file

	/*
	 * Each frame in the file has a name which is used to identify the
	 * different model animation sets.
	 */
	private static String[] frameNames;
	private static MD2_AnimState[] states;

	// All the XYZ points that make up the model
	private static PVector[] points;


	private static PVector modOffset;		// values to subtract to center model
	private static PVector modSize;		// size of model in 3 dimensions

	private static int[] glCommands;		// Type (FAN or STRIP and number of vertices to render
	private static MD2_Vertex[] glVertex;	// vertices to render in FAN or STRIP

	/**
	 * This method load a single MD model from the given files. <br>
	 * The model requires  <br>
	 * 1) the name of the file with the model data <br>
	 * 2) the name of the skin image file <br> 
	 * 
	 * If you use an existing ID previously used you will get the original
	 * model and no attempt will be made to load a new one.
	 * 
	 * @param app a PApplet object need to access Processing methods
	 * @param modelFile a model data filename
	 * @param skinFile an image filename
	 * @return an MD2_Model object
	 */	
	public static MD2_Data getModelData(PApplet app, String modelFile, String skinFile){
			MD2_Data modelData = md2ModsData.get(modelFile);
			if(modelData == null){
				PImage skin = app.loadImage(skinFile);
				byte[] b = new byte[MAX_FILE_SIZE];
				b = app.loadBytes(modelFile);
				buf = ByteBuffer.wrap(b);      
				// BIG_ENDIAN is the default - might be for Java
				// but the file was created with a C++ program
				buf.order(ByteOrder.LITTLE_ENDIAN);
				//buf.order(ByteOrder.BIG_ENDIAN);
				buf.rewind();

				loadHeader();
				getPointList();
				getModelStates();
				getGLcommands();
				// release buffer memory ASAP
				buf = null;
				System.gc();
				// Create the model data
				modelData = new MD2_Data(numFrames, numXYZ, framesize, 
						points, modOffset, modSize, glCommands, glVertex, skin, states);

				md2ModsData.put(modelFile, modelData);
			}
			return modelData;
	}

	/**
	 * Load all MD2 header information even if we don't get to use it
	 */
	private static void loadHeader(){
		ident = readString(4);
		version = buf.getInt();
		skinwidth = buf.getInt();
		skinheight = buf.getInt();
		framesize = buf.getInt();
		numSkins = buf.getInt();
		numXYZ = buf.getInt();
		numST = buf.getInt();        // number of texture
		numTris = buf.getInt();      // number of triangles
		numGLcmds = buf.getInt();
		numFrames = buf.getInt();    // total number of frames
		offsetSkins = buf.getInt();  // offset to skin names (64 bytes each)
		offsetST = buf.getInt();     // offset of texture s-t values
		offsetTris = buf.getInt();   // offset of triangle mesh
		offsetFrames = buf.getInt(); // offset of frame data (points)
		offsetGLcmds = buf.getInt(); // type of OpenGL commands to use
		offsetEnd = buf.getInt();    // end of file
	}

	private static void getPointList(){
		buf.position(offsetFrames);
		points = new PVector[numFrames * numXYZ];
		int index = 0;
		float x,y,z;
		float minX, minY, minZ, maxX, maxY, maxZ;
		minX = minY = minZ = Float.MAX_VALUE;
		maxX = maxY = maxZ = -Float.MAX_VALUE;
		// Not used but must keep
		@SuppressWarnings("unused")
		int normIndex;

		float sx,sy,sz,tx,ty,tz;
		frameNames = new String[numFrames];
		for(int j = 0 ; j < numFrames ; j++){
			buf.position(offsetFrames + framesize * j);
			sx = buf.getFloat();
			sy = buf.getFloat();
			sz = buf.getFloat();
			tx = buf.getFloat();
			ty = buf.getFloat();
			tz = buf.getFloat();
			frameNames[j] = readString(16);
			for(int i = 0; i < numXYZ; i++){
				x = sx * getUByte() + tx;
				y = sy * getUByte() + ty;
				z = sz * getUByte() + tz;
				if(x < minX) minX = x;
				if(y < minY) minY = y;
				if(z < minZ) minZ = z;
				if(x > maxX) maxX = x;
				if(y > maxY) maxY = y;
				if(z > maxZ) maxZ = z;
				normIndex = buf.get(); // not used in this program but do NOT remove
				points[index] = new PVector(x, y, z);
				index++;	
			}
		}
		modOffset = new PVector((minX + maxX)/2, (minY + maxY)/2, (minZ + maxZ)/2);
		modSize = new PVector(maxX-minX, maxY-minY, maxZ-minZ);
	}

	/**
	 * 	 * Get the next 2 bytes from the buffer and interpret as
	 * 	 * a signed integer (twos complement) 
	 * 	 * @return
	 */
	@SuppressWarnings("unused")
	private static int getShort(){
		int ch = buf.getChar();
		ch = (ch > 32767) ? 65536 - ch : ch;
		return ch;
	}

	/**
	 * 	 * Get the next 2 bytes from the buffer and interpret as
	 * 	 * an unsigned integer 
	 * 	 * @return
	 */
	@SuppressWarnings("unused")
	private static int getUShort(){
		int ch = buf.getChar();
		ch = (ch > 32767) ? -(65536 - ch) : ch;
		return ch;
	}

	/**
	 * 	 * Get the next byte from the buffer and interpret as
	 * 	 * an unsigned integer (0 - 255)
	 * 	 * @return
	 */
	private static int getUByte(){
		int ch = buf.get();
		ch = (ch < 0) ? ch + 256 : ch;
		return ch;
	}

	/**
	 * Extract a string from the buffer until a zero byte or
	 * nbytes have been read.
	 * The buffer pointer is advanced by nbytes irrespective of 
	 * string length.
	 *  
	 * @param nbytes
	 * @return
	 */
	private static String readString(int nbytes){
		return readString(nbytes, '\0');
	}

	/**
	 * Extract a string from the buffer until the stopAt character
	 * is reached (string does not include stopAt char) or until
	 * nbytes have been read.
	 * The buffer pointer is advanced by nbytes irrespective of 
	 * string length.
	 *
	 * @param nbytes
	 * @return
	 */
	private static String readString(int nbytes, char stopAt){
		int nextPos = buf.position() + nbytes;
		char ch;
		StringBuilder s = new StringBuilder("");
		for(int i = 0; i < nbytes; i++){
			ch = (char)buf.get();
			if(ch != stopAt)
				s.append(ch);
			else
				break;
		}
		buf.position(nextPos);
		return new String(s);
	}

	/**
	 * Create a list of model states based on frame names with any
	 * trailing digits removed e.g. crouch001, crouch002 both become 
	 * crouch.
	 */
	private static void getModelStates(){
		LinkedList<MD2_AnimState> list = new LinkedList<MD2_AnimState>();
		String nextFrameName;

		// Load first state so we have something to compare when
		// we loop through rest of frames
		String thisFrameName = stripTrailingNumber(frameNames[0]);
		MD2_AnimState state = new MD2_AnimState(thisFrameName,0,0);

		for(int i = 1; i < numFrames; i++){
			nextFrameName = stripTrailingNumber(frameNames[i]);
			if(state.name.equals(nextFrameName)){
				state.endFrame = i;
			}
			else {
				list.add(state);
				state = new MD2_AnimState(nextFrameName, i,i);
			}
		}
		list.add(state);
		// Convert linked list to an array of correct size
		states = list.toArray(new MD2_AnimState[list.size()]);
	}

	/**
	 * Remove trailing numbers from a string used to get state names
	 * @param s
	 * @return
	 */
	private static String stripTrailingNumber(String s){
		String result = "";
		if( s != null && s.length() > 0){
			int len = s.length();
			char[] c = new char[len]; 
			s.getChars(0, len, c, 0);
			int pos = len -1;
			while(pos > 0 && c[pos] >= '0' && c[pos] <= '9')
				pos--;
			if(pos > 0)
				result = s.substring(0,pos+1);
		}
		return result;
	}

	/**
	 * 	 * Get the OpenGL commands to be used (GL_TRIANGLE_STRIP or 
	 * 	 * GL_TRIANGLE_FAN) and the vertices (index to points array
	 * 	 * and texture coordinates)
	 */
	public static void getGLcommands(){
		buf.position(offsetGLcmds);
		int cmd;
		float s,t;
		int idx;
		LinkedList<Integer> cmds = new LinkedList<Integer>();
		LinkedList<MD2_Vertex> verts = new LinkedList<MD2_Vertex>();
		MD2_Vertex v;

		while(buf.position() < offsetEnd){
			// get GL command type and num vertices
			cmd = buf.getInt();
			cmds.addLast(cmd);
			if(cmd < 0)	cmd = -cmd;

			for(int n = 0; n < cmd; n++){
				s = buf.getFloat();
				t = buf.getFloat();
				idx = buf.getInt();
				v = new MD2_Vertex(s,t,idx);
				verts.addLast(v);
			}
		}
		/* 
		 * Convert LinkedList<Integer> to int array of the correct size
		 * This will unbox the integers just once so should make the
		 * rendering quicker.
		 */
		glCommands = new int[cmds.size()];
		Iterator<Integer> iter = cmds.iterator();
		int pos = 0;
		while(iter.hasNext()){
			glCommands[pos] = iter.next();
			pos++;
		}
		/*
		 * convert LinkedList<Vertex> to Vertex array of correct size.
		 * Faster to traverse array than list when we come to render
		 */
		glVertex = verts.toArray(new MD2_Vertex[verts.size()]);
	}

	/**
	 * The remaining methods in this class were used to confirm that
	 * the MD2 file was read correctly and are not needed in the
	 * distribution version
	 */
	public static void displayGLcommands(){
		int cmd;
		int vpos = 0;

		for(int i = 0; i < glCommands.length; i++){
			cmd = glCommands[i];
			if(cmd < 0){
				cmd = -cmd;
				System.out.println("GL_TRIANGLE_FAN    ( " + cmd + " vertices )");
			}
			else if(cmd > 0) {
				System.out.println("GL_TRIANGLE_STRIP  ( " + cmd + " vertices )");
			}
			for(int j = 0; j < cmd; j++){
				System.out.println(glVertex[vpos++]);
			}
		}
		System.out.println("Number of fans & strips " + glCommands.length);
		System.out.println("Number of verts to process " + glVertex.length);
	}


	public static void displayModelStates(){
		for(int i =0; i < states.length; i++){
			System.out.println(i + "\t" + states[i]);
		}
	}

	public static void displayFrameNames(){
		for(int i = 0 ; i < frameNames.length; i++){
			System.out.println(i + "\t"+ stripTrailingNumber(frameNames[i]));
		}
	}

	public static void displayHeader(){
		System.out.println("Ident " + ident+ " ");		 // identifies as MD2 file "IDP2"
		System.out.println("Version " + version + " ");	 // mine is 8
		System.out.println("Skin size " + skinwidth + " x " + skinheight);    // width of texture
		System.out.println("Frame size " + framesize + " bytes");    // number of bytes per frame
		System.out.println("Number of skins " + numSkins + " listed");     // number of textures
		System.out.println("Number of vertices " + numXYZ + " per frame");       // number of pos
		System.out.println("Number of textute coords " + numST + " ");        // number of texture
		System.out.println("Number of triangles " + numTris + " ");      // number of triangles
		System.out.println("Number of GL commands " + numGLcmds + " ");
		System.out.println("Number of frames " + numFrames + " ");    // total number of frames
		System.out.println(">> Offset to skins       " + offsetSkins+ " ");  // offset to skin names (64 bytes each)
		System.out.println(">> Offset to tex coords  " + offsetST + " ");     // offset of texture s-t values
		System.out.println(">> Offset to triangles   " + offsetTris + " ");   // offset of triangle mesh
		System.out.println(">> Offset to frame data  " + offsetFrames + " "); // offset of frame data (pos)
		System.out.println(">> Offset to GL commands " + offsetGLcmds + " "); // type of OpenGL commands to use
		System.out.println(">> Offset end of file    " + offsetEnd + " ");    // end of file
	}
}
