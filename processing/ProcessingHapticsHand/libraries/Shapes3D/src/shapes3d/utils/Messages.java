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

import java.text.MessageFormat;
import java.util.Locale;

/**
 * Simple class to display messages from the library
 * 
 * @author Peter Lager
 *
 */
public class Messages {

	
	public static String build(String pattern, Object ... arguments){
		return (pattern == null) ? "" : new MessageFormat(pattern, Locale.UK).format(arguments);        
	}
	
	public static String println(String pattern, Object ... arguments){
		String s = build(pattern, arguments);
		System.out.println(s);
		return s;
	}
	
	/**
	 * Unable to find the user defined pick event handler method.
	 * 
	 * info[0] event generator class
	 * info[1] event handling method name
	 * info[2] the parameter class names
	 * 
	 * @param info error message details
	 * @return error message
	 */
	public static String nonexistantEventHandler(Object[] info) {
		String className = info[0].getClass().getSimpleName();
		String methodName = (String) info[1];
		StringBuilder output = new StringBuilder();

		output.append("The "+className+" class cannot find this method \n");
		output.append("\tpublic void " + methodName + "(Shape3D shape, int partNo, int partFlag) { /* code */ }\n");
		System.out.println(output);
		return output.toString();
	}

	/**
	 * Error message when an exception is create inside a pick event handler.
	 * 
	 * info[0] event generator class
	 * info[1] event handling method name
	 * info[2] the exception thrown
	 * @param info error message details
	 * @return error message
	 */
	public static String eventHandlerFailed(Object[] info) {
		String className = info[0].getClass().getSimpleName();
		String methodName = (String) info[1];
		Exception e = (Exception) info[2];
		Throwable t = e.getCause();
		StackTraceElement[] calls = t.getStackTrace();
		StringBuilder output = new StringBuilder();
		output.append("#############  EXCEPTION IN PICK EVENT HANDLER  ##############");
		output.append("\nAn error occured during execution of the pick event handler:");
		output.append("\nCLASS: "+className+"   METHOD: "+methodName);
		output.append("\n\tCaused by " + t.toString());
		for(Object line : calls)
			output.append("\n\t"+ line.toString());			
		output.append("\n##############################################################\n");
		System.out.println(output);
		return output.toString();
	}
	
}
