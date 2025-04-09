/*
 * Copyright (c) 2019 Peter Lager
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

import java.io.IOException;
import java.util.logging.FileHandler;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;

/**
 * Usage
 Log.logger().info(...)
 etc.
 * 
 * @author Peter Lager
 */
public class Log {
    
    private static Log instance = null;

    public static Logger logger() {
        if (instance == null) {
            instance = new Log();
        }
        return instance.logger;
    }
 
    // ====================================================================
    
    private final Logger logger;

    private Log(){
            logger = Logger.getLogger(this.getClass().getName());
            logger.setLevel(Level.INFO);
            //  false = don't use console output
            logger.setUseParentHandlers(false);
            // This block configures the logger with handler and formatter  
            FileHandler fh;
            try {
                fh = new FileHandler("/Users/peter/data-log.txt");
                logger.addHandler(fh);
                SimpleFormatter formatter = new SimpleFormatter();
                fh.setFormatter(formatter);
            } catch (SecurityException | IOException e) {
                System.err.println("####  Unable to create data logger  ####");
            }
    }
 
}
