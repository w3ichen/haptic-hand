#include "mbed.h"
#include <cmath>    // For mathematical functions
#include <cstdio>   // For sprintf

// Define M_PI if not defined
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

// Serial communication - use the correct pins for Nucleo
mbed::BufferedSerial pc(USBTX, USBRX);  // Remove baud rate from constructor

void sendSimulatedData() {
    float time = 0.0f;
    const float period = 2.0f;
    
    while(1) {
        float t = time / period;
        t = t - floor(t);  // Alternative to fmod for normalized time
        
        // Simulate thumb movement
        float thumb_x = 50.0f * cos(2.0f * M_PI * t);
        float thumb_y = 50.0f * sin(2.0f * M_PI * t);
        float thumb_z = 20.0f;
        
        // Simulate index finger movement
        float index_x = 40.0f * cos(2.0f * M_PI * t + M_PI/3);
        float index_y = 40.0f * sin(2.0f * M_PI * t + M_PI/3);
        float index_z = 15.0f;
        
        // Simulate middle finger movement
        float middle_x = 30.0f * cos(2.0f * M_PI * t + 2*M_PI/3);
        float middle_y = 30.0f * sin(2.0f * M_PI * t + 2*M_PI/3);
        float middle_z = 10.0f;
        
        // Simulate object position
        float object_x = 25.0f * cos(2.0f * M_PI * t);
        float object_y = 15.0f * sin(4.0f * M_PI * t);
        float object_z = 0.0f;
        float object_radius = 10.0f;
        
        // Format and send the data
        char buffer[200];
        sprintf(buffer, "%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\t%.2f\n",
                thumb_x, thumb_y, thumb_z,
                index_x, index_y, index_z,
                middle_x, middle_y, middle_z,
                object_x, object_y, object_z,
                object_radius);
        
        pc.write(buffer, strlen(buffer));
        
        // Wait for acknowledgment
        char ack;
        while(pc.readable()) {
            pc.read(&ack, 1);
            if(ack == '1') break;
        }
        
        ThisThread::sleep_for(20ms);  // 20ms delay
        time += 0.02f;
    }
}

int main() {
    // Initialize serial communication
    pc.set_baud(115200);
    
    // Wait for system to stabilize
    ThisThread::sleep_for(1000ms);  // Wait 1 second
    
    // Start sending simulated data
    sendSimulatedData();
    
    return 0;
} 