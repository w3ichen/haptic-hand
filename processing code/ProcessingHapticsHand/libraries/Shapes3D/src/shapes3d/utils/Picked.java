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

import shapes3d.Shape3D;

/**
 * A simple immutable class to record the shape and part number returned by
 * the Shape3D.pick(...) method. <br>
 * It has 3 public attributes <br>
 * shape3d - the object reference for the picked shape <br>
 * part - the picked part number i.e. 0,1,2,3,..,7 depending on number of shape parts <br>
 * partFlag - the bit flag for the picked part 1,2,4,8,..,128 <br>
 * Note: partFlag = 1 &lt;&lt; part <br><br>
 * 
 * Objects of this class have natural ordering so when sorting the results of a marquee 
 * selection Picked objects are grouped by shape and then ordered by part number. <br>
 * 
 * @author Peter Lager
 */
public final class Picked implements Comparable<Picked> {

	public final Shape3D shape;
	public final int part;
	public final int partFlag;

	/**
	 * Create an instance of Picked that can be returned to the user
	 * @param shape the picked shape
	 * @param part the part picked (0,1,2,3,..,7 depending on number of shape parts)
	 * @param partFlag the bit mask used to identify the picked part (1,2,4,8,..,128 depending on number of shape parts)
	 */
	public Picked(Shape3D shape, int part, int partFlag) {
		super();
		this.shape = shape;
		this.part = part;
		this.partFlag = partFlag;				
	}

	@Override
	public boolean equals(Object o) {
		if (o == this) {
			return true;
		}
		if(!(o instanceof Picked)) {
			return false;
		}
		Picked p = (Picked) o;
		return(p.shape == shape && p.part == part);
	}
	
	@Override
	public int hashCode() {
		int result = 17;
		result = 31 * result + part;
		result = 31 * result + shape.hashCode();
		return result;
	}

	@Override
	public int compareTo(Picked o) {
		long shc = shape.hashCode();
		long oshc = o.shape.hashCode();
		if(shc != oshc ) { // Different shapes
			return shc < oshc ? -1 : 1;
		}
		// Same shapes so compar part numbers
		if(part == o.part) {
			return 0;
		}
		// Same shape different parts
		return part < o.part ? -1 : 1;
	}

}