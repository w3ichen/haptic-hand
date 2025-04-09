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
import processing.core.PVector;
import shapes3d.utils.SConstants;
import shapes3d.utils.UV;
import shapes3d.utils.Util;

/**
 * Objects of this class are used as end-caps for the Tube class
 * 
 * @author Peter Lager
 *
 */
class _Oval extends _ShapePart  implements SConstants, PConstants {

	protected PVector[] coord;
	protected PVector normal;
	protected UV[] uvNorm, uv;
	protected float radX, radY;

	public _Oval(int ppCol, PVector[] verts, PVector normal, UV[] uv_norm) {
		this(ppCol, verts, normal, uv_norm, " Oval part");
	}
	/**
	 * 
	 * @param ppCol part pick colour
	 * @param verts the vertices [0] = center of fan
	 * @param uv_norm the uv coordinates [0] = [0.5, 0.5]
	 */
	public _Oval(int ppCol, PVector[] verts, PVector normal, UV[] uv_norm, String tag) {
		super(ppCol, tag);
		this.normal = normal; 
//		this.coord = Util.deepCopy(verts);
//		this.uvNorm = Util.deepCopy(uv_norm);
		this.coord = verts;
		this.uvNorm = uv_norm;
		this.uv = Util.deepCopy(uvNorm);
	}

	@Override
	protected _ShapePart applyUV() {
		float uRange = u1 - u0;
		float vRange = v1 - v0;
		for(int c = 0; c < uv.length; c++) {
			transformer.transform(uvNorm[c], uv[c]);
			uv[c].u = u0 + uv[c].u * uRange;
			uv[c].v = v0 + uv[c].v * vRange;
		}
		return this;
	}

	/**
	 * Draw this part on to a graphics context
	 * @param pg the pick buffer graphics context
	 */
	@Override
	public void draw(PGraphics pg) {
		pg.pushStyle();
		drawWhat();
		pg.beginShape(TRIANGLE_FAN);
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
			pg.textureWrap(wrap);
			pg.texture(skin);
			for(int c = 0; c < coord.length; c++) {
				pg.normal(normal.x, normal.y, normal.z);
				pg.vertex(coord[c].x, coord[c].y, coord[c].z, uv[c].u, uv[c].v);
			}			
		}
		else {
			for(int c = 0; c < coord.length; c++) {
				pg.normal(normal.x, normal.y, normal.z);
				pg.vertex(coord[c].x, coord[c].y, coord[c].z);
			}			
		}
		pg.endShape();
		if(Shape3D.show_normals) {
			drawSurfaceNormals(pg);
		}
		pg.popStyle();
	}

	/**
	 * This is used for testing only
	 * @param pg the canvas
	 */
	private void drawSurfaceNormals(PGraphics pg) {
		pg.stroke(strokeColor);
		pg.strokeWeight(strokeWeight);
		pg.hint(DISABLE_OPTIMIZED_STROKE);
		for(int v = 0; v < coord.length; v++) {
			pg.line(coord[v].x, 
					coord[v].y, 
					coord[v].z, 
					coord[v].x + Shape3D.normal_length * normal.x, 
					coord[v].y + Shape3D.normal_length * normal.y, 
					coord[v].z + Shape3D.normal_length * normal.z);
		}			
	}

	/**
	 * This is used for testing only
	 * @param pg
	 */
//	private void drawSurfaceNormals(PGraphics pg) {
//		pg.stroke(strokeColor);
//		pg.strokeWeight(strokeWeight);
//		pg.hint(DISABLE_OPTIMIZED_STROKE);
//		for(int v = 0; v < coord.length; v++) {
//			pg.line(coord[v].x, coord[v].y, coord[v].z, coord[v].x + normal.x, coord[v].y + normal.y, coord[v].z + normal.z);
//		}			
//	}

	@Override
	public void drawPickBuffer(PGraphics pg) {
		//		if(!visible || drawMode == WIRE) return;
		pg.beginShape(TRIANGLE_FAN);
		pg.fill(partPickColor);
		for(int v = 0; v < coord.length; v++) {
			pg.vertex(coord[v].x, coord[v].y, coord[v].z);
		}			
		pg.endShape();		
	}


}
