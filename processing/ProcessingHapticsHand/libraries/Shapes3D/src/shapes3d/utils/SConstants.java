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

import shapes3d.org.apache.commons.math.geometry.Rotation;
import shapes3d.path.PathOrthogonal;

/**
 * Constants used by the library available to the user.
 * 
 * @author Peter Lager
 *
 */
public interface SConstants {
	int WIRE 	= 0x00000011;
	int SOLID 	= 0x00000012;
	int TEXTURE = 0x00000014;
	int DRAWALL = WIRE | SOLID | TEXTURE;
	
	int WHITE   = 0xFFFFFFFF;
	int BLACK   = 0xFF000000;
	int GREY    = 0xFFC0C0C0;
	int RED     = 0xFFFF0000;
	int GREEN   = 0xFF00FF00;
	int BLUE    = 0xFF0000FF;
	int YELLOW  = 0xFFFFFF00;
	int PURPLE  = 0xFFFF00FF;
	int CYAN    = 0xFF00FFFF;
	int ORANGE  = 0xFFFFC000;
	
	// Contour vertex order i.e. ClockWise or CounterClockWise
	int CW 		= 1;
	int CCW		= 2;
	
	// Flags for parts making up the shape
	int ALL 		= 0b11111111;
	
	int BOTTOM 		= 0b00000001;
	int TOP 		= 0b00000010;
	int FRONT 		= 0b00000100;
	int BACK 		= 0b00001000;
	int LEFT 		= 0b00010000;
	int RIGHT 		= 0b00100000;
	
	int BODY 		= 0b00000001;
	int END0		= 0b00000010;
	int END1		= 0b00000100;
	
	// Delta t used in determining the tangent to a curve
	float ONE_DEG_T = (float) (Math.PI / 180.0);
	
	// Orthoganol calculators
	PathOrthogonal ORTHO_X = new PathOrthogonal.PathNormalX();
	PathOrthogonal ORTHO_Y = new PathOrthogonal.PathNormalY();
	PathOrthogonal ORTHO_Z = new PathOrthogonal.PathNormalZ();
	PathOrthogonal ORTHO_A = new PathOrthogonal.PathNormalAMC();
	
	// UV transformations
	TransformUV ROT_0 	= TransformUV.ROT0;
	TransformUV ROT_90 	= TransformUV.ROT90;
	TransformUV ROT_180 = TransformUV.ROT180;
	TransformUV ROT_270 = TransformUV.ROT270;
	TransformUV FLIP_H 	= TransformUV.FLIPH;
	TransformUV FLIP_V 	= TransformUV.FLIPV;
	
	// Rotation
	Rotation ROTATION_ZERO  = new Rotation();

	int T_BOX 			= 0x1001;
	int T_DOME 			= 0x1002;
	int T_CONE 			= 0x1003;
	int T_ELLIPSOID		= 0x1004;
	int T_EXTRUSION		= 0x1005;
	int T_LATHESTOCK	= 0x1006;
	int T_MD2 			= 0x1007;
	int T_SKYBOX 		= 0x1008;
	int T_SKYDOME 		= 0x1009;
	int T_TERRAIN 		= 0x100A;
	int T_TUBE 			= 0x100B;
	
	
	int C_LATHESURFACE	= 0x2001;
	int C_OVAL			= 0x2002;
	int C_POLYGON		= 0x2003;
	
	int P_BCURVE2D		= 0x3001;
	int P_BCURVE3D		= 0x3002;
	int P_BSPLINE2D		= 0x3003;
	int P_BSPLINE3D		= 0x3004;
	int P_LINEAR		= 0x3005;
	int P_LISSAJOUS		= 0x3006;
	int P_RING			= 0x3007;
	int P_SPIRAL		= 0x3008;

	
}
