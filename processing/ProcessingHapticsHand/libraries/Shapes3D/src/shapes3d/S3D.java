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
import processing.core.PGraphics;
import shapes3d.utils.Picked;
import shapes3d.utils.SConstants;

/**
* This class is provided to simplify the use of library 
* constants e.g. S3D.TEXTURE <br>
* 
* @author Peter Lager
*
*/
public class S3D implements SConstants {
	private static boolean announced = false;
	
	/**
	 * @return the pretty version of the library.
	 */
	public static String getPrettyVersion() {
		return "3.0";
	}

	/**
	 * @return the version of the library used by Processing
	 */
	public static String getVersion() {
		return "12";
	}

	/**
	 * Display the library version in the ProcessingIDE
	 */
	static void announceShapes3D(){
		if(!announced){
			System.out.println("===================================================");
			System.out.println("   Shapes3D V3.0 created by Peter Lager");
			System.out.println("===================================================");
			announced = true;
		}
	}

	
	public static Picked pick(PApplet app, PGraphics pg, int x, int y){
		return Shape3D.pick(app, pg, x, y);
	}
}
