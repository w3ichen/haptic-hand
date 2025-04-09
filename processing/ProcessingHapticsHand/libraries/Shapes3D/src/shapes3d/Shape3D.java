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

import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

import processing.core.PApplet;
import processing.core.PGraphics;
import processing.core.PImage;
import processing.core.PMatrix;
import processing.core.PVector;
import processing.opengl.PGraphics3D;
import shapes3d.utils.Messages;
import shapes3d.utils.Picked;
import shapes3d.utils.SConstants;
import shapes3d.utils.Textures;
import shapes3d.utils.TransformUV;
import shapes3d.utils.Util;

/**
 * This is the base class for all 3D shapes. <br>
 * Each shape may consist of 1-8 parts, for instance the <br>
 * <ul>
 * <li>Box has 6 parts, the 6 sides </li>
 * <li>Cone has 2 parts, 2 half cones (top and bottom) </li>
 * <li>Ellipsoid has 1 part, the main body </li>
 * <li>Extrusion has 3 parts the main body and the 2 end caps. </li>
 * <li>Tube has 3 parts the main body and the 2 end caps. </li>
 * <li>LatheStock has 3 parts the rotated surface and the 2 end caps. </li>
 * </ul>
 * So when shape picking it is not only possible to detect which shape is picked 
 * but also the actual part. <br>
 * 
 * @author Peter Lager
 *
 */
public abstract class Shape3D implements SConstants {

	// Maps used for picking
	// Each shape has 8 unique pick colors associated with it. This map is used to find the  
	// Shape for a given color
	protected static HashMap<Integer, Shape3D> mapColor2Shape = new HashMap<Integer, Shape3D>();
	// Find the colorBuffer associated with a particular canvas
	protected static HashMap<PGraphics, PGraphics> mapCanvas2ColorBuffer = new HashMap<PGraphics, PGraphics>();
	// List of all shapes instantiated
	protected static List<Shape3D> shapesMade = new ArrayList<Shape3D>();
	// Set to store all picks from a selection marquee
	protected static Set<Picked> marqueeSelection = new HashSet<Picked>();
	// Next shape index
	private static int nextShapeNo = 0;

	protected static boolean show_normals = false;
	protected static int normal_color = 0xFFFF00FF;
	protected static float normal_weight = 1.0f;
	protected static float normal_length = 10;

	// Counter used to provide unique colour value for each shape
	protected static int nextPickColor = 0xFF000000;
	// Buffer used for shape picking
	protected static boolean keepCopy = false;
	protected static PImage pbImage = null;

	public static void showSurfaceNormals() {
		show_normals = true;
	}

	public static void showSurfaceNormals(int color, float weight, float length) {
		show_normals = true;
		normal_color = color;
		normal_weight = weight;
		normal_length = length;
	}

	public static void hideSurfaceNormals() {
		show_normals = false;		
	}

	public static int nextPickColor() {
		nextPickColor += 8;
		return nextPickColor;
	}

	/**
	 * Will find the shape nearest to the viewer that is drawn at the given pixel position. <br>
	 * The user must specify the drawing canvas to use.
	 * @param app allows access to Processing methods / functions
	 * @param canvas the canvas to use
	 * @param x x position to test
	 * @param y y position to test
	 * @return a Picked object with details of the shape picked or null if no shape is drawn at the given position.
	 */
	public static Picked pick(PApplet app, PGraphics canvas, int x, int y){
		PGraphics colorBuffer = mapCanvas2ColorBuffer.get(canvas);
		if(colorBuffer == null || colorBuffer.width != canvas.width || colorBuffer.height != canvas.height){
			colorBuffer = (PGraphics3D) app.createGraphics(canvas.width, canvas.height, PApplet.P3D);
			// The next four lines are required to initialise the pick buffer. If they are not included
			// the first call to this method from Processing fails.
			colorBuffer.noSmooth();
			colorBuffer.beginDraw();
			colorBuffer.background(WHITE);
			colorBuffer.endDraw();
			// Store the link between draw surface and buffer
			mapCanvas2ColorBuffer.put(canvas,  colorBuffer);
		}
		colorBuffer.beginDraw();
		colorBuffer.noLights();
		colorBuffer.noStroke();
		colorBuffer.background(WHITE);

		// Iterate all shapes made and draw those on this canvas to the pick-buffer
		for(Shape3D shape : shapesMade) {
			if (shape.on_canvas == canvas  && shape.pickable) {
				shape.drawPickBuffer(colorBuffer);
			}			
		}
		colorBuffer.endDraw();

		if(keepCopy) {
			pbImage = colorBuffer.get();
		}
		int c = colorBuffer.get(x,y);
		Shape3D shapePicked = mapColor2Shape.get(c);
		int shapePart = (c & 0x07);
		int shapeFlag = (1 << (c & 0x07));
		if(shapePicked != null) {
			shapePicked.fireEvent(shapePicked, shapePart, shapeFlag);
			return new Picked(shapePicked, shapePart, shapeFlag );
		}
		return null;
	}


	/**
	 * Will find all shapes that are visible in a rectangular area of the canvas. The area is defined
	 * by any two diagonally opposed corners. <br>
	 * 
	 * @param app allows access to Processing methods / functions
	 * @param canvas the canvas to use
	 * @param x0 horizontal position of a corner 0 of the selection area
	 * @param y0 vertical position of a corner 0 of the selection area
	 * @param x1 horizontal position of a corner 1 of the selection area
	 * @param y1 vertical position of a corner 1 of the selection area
	 * @param comp the comparator used to sort the pick results.
	 * @return an ordered array of shapes/parts visible in the selection aea
	 */
	public static Picked[] pick(PApplet app, PGraphics canvas, int x0, int y0, int x1, int y1){
		PGraphics colorBuffer = mapCanvas2ColorBuffer.get(canvas);
		if(colorBuffer == null || colorBuffer.width != canvas.width || colorBuffer.height != canvas.height){
			colorBuffer = (PGraphics3D) app.createGraphics(canvas.width, canvas.height, PApplet.P3D);
			// The next four lines are required to initialise the pick buffer. If they are not included
			// the first call to this method from Processing fails.
			colorBuffer.noSmooth();
			colorBuffer.beginDraw();
			colorBuffer.background(WHITE);
			colorBuffer.endDraw();
			// Store the link between draw surface and buffer
			mapCanvas2ColorBuffer.put(canvas,  colorBuffer);
		}
		// Get the selection marquee
		int[] marquee = Util.box_box_p(x0, y0, x1, y1,
				0, 0, colorBuffer.width - 1, colorBuffer.height - 1);
		if(marquee.length != 4) {
			return new Picked[0];
		}
		// Draw pick buffer
		colorBuffer.beginDraw();
		colorBuffer.noLights();
		colorBuffer.noStroke();
		colorBuffer.background(WHITE);

		// Iterate all shapes made and draw those on this canvas to the pick-buffer
		for(Shape3D shape : shapesMade) {
			if (shape.on_canvas == canvas  && shape.pickable) {
				shape.drawPickBuffer(colorBuffer);
			}			
		}
		colorBuffer.endDraw();

		if(keepCopy) {
			pbImage = colorBuffer.get();
		}
		// Clear the existing marquee selection
		marqueeSelection.clear();
		// Load the buffer pixels
		colorBuffer.loadPixels();
		int[] p = colorBuffer.pixels;

		for(int v = marquee[1]; v <= marquee[3]; v++) {
			int v_offset = v * colorBuffer.width;
			for(int h = marquee[0]; h <= marquee[2]; h++) {
				int c = p[h + v_offset];
				Shape3D shapePicked = mapColor2Shape.get(c);
				if(shapePicked != null) {
					int shapePart = (c & 0x07);
					int shapeFlag = (1 << (c & 0x07));
					marqueeSelection.add(new Picked(shapePicked, shapePart, shapeFlag));
				}
			}
		}
		Picked[] picked = marqueeSelection.toArray(new Picked[marqueeSelection.size()]);
		Arrays.sort(picked);
		return picked;
	}

	/**
	 * This method accepts an array of Picked objects, possibly from a marquee
	 * selection and merge the results so that each pick object is for a unique
	 * shape and the part flag will indicate all the parts selected for that object. <br>
	 * The original Picked object array is unchanged. <br>
	 * 
	 * @param picked the array of picked objects (1 for each part picked)
	 * @return an array of picked objects (1 for each shape)
	 */
	public static Picked[] mergePicks(Picked[] picked) {
		Map<Shape3D, Integer> map = new HashMap<Shape3D, Integer>();
		for(Picked p : picked) {
			Integer f = map.get(p.shape);
			f = (f == null) ? p.partFlag : f | p.partFlag;
			map.put(p.shape, f);
		}
		Picked[] result = new Picked[map.size()];
		int idx = 0;
		for (Map.Entry<Shape3D, Integer> entry : map.entrySet()) {
			result[idx++] = new Picked(entry.getKey(), -1, entry.getValue());
		}
		return result;
	}

	/**
	 * Shapes3D can keep an image of the last pick buffer. This is useful for 
	 * debugging but should not be used otherwise because it use significant 
	 * processor time.
	 * @param keep true if we want to keep a copy of the buffer
	 */
	public static void keepPickBufferImage(boolean keep) {
		keepCopy = keep;
	}

	/**
	 * Get a copy of the last pick buffer used. If you want to use this 
	 * facility then enable it with the keepPickBufferImage(boolean) method.
	 * @return null if no image exists else a copy of the pickbuffer
	 */
	public static PImage pickBufferImage() {
		return pbImage;
	}

	/**
	 * Return the number of shapes created so far.
	 * @return the next shape number to use
	 */
	public static int nbrShapes3D() {
		return nextShapeNo;
	}

	// ############################################################################################
	// ############################################################################################
	//                    Instance attributes and methods
	// ############################################################################################
	// This is the last surface this shape was drawn to. A single shape 
	// can be drawn to multiple canvases.
	protected PGraphics on_canvas;
	// This is  a copy of the matrix when the shape was drawn
	protected PMatrix on_canvas_matrix;

	//	protected Optional<Pilot> pilot;

	// Current position, rotation and velocity for this shape.
	protected PVector pos = new PVector(0,0,0);	
	protected PVector rot = new PVector(0,0,0);
	// Up vector (starts along positive Y axis)
	protected PVector up = new PVector(0,1,0);
	// Centre of rotation (starts as [0,0,0] )
	protected PVector centreRot = new PVector(0,0,0);
	// Shape scale factor
	protected float shapeScale = 1.0f;

	// The parts that make up the entire shape
	protected _ShapePart[] shapeParts = new _ShapePart[0]; // avoid null tests :-)
	// SHape part flag mask
	protected int useParts = ALL;

	protected int pickColor;
	protected boolean pickable = true;

	// Event handling
	/* The object to handle the event */
	protected Object eventHandlerObject = null;
	/* The method in eventHandlerObject to execute */
	protected Method eventHandlerMethod = null;
	/* the name of the method to handle the event */ 
	protected String eventHandlerMethodName;

	/**
	 * User defined tag for this shape. <br>
	 * This can be any text the user likes or finds useful. When a shape is created
	 * this is initialised to the name of the class e.g. Toroid, Cone etc.
	 * 
	 */
	public String tag;

	/**
	 * User defined tag number. <br>
	 * This can be any number the user likes or finds useful.
	 */
	public int tagNo = 0;

	/**
	 * All child classes should call this constructor.
	 */
	public Shape3D(){
		S3D.announceShapes3D();
		// Get the pickcolor for this shape. 
		// Each shape can have 1 to 8 pick colors
		pickColor = nextPickColor();
		for(int i = 0; i < 8; i++) {
			mapColor2Shape.put(pickColor + i, this);
		}
		tagNo = (++nextShapeNo);
		tag = this.getClass().getSimpleName() + " (" + tagNo + ")";
		shapesMade.add(this);
	}

	public abstract Shape3D getThis();

	protected abstract void calcShape();
	protected abstract void makeParts();
	protected abstract void releaseMemory();

	/**
	 * Attempt to create the default pick event handler for this shape. 
	 * The default event handler is a method that returns void and has a single
	 * parameter of the same type as the control class generating the
	 * event and a method name specific for that class. 
	 * 
	 * @param obj the object to handle the event
	 * @param methodName the method to execute in the object handler class
	 */
	public void addPickHandler(Object obj, String methodName){
		try{
			eventHandlerObject = obj;
			eventHandlerMethodName = methodName;
			eventHandlerMethod = obj.getClass().getMethod(methodName, new Class<?>[] {Shape3D.class, int.class, int.class } );
		} catch (Exception e) {
			Messages.nonexistantEventHandler(new Object[] {this, methodName } );
			eventHandlerObject = null;
			eventHandlerMethodName = "";
		}
	}

	/**
	 * Attempt to fire an event for this control.
	 * 
	 * The method called must have a single parameter which is the object 
	 * firing the event.
	 * If the method to be called is to have different parameters then it should
	 * be overridden in the child class
	 * The method 
	 */
	protected void fireEvent(Object... objects){
		if(eventHandlerMethod != null){
			try {
				eventHandlerMethod.invoke(eventHandlerObject, objects);
			} catch (Exception e) {
				Messages.eventHandlerFailed(new Object[] {eventHandlerObject, eventHandlerMethodName, e } );
			}
		}		
	}

	/**
	 * Determines whether this shape can be picked. 
	 * If false then shapes behind this shape can be picked instead.
	 * @param pickable if true this shape can be picked
	 * @return this shape
	 */
	public Shape3D pickable(boolean pickable) {
		this.pickable = pickable;
		return getThis();
	}

	/**
	 * Is this shape pickable
	 * @return true if this shape is pickable
	 */
	public boolean pickable() {
		return pickable;
	}

	/**
	 * Get the number of parts created for this shape
	 * @return the number of shape parts in this shape
	 */
	public int nbrParts() {
		return shapeParts.length;
	}

	/**
	 * The following methods<br>
	 * drawMode, fill, stroke, strokeWeight, visible, texture, movie, uv <br>
	 * have two versions, the two parameter version <br>
	 * <pre>method_name(value, parts) </pre>
	 * where the first parameter is the value to apply and the second specifies 
	 * which shape parts to apply the value to. <br>
	 * The second version has just a single parameter <br>
	 * <pre>method_name(value) </pre>
	 * where the parameter is the value to apply. By default this value will be applied
	 * to <em>all</em> the shape parts. <br>
	 * This method allows you to specify which parts should be modified with this version of the method. <br>
	 * To revert back to the original default behaviour call <br>
	 * <pre> shape.use(S3D.ALL); </pre>
	 * @param parts_to_use the shape parts modified in the single parameter method
	 * @return this shape
	 */
	public Shape3D use(int parts_to_use) {
		useParts = parts_to_use & ALL;
		return getThis();
	}

	/**
	 * Set the tag to be used for all parts.
	 * @param tag the tag the descriptor string
	 * @return this shape
	 */
	public Shape3D tag(String tag){
		return tag(tag, useParts);
	}

	/**
	 * Set the tag for all the specified parts.
	 * @param tag the descriptor string
	 * @param parts the parts affected
	 * @return this shape
	 */
	public Shape3D tag(String tag, int parts){
		for(int pn = 0, flag = 1; pn < shapeParts.length; pn++) {
			if(flag == (parts & flag)) {
				shapeParts[pn].tag = tag;
			}
			flag <<= 1;
		}
		return getThis();
	}

	/**
	 * Get an array of the tags for the shape parts.
	 * @return an array holding the tags of the shape parts
	 */
	public String[] tags(){
		String[] array = new String[shapeParts.length];
		for(int i = 0; i < array.length; i++) {
			array[i] =  shapeParts[i].tag;
		}
		return array;
	}

	/**
	 * The draw mode can be either <br>
	 * S3D.SOLID - solid color as set with fill() method <br>
	 * S3D.WIRE - wire frame colour and wire thickness set with stroke() and strokeWeight() methods <br>
	 * S3D.TEXTURE - an image or movie is used to fill the shape <br>
	 * or any combination by or'ing them together e.g. S3D.SOLID | S3D.WIRE <br>
	 * Sets the drawing mode for all parts of the shape.
	 * @param mode the draw mode 
	 * @return this shape
	 */
	public Shape3D drawMode(int mode){
		return drawMode(mode, useParts);
	}

	/**
	 * The draw mode can be either <br>
	 * S3D.SOLID - solid color as set with fill() method <br>
	 * S3D.WIRE - wire frame colour and wire thickness set with stroke() and strokeWeight() methods <br>
	 * S3D.TEXTURE - an image or movie is used to fill the shape <br>
	 * or any combination by or'ing them together e.g. S3D.SOLID | S3D.WIRE <br>
	 * Sets the drawing mode for the specified parts of the shape.
	 * @param mode the draw mode 
	 * @param parts the parts to be textured
	 * @return this shape
	 */
	public Shape3D drawMode(int mode, int parts){
		for(int pn = 0, flag = 1; pn < shapeParts.length; pn++) {
			if(flag == (parts & flag)) {
				shapeParts[pn].drawMode(mode);
			}
			flag <<= 1;
		}
		return getThis();
	}

	/**
	 * Get an array of the draw modes for the shape parts.
	 * @return an array of the draw modes for the shape parts
	 */
	public int[] drawModes(){
		int[] array = new int[shapeParts.length];
		for(int i = 0; i < array.length; i++) {
			array[i] =  shapeParts[i].drawMode();
		}
		return array;
	}

	/**
	 * Set the fill color for all the shape parts.
	 * @param col the color to use
	 * @return this shape
	 */
	public Shape3D fill(int col){
		return fill(col, useParts);
	}

	/**
	 * Set the fill color for the specified shape parts.
	 * @param col the color to use
	 * @param parts the parts affected
	 * @return this shape
	 */
	public Shape3D fill(int col, int parts){
		for(int pn = 0, flag = 1; pn < shapeParts.length; pn++) {
			if(flag == (parts & flag)) {
				shapeParts[pn].fill(col);
			}
			flag <<= 1;
		}
		return getThis();
	}

	/**
	 * @return an array of the fill colors for the shape parts.
	 */
	public int[] fills(){
		int[] array = new int[shapeParts.length];
		for(int i = 0; i < array.length; i++) {
			array[i] =  shapeParts[i].fill();
		}
		return array;
	}

	/**
	 * Set the stroke color for all the shape parts
	 * @param col the color to use
	 * @return this shape
	 */
	public Shape3D stroke(int col){
		return stroke(col, useParts);
	}

	/**
	 * Set the stroke color for the specified shape parts
	 * @param col the color to use
	 * @param parts the parts affected
	 * @return this shape
	 */
	public Shape3D stroke(int col, int parts){
		for(int pn = 0, flag = 1; pn < shapeParts.length; pn++) {
			if(flag == (parts & flag)) {
				shapeParts[pn].stroke(col);
			}
			flag <<= 1;
		}
		return getThis();
	}

	/**
	 * @return an array of the stroke colors for the shape parts.
	 */
	public int[] strokes(){
		int[] array = new int[shapeParts.length];
		for(int i = 0; i < array.length; i++) {
			array[i] =  shapeParts[i].stroke();
		}
		return array;
	}

	/**
	 * Set the stroke weight for all the shape parts
	 * @param weight the stroke weight to use
	 * @return this shape
	 */
	public Shape3D strokeWeight(float weight){
		return strokeWeight(weight, useParts);
	}

	/**
	 * Set the stroke weight for all the shape parts
	 * @param weight the stroke weight to use
	 * @param parts the parts affected
	 * @return this shape
	 */
	public Shape3D strokeWeight(float weight, int parts){
		for(int pn = 0, flag = 1; pn < shapeParts.length; pn++) {
			if(flag == (parts & flag)) {
				shapeParts[pn].strokeWeight(weight);
			}
			flag <<= 1;
		}
		return getThis();
	}

	/**
	 * Get an array of the stroke weights for the shape parts.
	 * @return an array of the stroke weights applied to the shape parts
	 */
	public float[] strokeWeights(){
		float[] array = new float[shapeParts.length];
		for(int i = 0; i < array.length; i++) {
			array[i] =  shapeParts[i].strokeWeight();
		}
		return array;
	}

	/**
	 * Set the scale for this shape
	 * @param scale the scale to be used for the rendered shape
	 * @return this shape
	 */
	public Shape3D scale(float scale) {
		this.shapeScale = scale;
		return getThis();
	}


	/**
	 * 
	 * @return the rendering scale for this shape
	 */
	public float scale() {
		return shapeScale;
	}

	// ======= MOVIE TEXTURES ==========================================

	/**
	 * Use a processing.video.Movie object as a texture for all parts of this 
	 * shape.
	 * @param pApplet the enclosing PApplet object
	 * @param movie the movie to use as a texture
	 * @return this shape
	 */
	public Shape3D movie(PApplet pApplet, PImage movie) {
		return movie(pApplet, movie, useParts);
	}

	/**
	 * Use a processing.video.Movie object as a texture for the specified parts 
	 * of this shape.
	 * @param pApplet the enclosing PApplet object
	 * @param movie the movie to use as a texture
	 * @param parts the parts affected
	 * @return this shape
	 */
	public Shape3D movie(PApplet pApplet, PImage movie, int parts){
		for(int pn = 0, flag = 1; pn < shapeParts.length; pn++) {
			if(flag == (parts & flag)) {
				shapeParts[pn].movie(pApplet, movie);
			}
			flag <<= 1;
		}
		return getThis();
	}

	// ======= IMAGE TEXTURES ==========================================
	/**
	 * Use a processing.core.PImage object as a texture for all parts 
	 * of this shape.
	 *  
	 * @param app the enclosing PApplet object
	 * @param filename the image filename
	 * @return this shape
	 */
	public Shape3D texture(PApplet app, String filename){
		return texture(Textures.loadImage(app, filename), useParts);
	}

	/**
	 * Use a processing.core.PImage object as a texture for all parts 
	 * of this shape.
	 *  
	 * @param texture the PImage to use as the texture
	 * @return this shape
	 */
	public Shape3D texture(PImage texture){
		return texture(texture, useParts);
	}

	/**
	 * Use a processing.core.PImage object as a texture for the specified parts 
	 * of this shape.
	 *  
	 * @param pApplet the enclosing PApplet object
	 * @param filename the image filename
	 * @param parts the parts to be textured
	 * @return this shape
	 */
	public Shape3D texture(PApplet app, String filename, int parts){
		return texture(Textures.loadImage(app, filename), parts);
	}

	/**
	 * Use a processing.core.PImage object as a texture for the specified parts 
	 * of this shape.
	 *  
	 * @param texture the PImage to use as the texture
	 * @param parts the parts to be textured
	 * @return this shape
	 */
	public Shape3D texture(PImage texture, int parts){
		for(int pn = 0, flag = 1; pn < shapeParts.length; pn++) {
			if(flag == (parts & flag)) {
				shapeParts[pn].texture(texture);
			}
			flag <<= 1;
		}
		return getThis();
	}

	/**
	 * @return an array of the textures used for the shape parts.
	 */
	public PImage[] textures(){
		PImage[] array = new PImage[shapeParts.length];
		for(int i = 0; i < array.length; i++) {
			array[i] =  shapeParts[i].texture();
		}
		return array;
	}

	/**
	 * Set the texture coordinates for all shape parts.
	 * @param u0 horizontal texture coordinate
	 * @param u1 horizontal texture coordinate
	 * @param v0 vertical texture coordinate
	 * @param v1 vertical texture coordinate
	 * @return this shape
	 */
	public Shape3D uv(float u0, float u1, float v0, float v1){
		return uv(u0, u1, v0, v1, useParts);
	}

	/**
	 * Set the texture coordinates for the specified shape parts.
	 * @param u0 horizontal texture coordinate
	 * @param u1 horizontal texture coordinate
	 * @param v0 vertical texture coordinate
	 * @param v1 vertical texture coordinate
	 * @param parts the parts to be affected
	 * @return this shape
	 */
	public Shape3D uv(float u0, float u1, float v0, float v1, int parts){
		for(int pn = 0, flag = 1; pn < shapeParts.length; pn++) {
			if(flag == (parts & flag)) {
				shapeParts[pn].uv(u0, u1, v0, v1);
			}
			flag <<= 1;
		}
		return getThis();
	}

	/**
	 * Use this to transform the UV coordinates for all parts.
	 * 
	 * @param transformer the UV transformation to apply
	 * @return this shape
	 */
	public Shape3D uvt(TransformUV transformer) {
		return uvt(transformer, useParts);
	}

	/**
	 * Use this to transform the UV coordinates for the specified parts.
	 * 
	 * @param transformer the UV transformation to apply
	 * @param parts combined part flags
	 * @return this shape
	 */
	public Shape3D uvt(TransformUV transformer, int parts) {
		for(int pn = 0, flag = 1; pn < shapeParts.length; pn++) {
			if(flag == (parts & flag)) {
				shapeParts[pn].uvt(transformer);
			}
			flag <<= 1;
		}
		return getThis();
	}

	/**
	 * Use this to decide whether the texture is repeated or clamped. <br>
	 * The parameter must be either REPEAT or CLAMP, any other 
	 * value will be ignored. 
	 * @param wrap REPEAT or CLAMP
	 * @return this shape
	 */
	public Shape3D uvwrap(int wrap) {
		return uvwrap(wrap, useParts);
	}

	/**
	 * Use this to decide whether the texture is repeated or clamped for 
	 * the specified parts. <br>
	 * The parameter must be either REPEAT or CLAMP, any other 
	 * value will be ignored. 
	 * @param wrap REPEAT or CLAMP
	 * @param parts combined part flags
	 * @return this shape
	 */
	public Shape3D uvwrap(int wrap, int parts) {
		for(int pn = 0, flag = 1; pn < shapeParts.length; pn++) {
			if(flag == (parts & flag)) {
				shapeParts[pn].uvwrap(wrap);
			}
			flag <<= 1;
		}
		return getThis();
	}

	public Shape3D mesh(int nbrColSlices, int nbrRowSlices) {
		return mesh(nbrColSlices, nbrRowSlices, useParts);
	}

	public Shape3D mesh(int nbrColSlices, int nbrRowSlices, int parts) {
		for(int pn = 0, flag = 1; pn < shapeParts.length; pn++) {
			if(flag == (parts & flag)) {
				shapeParts[pn].mesh(nbrColSlices, nbrRowSlices);
			}
			flag <<= 1;
		}
		return getThis();
	}

	/**
	 * Makes all shape parts visible or invisible.
	 * 
	 * @param visible true if you want to see this shape
	 * @return this shape
	 */
	public Shape3D visible(boolean visible){
		return visible(visible, useParts);
	}

	/**
	 * Makes the specified shape parts visible or invisible.
	 * @param visible true if you want to see this shape
	 * @param parts combined part flags
	 * @return this shape
	 */
	public Shape3D visible(boolean visible, int parts){
		for(int pn = 0, flag = 1; pn < shapeParts.length; pn++) {
			if(flag == (parts & flag)) {
				shapeParts[pn].visible(visible);
			}
			flag <<= 1;
		}
		return getThis();
	}

	/**
	 * @return an array of booleans representing the visibility 
	 * state of the shape parts.
	 */
	public boolean[] visibles(){
		boolean[] array = new boolean[shapeParts.length];
		for(int i = 0; i < array.length; i++) {
			array[i] =  shapeParts[i].isVisible();
		}
		return array;
	}

	/**
	 * Sets the shape's current position.
	 * @param pos the new position
	 * @return this shape
	 */
	public Shape3D moveTo(PVector pos) {
		this.pos.x = pos.x;
		this.pos.y = pos.y;
		this.pos.z = pos.z;
		return getThis();
	}

	/**
	 * Sets the shape's current position.
	 * @param x x coordinate
	 * @param y y coordinate
	 * @param z z coordinate
	 * @return this shape
	 */
	public Shape3D moveTo(float x, float y, float z){
		pos.x = x;
		pos.y = y;
		pos.z = z;
		return getThis();
	}

	/**
	 * Sets the shape's current position. <br>
	 * Position is unchanged if the parameter array has less than 
	 * 3 elements.
	 * @param xyz the [xyz] coordinates
	 * @return this shape
	 */
	public Shape3D moveTo(float[] xyz){
		if(xyz.length >= 3){
			pos.x = xyz[0];
			pos.y = xyz[1];
			pos.z = xyz[2];
		}
		return getThis();
	}

	public float x() {
		return pos.x;
	}

	public float y() {
		return pos.y;
	}

	public float z() {
		return pos.z;
	}

	/**
	 * @return the current position as a PVector
	 */
	public PVector getPosVec() {
		return new PVector(pos.x, pos.y, pos.z);
	}

	/**
	 * Get the current rotations as a PVector
	 * 
	 * @param target use this object to store position
	 * @return the updated position
	 */
	public PVector getPosVec(PVector target){
		if(target == null)
			target = new PVector();
		target.set(pos);
		return target;
	}

	/**
	 * @return the current position as an array.
	 */
	public float[] getPosArray(){
		return getPosArray(null);
	}

	/**
	 * Get the current position as an array. <br>
	 * If target is not null it is used to store the current position.
	 * @param target use this object to store position
	 * @return the updated position
	 */
	public float[] getPosArray(float[] target){
		if(target == null || target.length < 3)
			target = new float[3];
		target[0] = pos.x;
		target[1] = pos.y;
		target[2] = pos.z;
		return target;
	}

	/**
	 * @return the current rotations as a PVector
	 */
	public PVector getRotVec() {
		return new PVector(rot.x, rot.y, rot.z);
	}

	/**
	 * Get the current rotations as a PVector
	 * 
	 * @param target use this object to store rotations
	 * @return the three orthogonal angles
	 */
	public PVector getRotVec(PVector target){
		if(target == null)
			target = new PVector();
		target.set(rot);
		return target;
	}

	/**
	 * @return the current rotations as an array.
	 */
	public float[] getRotArray(){
		return getRotArray(null);
	}

	/**
	 * Get the current rotations as an array. <br>
	 * If target is not null it is used to store the current position.
	 * @param target use this object to store rotations
	 * @return the three orthogonal angles
	 */
	public float[] getRotArray(float[] target){
		if(target == null || target.length < 3)
			target = new float[3];
		target[0] = rot.x;
		target[1] = rot.y;
		target[2] = rot.z;
		return target;
	}

	/**
	 * Set the current rotations.
	 * @param angles a PVector containing the x/y/z rotations in radians.
	 * @return this shape
	 */
	public Shape3D rotateTo(PVector angles) {
		rot.set(angles);
		return getThis();
	}

	/**
	 * Set the current rotations.
	 * Ignored if the array has less than 3 elements.
	 * @param angles an array containing the x/y/z rotations in radians.
	 * @return this shape
	 */
	public Shape3D rotateTo(float[] angles){
		if(angles.length >= 3){
			rot.x = angles[0];
			rot.y = angles[1];
			rot.z = angles[2];
		}
		return getThis();
	}

	/**
	 * Set the current rotations.
	 * @param x rotation about x axis
	 * @param y rotation about y axis
	 * @param z rotation about z axis
	 * @return this shape
	 */
	public Shape3D rotateTo(float x, float y, float z) {
		rot.x = x;
		rot.y = y;
		rot.z = z;
		return getThis();
	}

	/**
	 * Set the rotation about the x axis
	 * @param x the angle in radians
	 * @return this shape
	 */
	public Shape3D rotateToX(float x){
		rot.x = x;
		return getThis();
	}

	/**
	 * Set the rotation about the y axis
	 * @param y the angle in radians
	 * @return this shape
	 */
	public Shape3D rotateToY(float y){
		rot.y = y;
		return getThis();
	}

	/**
	 * Set the rotation about the z axis
	 * @param z the angle in radians
	 * @return this shape
	 */
	public Shape3D rotateToZ(float z){
		rot.z = z;
		return getThis();
	}

	/**
	 * Rotate shape from its current rotation state by the specified angles (radians)<br>
	 * @param x add this angle to the current x rotation angle
	 * @param y add this angle to the current y rotation angle
	 * @param z add this angle to the current z rotation angle
	 * @return this shape
	 */
	public Shape3D rotateBy(float x, float y, float z){
		rot.x += x;
		rot.y += y;
		rot.z += z;
		return getThis();
	}

	/**
	 * Rotate shape from its current rotation state by the specified angles (radians)
	 * in the array.<br>
	 * Ignored if the array has less than 3 elements. 
	 * @param angle an array of relative angles
	 * @return this shape
	 */
	public Shape3D rotateBy(float[] angle){
		if(angle.length >= 3){
			rot.x += angle[0];
			rot.y += angle[1];
			rot.z += angle[2];
		}
		return getThis();
	}

	/**
	 * Rotate shape from its current rotation state by the specified angles (radians)
	 * in the PVector.<br>
	 * @param angles a PVector containing the XYZ relative angles
	 * @return this shape
	 */
	public Shape3D rotateBy(PVector angles){
		rot.add(angles);
		return getThis();
	}

	/**
	 * Change the rotation about the x axis by the specified amount.
	 * @param x the angle in radians
	 * @return this shape
	 */
	public Shape3D rotateByX(float x){
		rot.x += x;
		return getThis();
	}

	/**
	 * Change the rotation about the y axis by the specified amount.
	 * @param y the angle in radians
	 * @return this shape
	 */
	public Shape3D rotateByY(float y){
		rot.y += y;
		return getThis();
	}

	/**
	 * Change the rotation about the z axis by the specified amount.
	 * @param z the angle in radians
	 * @return this shape
	 */
	public Shape3D rotateByZ(float z){
		rot.z += z;
		return getThis();
	}

	public void draw(PGraphics pg) {
		on_canvas = pg;
		pg.pushMatrix();
		pg.pushStyle();

		pg.translate(pos.x, pos.y, pos.z);
		pg.rotateX(rot.x);
		pg.rotateY(rot.y);
		pg.rotateZ(rot.z);
		pg.scale(shapeScale);

		// After performing all the matrix transformations save the matrix
		// so it can be used
		on_canvas_matrix = pg.getMatrix().get();

		for(_ShapePart shapePart : shapeParts) {
			if(shapePart.visible) {
				shapePart.draw(pg);
			}
		}
		pg.popStyle();
		pg.popMatrix();
	}

	public void drawPickBuffer(PGraphics pg) {
		pg.pushMatrix();
		pg.pushStyle();

		pg.setMatrix(on_canvas_matrix);

		for(_ShapePart shapePart : shapeParts) {
			if(pickable && shapePart.visible && shapePart.drawMode != WIRE) {
				shapePart.drawPickBuffer(pg);
			}
		}
		pg.popStyle();
		pg.popMatrix();
	}

}
