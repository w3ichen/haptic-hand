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

/**
 * A collection of classes used to perform rotations on UV coordinates.
 * 
 * @author Peter Lager
 *
 */
public class TransformUV {
	
	private static TransformUV transformer = new TransformUV();
	
	// Series of constants to define the major transformations
	public static TransformUV ROT0 		= transformer.new Rotate0();
	public static TransformUV ROT90 	= transformer.new Rotate90();
	public static TransformUV ROT180 	= transformer.new Rotate180();
	public static TransformUV ROT270 	= transformer.new Rotate270();
	public static TransformUV FLIPH 	= transformer.new FlipH();
	public static TransformUV FLIPV 	= transformer.new FlipV();
	
	public void transform(final UV baseUV, UV destUV) {};

	/**
	 * Zero rotation - leaves UV coordinates unchanged
	 * @author Peter Lager
	 *
	 */
	public final class Rotate0 extends TransformUV {
		@Override
		public void transform(final UV baseUV, UV destUV) {
			destUV.set(baseUV);
		}
	}
	
	/**
	 * Rotate UV coordinates 90&deg;
	 * @author Peter Lager
	 *
	 */
	public final class Rotate90 extends TransformUV {
		@Override
		public void transform(final UV baseUV, UV destUV) {
			destUV.set(baseUV.v, 1 - baseUV.u);
		}
	}
	
	/**
	 * Rotate UV coordinates 180&deg;
	 * @author Peter Lager
	 *
	 */
	public final class Rotate180 extends TransformUV {
		@Override
		public void transform(final UV baseUV, UV destUV) {
			destUV.set(1 - baseUV.u, 1 - baseUV.v);
		}
	}
	
	/**
	 * Rotate UV coordinates 270&deg;
	 * @author Peter Lager
	 *
	 */
	public final class Rotate270 extends TransformUV {
		@Override
		public void transform(final UV baseUV, UV destUV) {
			destUV.set(1 - baseUV.v, baseUV.u);
		}
	}

	/**
	 * Mirror UV coordinates about horizontal axis
	 * @author Peter Lager
	 *
	 */
	public final class FlipH extends TransformUV {
		@Override
		public void transform(final UV baseUV, UV destUV) {
			destUV.set(1 - baseUV.u, baseUV.v);
		}
	}
	
	/**
	 * Mirror UV coordinates about vertical axis
	 * @author Peter Lager
	 *
	 */
	public final class FlipV extends TransformUV {
		@Override
		public void transform(final UV baseUV, UV destUV) {
			destUV.set(baseUV.u, 1 - baseUV.v);
		}
	}
		
}