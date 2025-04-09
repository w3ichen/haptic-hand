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
 * Objects of the class are used as end-caps for object formed
 * by extrusion.
 * 
 * @author Peter Lager
 *
 */
class _Polygon extends _ShapePart {

	protected PVector[] coord;
	protected PVector normal;
	protected UV[] uvNorm;
	protected UV[] uv;

	protected int[] tr;


	public _Polygon(int ppCol, PVector[] verts, PVector normal, int[] tris, UV[] uv_norm) {
		this(ppCol, verts, normal, tris, uv_norm, "Polygon part");
	}

	/**
	 * 
	 * @param ppCol
	 * @param verts
	 * @param tris
	 * @param uv_norm
	 * @param tag
	 */
	public _Polygon(int ppCol, PVector[] verts, PVector normal, int[] tris, UV[] uv_norm, String tag) {
		super(ppCol, tag);
		this.normal = normal;
		this.coord = verts;
		this.uvNorm = uv_norm;
		this.uv = Util.deepCopy(this.uvNorm);
		this.tr = tris;
//		this.coord = Util.deepCopy(verts);
//		this.uvNorm = Util.deepCopy(uv_norm);
//		this.uv = Util.deepCopy(this.uvNorm);
//		this.tr = Util.deepCopy(tris);
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
		pg.beginShape(TRIANGLES);
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
			for(int tn = 0; tn < tr.length; tn++) {
				pg.normal(normal.x, normal.y, normal.z);
				pg.vertex(coord[tr[tn]].x, coord[tr[tn]].y, coord[tr[tn]].z, uv[tr[tn]].u, uv[tr[tn]].v);
			}			
		}
		else {
			for(int tn = 0; tn < tr.length; tn++) {
				pg.normal(normal.x, normal.y, normal.z);
				pg.vertex(coord[tr[tn]].x, coord[tr[tn]].y, coord[tr[tn]].z);
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

	/**
	 * Draw this part on to a graphics context
	 * @param pg the pick buffer graphics context
	 */
	@Override
	public void drawPickBuffer(PGraphics pg) {
		pg.beginShape(TRIANGLES);
		pg.fill(partPickColor);
		for(int tn = 0; tn < tr.length; tn++) {
			pg.vertex(coord[tr[tn]].x, coord[tr[tn]].y, coord[tr[tn]].z);
		}			
		pg.endShape();
	}

}
