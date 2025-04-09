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
import processing.core.PConstants;
import processing.core.PGraphics;
import processing.core.PVector;
import shapes3d.utils.UV;

/**
 * This class represents the closure cap for a LatheStock shape.
 * 
 * @author Peter Lager
 *
 */
class _LatheCap extends _ShapePart implements PConstants {

	// Model view coordinates of end cap
	// [0] is the centre, [1]-> the edges
	protected PVector[] coord;
	protected PVector normal;
	// UV texture coordinates normalised
	protected UV[] uvNorm, uv;

	/**
	 * 
	 * @param ppCol
	 * @param coords
	 * @param startAngle
	 * @param endAngle
	 */
	public _LatheCap(int ppCol, PVector[] coords, PVector normal, float startAngle, float endAngle) {
		this(ppCol, coords, normal, startAngle, endAngle, "Lathe end cap part");
	}
	
	/**
	 * 
	 * @param ppCol
	 * @param coords
	 * @param startAngle
	 * @param endAngle
	 * @param tag
	 */
	public _LatheCap(int ppCol, PVector[] coords, PVector normal, float startAngle, float endAngle, String tag) {
		super(ppCol, tag);
		this.coord = coords;
//		this.coord = Util.deepCopy(coords);
		this.normal = normal;
		// Can't do deep copy of coords because we need to add centre
		uvNorm = new UV[coord.length];
		uv = new UV[coord.length];
		uvNorm[0] = new UV(0.5f, 0.5f);
		uv[0] = new UV(0.5f, 0.5f);
		float deltaAngle = (endAngle - startAngle) / (coord.length - 2);
		for(int s = 1; s < uvNorm.length ; s++) {
			float a = startAngle + - s * deltaAngle;
			uvNorm[s] = new UV((1 - PApplet.cos(a))/2, (1 + PApplet.sin(a))/2);
			uv[s] = uvNorm[s].copy();
		}
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
