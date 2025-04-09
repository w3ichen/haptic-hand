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

import processing.core.PGraphics;
import processing.core.PVector;
import shapes3d.utils.UV;
import shapes3d.utils.Util;

/**
 * A generic 2D mesh that can be shaped by child classes.
 * 
 * @author Peter Lager
 *
 */
class _Mesh2D extends _ShapePart {

	protected PVector[][] coord;
	protected PVector[][] normal;  // Surface normals will be calculated by child class
	protected UV[][] uvNorm;
	protected UV[][] uv;

	/**
	 * Used by child classes if needed
	 * @param ppCol
	 * @param tag
	 */
	protected _Mesh2D(int ppCol, String tag) {
		super(ppCol, tag);
	}

	/**
	 * 
	 * @param ppCol
	 * @param coords
	 * @param uv_norm
	 * @param tag
	 */
	public _Mesh2D(int ppCol, PVector[][] coords, PVector[][] norms, UV[][] uv_norm, String tag) {
		super(ppCol, tag);
//		this.coord = Util.deepCopy(coords);
//		this.normal = Util.deepCopy(norms);
//		uvNorm = Util.deepCopy(uv_norm);
		this.coord = coords;
		this.normal = norms;
		uvNorm = Util.deepCopy(uv_norm);
		uv = Util.deepCopy(uv_norm);
		applyUV();
	}

	
	
	@Override
	protected _ShapePart applyUV() {
		float uRange = u1 - u0;
		float vRange = v1 - v0;
		for(int col = 0; col < uv.length; col++) { // u
			for(int row = 0; row < uv[col].length; row++) { // v
				transformer.transform(uvNorm[col][row], uv[col][row]);
				uv[col][row].u = u0 + uv[col][row].u * uRange;
				uv[col][row].v = v0 + uv[col][row].v * vRange;
			}
		}
		return this;
	}

	/**
	 * Draw this part on to a graphics context
	 * @param pg the graphics context
	 */
	@Override
	public void draw(PGraphics pg) {
		pg.pushStyle();
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
			pg.textureWrap(wrap);
			for(int col = 0; col < coord.length - 1; col++) {
				pg.beginShape(QUAD_STRIP);
				pg.texture(skin);
				for(int row = 0; row < coord[col].length; row++) {
					pg.normal(normal[col][row].x, normal[col][row].y, normal[col][row].z);
					pg.vertex(coord[col][row].x, coord[col][row].y, coord[col][row].z, uv[col][row].u, uv[col][row].v);
					pg.normal(normal[col+1][row].x, normal[col+1][row].y, normal[col+1][row].z);
					pg.vertex(coord[col+1][row].x, coord[col+1][row].y, coord[col+1][row].z, uv[col+1][row].u, uv[col+1][row].v);
				}
				pg.endShape();
			}
		}
		else {
			for(int col = 0; col < coord.length - 1; col++) {
				pg.beginShape(QUAD_STRIP);
				for(int row = 0; row < coord[col].length; row++) {
					pg.normal(normal[col][row].x, normal[col][row].y, normal[col][row].z);
					pg.vertex(coord[col][row].x, coord[col][row].y, coord[col][row].z);
					pg.normal(normal[col+1][row].x, normal[col+1][row].y, normal[col+1][row].z);
					pg.vertex(coord[col+1][row].x, coord[col+1][row].y, coord[col+1][row].z);
				}
				pg.endShape();
			}			
		}
		if(Shape3D.show_normals) {
			drawSurfaceNormals(pg);
		}
		pg.popStyle();
	}

	private void drawSurfaceNormals(PGraphics pg) {
		pg.stroke(Shape3D.normal_color);
		pg.strokeWeight(Shape3D.normal_weight);
		pg.hint(DISABLE_OPTIMIZED_STROKE);
		for(int col = 0; col < coord.length; col++) {
			for(int row = 0; row < coord[col].length; row++) {
				pg.line(coord[col][row].x, 
						coord[col][row].y, 
						coord[col][row].z, 
						coord[col][row].x + Shape3D.normal_length * normal[col][row].x, 
						coord[col][row].y + Shape3D.normal_length * normal[col][row].y, 
						coord[col][row].z + Shape3D.normal_length * normal[col][row].z);
			}			
		}
	}

//	private void drawSurfaceNormals2(PGraphics pg) {
//		pg.stroke(strokeColor);
//		pg.strokeWeight(strokeWeight);
//		pg.hint(DISABLE_OPTIMIZED_STROKE);
//		for(int col = 0; col < coord.length; col++) {
//			for(int row = 0; row < coord[col].length; row++) {
//				pg.line(coord[col][row].x, coord[col][row].y, coord[col][row].z, 
//						coord[col][row].x + normal[col][row].x, coord[col][row].y + normal[col][row].y, coord[col][row].z + normal[col][row].z);
//			}			
//		}
//	}

	/**
	 * Draw this part on to a graphics context
	 * @param pg the pick buffer graphics context
	 */
	@Override
	public void drawPickBuffer(PGraphics pg) {
		pg.fill(partPickColor);
		for(int col = 0; col < coord.length - 1; col++) {
			pg.beginShape(QUAD_STRIP);
			for(int row = 0; row < coord[col].length; row++) {
				pg.vertex(coord[col][row].x, coord[col][row].y, coord[col][row].z);
				pg.vertex(coord[col+1][row].x, coord[col+1][row].y, coord[col+1][row].z);
			}
			pg.endShape();
		}			
	}

}
