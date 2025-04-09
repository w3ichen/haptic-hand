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
 * A terrain mesh differs from the _Mesh2D and _FlatMesh2D in that you can 
 * specify the XZ position and distance to be rendered.
 *  
 * @author Peter Lager
 *
 */
public class _TerrainMesh2D extends _ShapePart {

	protected PVector[][] coord;
	protected PVector[][] normal;
	protected UV[][] uvNorm;
	protected UV[][] uv;


	protected _TerrainMesh2D(int ppCol, PVector[][] coords, PVector[][] normals, UV[][] uvs) {
		super(ppCol);
		coord = coords; // Don't make a copy want a reference in Terrain
		normal = normals;
		uvNorm = Util.deepCopy(uvs);
		uv = Util.deepCopy(uvNorm);
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

	@Override
	public void draw(PGraphics pg) {
		draw(pg, 0, 0, coord.length - 1, coord.length - 2);
	}


	public void draw(PGraphics pg, int left, int top, int right, int bot) {
		// System.out.println("_TerrainMesh2D : " + "draw(PGraphics pg, int left, int top, int right, int bot)");
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
			for(int row = top; row < bot; row++) {
				pg.beginShape(TRIANGLE_STRIP);
				pg.texture(skin);
				for(int col = left; col <= right; col++) {
					pg.normal(normal[col][row].x, normal[col][row].y, normal[col][row].z);
					pg.vertex(coord[col][row].x, coord[col][row].y, coord[col][row].z, uv[col][row].u, uv[col][row].v);
					pg.normal(normal[col][row+1].x, normal[col][row+1].y, normal[col][row+1].z);
					pg.vertex(coord[col][row+1].x, coord[col][row+1].y, coord[col][row+1].z, uv[col][row+1].u, uv[col][row+1].v);
				}
				pg.endShape();
			}
		}
		else {
			for(int row = top; row < bot; row++) {
				pg.beginShape(TRIANGLE_STRIP);
				for(int col = left; col <= right; col++) {
					pg.normal(normal[col][row].x, normal[col][row].y, normal[col][row].z);
					pg.vertex(coord[col][row].x, coord[col][row].y, coord[col][row].z);
					pg.normal(normal[col][row+1].x, normal[col][row+1].y, normal[col][row+1].z);
					pg.vertex(coord[col][row+1].x, coord[col][row+1].y, coord[col][row+1].z);
				}
				pg.endShape();
			}			
		}
		pg.popStyle();
	}



//	private void drawSurfaceNormals(PGraphics pg, int left, int top, int right, int bot) {
//		pg.stroke(strokeColor);
//		pg.strokeWeight(strokeWeight);
//		pg.hint(DISABLE_OPTIMIZED_STROKE);
//		for(int row = top; row < bot; row++) {
//			for(int col = left; col <= right; col++) {
//				pg.line(coord[col][row].x, coord[col][row].y, coord[col][row].z, 
//						coord[col][row].x + normal[col][row].x, coord[col][row].y + normal[col][row].y, coord[col][row].z + normal[col][row].z);
//			}			
//		}
//	}

	public void drawPickBuffer(PGraphics pg, int left, int top, int right, int bot) {
		pg.fill(partPickColor);
		for(int row = top; row < bot; row++) {
			pg.beginShape(TRIANGLE_STRIP);
			for(int col = left; col <= right; col++) {
				pg.vertex(coord[col][row].x, coord[col][row].y, coord[col][row].z);
				pg.vertex(coord[col][row+1].x, coord[col][row+1].y, coord[col][row+1].z);
			}
			pg.endShape();
		}					
	}

	@Override
	public void drawPickBuffer(PGraphics pg) {
		drawPickBuffer(pg, 0, 0, coord.length - 1, coord.length - 2);
	}

}
