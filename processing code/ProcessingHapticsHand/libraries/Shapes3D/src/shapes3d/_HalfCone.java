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
 * A circular or elliptical disc which can be raised or lowered at
 * the centre to make a cone shaped part.
 * 
 * @author Peter Lager
 *
 */
class _HalfCone extends _ShapePart {

	protected PVector[] coord;
	protected PVector[] normal;
	protected UV[] uvNorm;
	protected UV[] uv;

	public _HalfCone(int ppCol, PVector[] verts, PVector[] norms, UV[] uv_norm) {
		this(ppCol, verts, norms, uv_norm, "Half cone part");
	}

	/**
	 * 
	 * @param ppCol the pick color for this part    
	 * @param verts coordinates in CCW direction
	 * @param uv_norm normalised texture coordinates
	 * @param col surface color to start with
	 */
	public _HalfCone(int ppCol, PVector[] verts, PVector[] norms, UV[] uv_norm, String tag) {
		super(ppCol, tag);
		this.coord = verts;
		this.normal = norms;
		this.uvNorm = uv_norm;
//		this.coord = Util.deepCopy(verts);
//		this.normal = Util.deepCopy(norms);
//		this.uvNorm = Util.deepCopy(uv_norm);
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
	 * @param pg the graphics context
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
			for(int v = 0; v < coord.length; v++) {
				pg.normal(normal[v].x, normal[v].y, normal[v].z);
				pg.vertex(coord[v].x, coord[v].y, coord[v].z, uv[v].u, uv[v].v);
			}			
		}
		else {
			for(int v = 0; v < coord.length; v++) {
				pg.normal(normal[v].x, normal[v].y, normal[v].z);
				pg.vertex(coord[v].x, coord[v].y, coord[v].z);
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
					coord[v].x + Shape3D.normal_length * normal[v].x, 
					coord[v].y + Shape3D.normal_length * normal[v].y, 
					coord[v].z + Shape3D.normal_length * normal[v].z);
		}			
	}
	
	/**
	 * Draw this part on to a graphics context
	 * @param pg the pick buffer graphics context
	 */
	@Override
	public void drawPickBuffer(PGraphics pg) {
		pg.beginShape(TRIANGLE_FAN);
		pg.fill(partPickColor);
		for(int v = 0; v < coord.length; v++) {
			pg.vertex(coord[v].x, coord[v].y, coord[v].z);
		}			
		pg.endShape();			
	}


}