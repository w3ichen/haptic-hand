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
 * Unlike its parent class this represents a flat mesh. The Box class uses
 * a flat mesh for each of its 6 sides.
 * 
 * @author Peter Lager
 *
 */
public class _FlatMesh2D extends _Mesh2D{

	protected PVector normal;

	public _FlatMesh2D(int ppCol, PVector[][] coords, PVector normal, UV[][] uv_norm) {
		this(ppCol, coords, normal, uv_norm, "Flat mesh part");
	}

	public _FlatMesh2D(int ppCol, PVector[][] coords, PVector normal, UV[][] uv_norm, String tag) {
		super(ppCol, tag);
		this.coord = coords;
		uvNorm = Util.deepCopy(uv_norm);
		uv = Util.deepCopy(uv_norm);
		applyUV();
		this.normal = normal;
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
					pg.normal(normal.x, normal.y, normal.z);
					pg.vertex(coord[col][row].x, coord[col][row].y, coord[col][row].z, uv[col][row].u, uv[col][row].v);
					pg.normal(normal.x, normal.y, normal.z);
					pg.vertex(coord[col+1][row].x, coord[col+1][row].y, coord[col+1][row].z, uv[col+1][row].u, uv[col+1][row].v);
				}
				pg.endShape();
			}
		}
		else {
			for(int col = 0; col < coord.length - 1; col++) {
				pg.beginShape(QUAD_STRIP);
				for(int row = 0; row < coord[col].length; row++) {
					pg.normal(normal.x, normal.y, normal.z);
					pg.vertex(coord[col][row].x, coord[col][row].y, coord[col][row].z);
					pg.normal(normal.x, normal.y, normal.z);
					pg.vertex(coord[col+1][row].x, coord[col+1][row].y, coord[col+1][row].z);
				}
				pg.endShape();
			}			
		}
		// Uncomment next line to draw surface normals
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
						coord[col][row].x + Shape3D.normal_length * normal.x, 
						coord[col][row].y + Shape3D.normal_length * normal.y, 
						coord[col][row].z + Shape3D.normal_length * normal.z);
			}			
		}
	}
	
	/**
	 * Draw this part on to a graphics context
	 * @param pg the pick buffer graphics context
	 */
	public void drawPickBuffer(PGraphics pg) {
		int ncols = coord.length;
		int nrows = coord[0].length;
		pg.beginShape(QUADS);
		pg.fill(partPickColor);
		pg.vertex(coord[0][0].x, coord[0][0].y, coord[0][0].z);
		pg.vertex(coord[0][nrows-1].x, coord[0][nrows-1].y, coord[0][nrows-1].z);
		pg.vertex(coord[ncols-1][nrows-1].x, coord[ncols-1][nrows-1].y, coord[ncols-1][nrows-1].z);
		pg.vertex(coord[ncols-1][0].x, coord[ncols-1][0].y, coord[ncols-1][0].z);			
		pg.endShape();
	}

	/**
	 * By default this shape part is a single QUAD but this method can be used to 
	 * create a grid of QUADs which would be needed for some atexture animations.
	 * 
	 * @param nbrColSlices number of slices
	 * @param nbrRowSlices number of slices in orthogonal direction
	 * @return this shape part
	 */
	public _ShapePart mesh(int nbrColSlices, int nbrRowSlices) {
		int ncols = coord.length;
		int nrows = coord[0].length;
		int _ncols = nbrColSlices + 1;
		int _nrows = nbrRowSlices + 1;
		// There is no point continuing if we are not changing the mesh size.
		if(_ncols == ncols && _nrows == nrows) {
			return this;
		}
		PVector[][] _coord = new PVector[_ncols][_nrows];
		// Copy 4 corners from original coordinates
		_coord[0][0] = coord[0][0].copy();
		_coord[_ncols-1][0] = coord[ncols-1][0].copy();
		_coord[0][_nrows-1] = coord[0][nrows - 1].copy();
		_coord[_ncols-1][_nrows-1] = coord[ncols-1][nrows - 1].copy();
		PVector diff;
		// Calculate col = [0]
		diff = PVector.sub(_coord[0][_nrows-1], _coord[0][0]);
		diff.div(nbrRowSlices);
		for(int row = 1; row < _nrows; row++) {
			_coord[0][row] = PVector.add(_coord[0][0], PVector.mult(diff, row));
		}
		// Calculate col = [ncols-1]
		diff = PVector.sub(_coord[_ncols-1][_nrows-1], _coord[_ncols-1][0]);
		diff.div(nbrRowSlices);
		for(int row = 1; row < _nrows; row++) {
			_coord[_ncols - 1][row] = PVector.add(_coord[_ncols-1][0], PVector.mult(diff, row));
		}
		// Calc col = [1] to [_ncols-2]
		for(int col = 1; col < _ncols-1; col++) {
			for(int row = 0; row < _nrows; row++) {
				diff = PVector.sub(_coord[_ncols-1][row], _coord[0][row]);
				diff.div(nbrColSlices);
				_coord[col][row] = PVector.add(_coord[0][row], PVector.mult(diff, col));
			}
		}
		float widthCol = 1.0f / nbrColSlices;
		float widthRow = 1.0f / nbrRowSlices;
		UV[][] _uv = new UV[_ncols][_nrows];
		for(int col = 0; col < _ncols; col++) {
			for(int row = 0; row < _nrows; row++) {
				_uv[col][row] = new UV(col * widthCol, row * widthRow);
			}
		}
		coord = _coord;
		uvNorm = _uv;
		uv = Util.deepCopy(_uv);
		applyUV();
		return this;
	}

}
