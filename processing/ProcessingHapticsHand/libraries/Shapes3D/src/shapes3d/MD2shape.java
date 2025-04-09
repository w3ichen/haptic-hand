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


import processing.core.PApplet;
import processing.core.PVector;
import shapes3d.utils.MD2;
import shapes3d.utils.MD2_AnimState;
import shapes3d.utils.MD2_Data;
import shapes3d.utils.Orientation;

/**
 * This shape can be built using 1 to 8 linked MD2 models. Linked models share 
 * the same number of frames and animation states, for instance a warrior and
 * his weapon. <br>
 * 
 * @author Peter Lager
 *
 */
public class MD2shape extends Shape3D  {
	
	private PApplet app = null;
	private String[] files;
	
	// Keep a reference to the first MD2 model and its data
	private _MD2mesh md2_part;

	/**
	 * Each MD2 model requires two files, the first first holds the numerical and 
	 * rendering data and the second file a bitmap for the skin texture. Since a 
	 * MD2shape can have more than one model simply pass a list of files as 
	 * data+skin file pairs.
	 *  
	 * @param app allows access to Processing methods/functions
	 * @param files data0, skin0, data1, skin1 ...
	 */
	public MD2shape(PApplet app, String... files) {
		this.app = app;
		this.files = files;
		makeParts();
		releaseMemory();
	}
	
	/**
	 * @return this shape
	 */
	public MD2shape getThis() {
		return this;
	}

	/**
	 * Update the model shape
	 * 
	 * @param delta_t
	 */
	public void update(float delta_t){
		for(_ShapePart part : shapeParts) {
			((_MD2mesh) part).update(delta_t);
		}
	}
	
	/**
	 * Gets the current animation position.
	 * Integer part is frame number and fractional part is interpolation
	 * value to next frame.
	 * 
	 * @return
	 */
	public float getAnimPos(){
		return md2_part.getAnimPos(); // cFrame + interpol;
	}

	/**
	 * Set the model state to be rendered animation is repeated for ever.
	 * @param stateNo
	 */
	public void setState(int stateNo){
		setState(stateNo, true);
	}

	/**
	 * Set the model state to be rendered 
	 * 
	 * @param stateNo
	 * @param true = repeat animation is repeated for ever
	 * @return 
	 */
	public MD2shape setState(int stateNo, boolean repeat){
		for(_ShapePart part : shapeParts) {
			((_MD2mesh) part).setState(stateNo, repeat);
		}
		return getThis();
	}

	/**
	 * get a particular animation state
	 * 
	 * @param stateNo
	 * @return animation state
	 */
	public MD2_AnimState getAnimState(int stateNo){
		return md2_part.getAnimState(stateNo);
	}
	
	/**
	 * Allows user to get and use any animation states available
	 * @return
	 */
	public MD2_AnimState[] getAnimStates(){
		return md2_part.getAnimStates();
	}

	/**
	 * Orient the vertex data for this model
	 * @param orientation
	 * @return
	 */
	public MD2shape orientModel(Orientation orientation){
		for(_ShapePart part : shapeParts) {
			((_MD2mesh) part).orientModel(orientation);
		}
		return getThis();
	}
	
	/**
	 * Centers the model so it evenly spaced over (0,0,0)
	 * Note: this will change all the XYZ points in the model
	 * @return 
	 */
	public MD2shape centreModel(){
		for(_ShapePart part : shapeParts) {
			((_MD2mesh) part).centreModel();
		}
		return getThis();
	}

	/**
	 * Centers the model so it evenly spaced over a given offset
	 * useful if we have 2 linked models.
	 * Note: this will change all the XYZ points in the model
	 * @param offset the distance to move vertices
	 * @return 
	 */
	public MD2shape centreModel(PVector offset){
		for(_ShapePart part : shapeParts) {
			((_MD2mesh) part).centreModel(offset);
		}
		return getThis();
	}

	/**
	 * Scales the model
	 * Note: this will change all the XYZ points in the model
	 * @param scale the scale factor to apply to vertices
	 */
	public MD2shape scaleModel(float scale){
		for(_ShapePart part : shapeParts) {
			((_MD2mesh) part).scaleModel(scale);
		}
		return getThis();
	}
	
	/**
	 * Get the offset of the model center from (0,0,0)
	 * @return distance of model center from [0,0,0]
	 */
	public PVector getModOffset(){
		return md2_part.getModOffset();
	}

	/**
	 * Get the size of the model
	 * @return the model's width, height and depth
	 */
	public PVector getModSize(){
		return md2_part.getModSize();
	}

	/**
	 * Get the model data from the first model
	 * @return the model data
	 */
	public MD2_Data getData() {
		return md2_part.getData();
	}

	@Override
	protected void calcShape() {}

	@Override
	protected void makeParts() {
		shapeParts = new _ShapePart[files.length / 2];
		for(int p = 0; p < files.length - 1; p += 2) {
			shapeParts[p/2] = new _MD2mesh(pickColor + p / 2, MD2.getModelData(app, files[p], files[p + 1]));
		}
		md2_part = (_MD2mesh) shapeParts[0];
	}

	@Override
	protected void releaseMemory() {
		app = null;
		files = null;
	}

}
