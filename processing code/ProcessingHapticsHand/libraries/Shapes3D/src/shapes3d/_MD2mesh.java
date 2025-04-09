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

import processing.core.PConstants;
import processing.core.PGraphics;
import processing.core.PMatrix;
import processing.core.PVector;
import shapes3d.utils.MD2_AnimState;
import shapes3d.utils.MD2_Data;
import shapes3d.utils.Orientation;

/**
 * This class is responsible for managing the animation and rendering of the MD2 model
 * 
 * @author Peter Lager
 *
 */
public class _MD2mesh extends _ShapePart implements PConstants {

	protected PVector pos = new PVector(0,0,0);	
	protected PVector rot = new PVector(0,0,0);

	private int stateIndex;         // index to current state
	private int cFrame;				// current frame # in animation
	private int nFrame;				// next frame # in animation
	private float interpol;			// percent through current frame
	private boolean repeat = true;	// repeat the state animation forever

	private MD2_Data mdata;

	// ====================================================================
	// The following attributes allow the user to use the model with
	// the Shapes3D library
	protected int pickColor;
	protected boolean pickable = false;

	protected PGraphics on_canvas = null;
	protected PMatrix on_canvas_matrix;
	// ====================================================================

	public _MD2mesh(int ppCol, MD2_Data mdata){
		super(ppCol);
		this.mdata = mdata; 
		if(mdata.skin != null){
			this.skin = mdata.skin;
			drawMode = TEXTURE;
		}
		else {
			drawMode = SOLID + WIRE;
		}
	}

	public void draw(PGraphics pg){
		pg.pushStyle();
		float x,y,z,s,t;
		int cmd;
		int vpos = 0;
		int cfIdx = cFrame * mdata.numXYZ;
		int nfIdx = nFrame * mdata.numXYZ;
		PVector cp,np;
		drawWhat();

		if(useSolid)
			pg.fill(fillColor);
		else
			pg.noFill();
		if(useWire){
			pg.stroke(strokeColor);
			pg.strokeWeight(strokeWeight);
			pg.hint(DISABLE_OPTIMIZED_STROKE);
		}
		else {
			pg.noStroke();
		}

		if(skin != null && useTexture){
			pg.textureMode(NORMAL);
			for(int i = 0; i < mdata.glComannd.length; i++){
				cmd = mdata.glComannd[i];
				if(cmd < 0){
					cmd = -cmd;
					pg.beginShape(TRIANGLE_FAN);
				}
				else if(cmd > 0) {
					pg.beginShape(TRIANGLE_STRIP);
				}
				pg.texture(skin);
				for(int j = 0; j < cmd; j++){
					cp = mdata.point[cfIdx + mdata.glVertex[vpos].idx];
					np = mdata.point[nfIdx + mdata.glVertex[vpos].idx];
					s = mdata.glVertex[vpos].s;
					t = mdata.glVertex[vpos].t;
					x = cp.x + interpol * (np.x - cp.x);
					y = cp.y + interpol * (np.y - cp.y);
					z = cp.z + interpol * (np.z - cp.z);
					pg.vertex(x, y, z, s, t);
					vpos++;
				}
				pg.endShape();
			}
		}
		else { // SOLID and/or WIRE modes
			for(int i = 0; i < mdata.glComannd.length; i++){
				cmd = mdata.glComannd[i];
				if(cmd < 0){
					cmd = -cmd;
					pg.beginShape(TRIANGLE_FAN);
				}
				else if(cmd > 0) {
					pg.beginShape(TRIANGLE_STRIP);
				}
				for(int j = 0; j < cmd; j++){
					cp = mdata.point[cfIdx + mdata.glVertex[vpos].idx];
					np = mdata.point[nfIdx + mdata.glVertex[vpos].idx];
					x = cp.x + interpol * (np.x - cp.x);
					y = cp.y + interpol * (np.y - cp.y);
					z = cp.z + interpol * (np.z - cp.z);
					pg.vertex(x, y, z);
					vpos++;
				}
				pg.endShape();
			}
		}			
		pg.popStyle();
	}


	public void drawPickBuffer(PGraphics pg) {
		pg.pushStyle();
		float x,y,z;
		int cmd;
		int vpos = 0;

		int cfIdx = cFrame * mdata.numXYZ;
		int nfIdx = nFrame * mdata.numXYZ;

		PVector cp,np;
		pg.fill(partPickColor);

		for(int i = 0; i < mdata.glComannd.length; i++){
			cmd = mdata.glComannd[i];
			if(cmd < 0){
				cmd = -cmd;
				pg.beginShape(TRIANGLE_FAN);
			}
			else if(cmd > 0) {
				pg.beginShape(TRIANGLE_STRIP);
			}
			for(int j = 0; j < cmd; j++){
				cp = mdata.point[cfIdx + mdata.glVertex[vpos].idx];
				np = mdata.point[nfIdx + mdata.glVertex[vpos].idx];
				x = cp.x + interpol * (np.x - cp.x);
				y = cp.y + interpol * (np.y - cp.y);
				z = cp.z + interpol * (np.z - cp.z);
				pg.vertex(x, y, z);
				vpos++;
			}
			pg.endShape();
		}
		pg.popStyle();
	}


	/**
	 * Update the interpolation value so that the model is animated.
	 *   
	 * @param delta_t the increment to be applied to the interpolation value
	 */
	public void update(float delta_t){
		int sFrame = mdata.anim_state[stateIndex].startframe;
		int eFrame = mdata.anim_state[stateIndex].endFrame;
		interpol += delta_t;
		
		// Repeat animation
		while(interpol >= 1.0f){
			interpol -= 1.0f;
			cFrame++;
			if(repeat){
				if(cFrame > eFrame)
					cFrame = sFrame;
				nFrame = cFrame + 1;
				if(nFrame > eFrame)
					nFrame = sFrame;
			}
			else {
				if(cFrame >= eFrame){
					cFrame = eFrame;
					nFrame = eFrame;
					interpol = 0;
				}
			}
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
		return cFrame + interpol;
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
	 */
	public void setState(int stateNo, boolean repeat){
		if(stateNo < 0 || stateNo >= mdata.anim_state.length){
			System.out.println("Invalid state " + stateNo + "  " + this);
			return;
		}
		this.repeat = repeat; 
		stateIndex = stateNo;	
		interpol = 0.0f;
		cFrame = mdata.anim_state[stateNo].startframe;
		nFrame = cFrame + 1;
		if(nFrame > mdata.anim_state[stateNo].endFrame)
			nFrame = mdata.anim_state[stateNo].startframe;
	}

	/**
	 * get a particular animation state
	 * 
	 * @param stateNo
	 * @return
	 */
	public MD2_AnimState getAnimState(int stateNo){
		if(stateNo < 0 || stateNo >= mdata.anim_state.length)
			return null;
		else
			return mdata.anim_state[stateNo];
	}
	/**
	 * Allows user to get and use any animation states available
	 * @return
	 */
	public MD2_AnimState[] getAnimStates(){
		return mdata.anim_state;
	}

	/**
	 * Centers the model so it evenly spaced over (0,0,0)
	 * Note: this will change all the XYZ points in the model
	 */
	public void orientModel(Orientation orientation){
		mdata.orientModel(orientation);
	}

	/**
	 * Centers the model so it evenly spaced over (0,0,0)
	 * Note: this will change all the XYZ points in the model
	 */
	public void centreModel(){
		mdata.centreModel();
	}

	/**
	 * Centers the model so it evenly spaced over a given offset
	 * useful if we have 2 linked models.
	 * Note: this will change all the XYZ points in the model
	 * @param offset the distance to move vertices
	 */
	public void centreModel(PVector offset){
		mdata.centreModel(offset);
	}

	/**
	 * Scales the model
	 * Note: this will change all the XYZ points in the model
	 * @param scale the scale factor to apply to vertices
	 */
	public void scaleModel(float scale){
		mdata.scaleModel(scale);
	}

	/**
	 * Get the offset of the model center from (0,0,0)
	 * @return distance of model center from [0,0,0]
	 */
	public PVector getModOffset(){
		return mdata.modOffset.copy();
	}

	/**
	 * Get the size of the model
	 * @return the model's width, height and depth
	 */
	public PVector getModSize(){
		return mdata.modSize.copy();
	}

	public MD2_Data getData() {
		return mdata;
	}
	
	/**
	 * Display the model statistics and memory usage
	 * @return textual description of model data
	 */
	public String toString(){
		return mdata.toString();
	}

	/**
	 * @return this shape part
	 */
	@Override
	protected _ShapePart applyUV() {
		return this;
	}


}



