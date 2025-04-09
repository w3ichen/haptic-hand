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

import processing.core.PApplet;

/**
 * Simple timer class to measure elapsed time. <br>
 * 
 * The main method for getting the elapsed time  is -
 * <pre>public float elapsedTime() </pre>
 * but this method behaves differently depending on which constructor 
 * is used. <br>
 * <b>MANUAL MODE</b><br>
 * If created using the default constructor (i.e. the one without parameters)
 * then the method will return the time since it was last called. So can be used
 * to measure the elapsed time between any events e.g. between mouse clicks. It 
 * can also be used to measure how long something takes to perform some code e.g.
 * <pre>
 * void aMethod(){
 *   int_timer.elapsedTime(); // don't need to store time now
 *   // some lengthy code here perhaps
 *   float t = int_timer.elapsedTime(); // t = time to perform the action
 * }
 * </pre><br>
 * <b>AUTO MODE</b><br>
 * If you use pass a PApplet object to the constructor then the method will 
 * always return the time between the current frame and the previous frame, 
 * no matter how many times it is called.
 * 
 * @author Peter Lager
 *
 */
final public class IntervalTimer {

	private PApplet app = null;

	private long last;

	private long runStartTime;
	private float elapsedTime;

	/**
	 * If you use this constructor you will get a simple interval timer that returns
	 * the time between call to elapsedTime().
	 */
	public IntervalTimer(){
		reset();
	}

	/**
	 * You must use this constructor
	 * Using this constructor means that the gameTime and elapsedTime are 
	 * automatically updated for you just before the draw method is called.
	 * So there is no need for you to call the setLapTime() method.
	 * 
	 * @param papp the PApplet object
	 */
	public IntervalTimer(PApplet papp){
		reset();
		app = papp;
		app.registerMethod("pre", this);
	}

	public void pre(){
		update();
	}

	public void turnOffAuto() {
		if(app != null) {
			app.unregisterMethod("pre", this);
		}
	}

	/**
	 * In AUTO mode this is called for you just before the draw() method is 
	 * executed. So it will measure the elapsed time between frames. To mesure
	 * the elapsed time between frames in MANUAL mode at the start of the draw 
	 * method so if you have a timer object called <pre>inet_timer</pre> then 
	 * at the at the start of the draw() method you update the timer with <br>
	 * <pre>int_timer.update();</pre> <br>
	 * and get the inter-frame time with <br>
	 * <pre>int_timer.elapsedTime();</pre> <br>
	 */  
	public void update(){
		long ct = System.currentTimeMillis();
		elapsedTime = (ct - last)/1000.0f;
		last = ct;    
	}
	
	/**
	 * Get the elapsed time appropriate for the timer mode.
	 * 
	 * @return time in seconds
	 */
	public float elapsedTime(){
		if(app == null) {
			update();
		}
		return elapsedTime;
	}

	/**
	 * Get the time since the timer was created/reset
	 * @return time in seconds
	 */
	public float runTime(){
		return (System.currentTimeMillis() - runStartTime)/1000.0f;
	}

	/**
	 * Reset the clock. <br>
	 */
	public void reset(){
		runStartTime = System.currentTimeMillis();
		last = runStartTime;
	}

}