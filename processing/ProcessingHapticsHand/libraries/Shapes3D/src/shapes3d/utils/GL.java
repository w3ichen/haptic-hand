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

package shapes3d.utils;

import processing.core.PGraphics;
import processing.opengl.PGraphicsOpenGL;

/**
 * Some experimental methods to control face culling. I havn't got
 * them to work in Processing yet.
 * 
 * @author Peter Lager
 *
 */
public class GL {

	public final static boolean GL_FALSE		= false;
	public final static boolean GL_TRUE			= true;

	/* FrontFaceDirection */
	public final static int GL_CW				= 0x0900;
	public final static int GL_CCW				= 0x0901; // Default

	/* CullFaceMode */
	public final static int GL_FRONT			= 0x0404;
	public final static int GL_BACK				= 0x0405;
	public final static int GL_FRONT_AND_BACK	= 0x0408;

	/* EnableCapability */
	public final static int GL_CULL_FACE		= 0x0B44;


	/**
	 * Controls how front-facing polygons are determined. By default, 
	 * mode is GL_CCW, which corresponds to a counterclockwise 
	 * orientation of the ordered vertices of a projected polygon in
	 * window coordinates. If mode is GL_CW, faces with a clockwise 
	 * orientation are considered front-facing.
	 * 
	 * @param pg the OpenGL drawing surface
	 * @param mode either GL_CCW or GL_CW
	 */
	public static void frontFace(PGraphics pg, int mode) {
		if(pg.isGL())
			((PGraphicsOpenGL)pg).pgl.frontFace(mode);
	}

	/**
	 * Indicates which polygons should be discarded (culled) before 
	 * they are converted to screen coordinates. The mode is either
	 * GL_FRONT, GL_BACK, or G_FRONT_AND_BACK to indicate front-facing,
	 * back-facing or all polygons. Culling can be enabled / disabled 
	 * with the glEnable(boolean) or glDisable(boolean) methods.
	 * @param pg the OpenGL drawing surface
	 * @param mode GL_TRUE or GL_FALSE
	 */
	public static void cullFace(PGraphics pg, int mode) {
		if(pg.isGL())
			((PGraphicsOpenGL)pg).pgl.cullFace(mode);
	}

	/**
	 * 
	 * @param pg the OpenGL drawing surface
	 * @param cap capability
	 */
	public static void enable(PGraphics pg, int cap) {
		if(pg.isGL())
			((PGraphicsOpenGL)pg).pgl.enable(cap);
	}

	/**
	 * 
	 * @param pg the OpenGL drawing surface
	 * @param cap capability
	 */
	public static void disable(PGraphics pg, int cap) {
		if(pg.isGL())
			((PGraphicsOpenGL)pg).pgl.disable(cap);
	}
}
