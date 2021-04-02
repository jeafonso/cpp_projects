#include <string>
#include <cmath>

#include "format.h"

using std::string;

string Format::ElapsedTime(long seconds) { 
  	std::string time = "";
    std::string sHours, sMin, sSec;

    int hours = seconds / 3600;
    if(hours < 10.0){
        sHours = "0" + std::to_string(hours);
    } else {
        sHours = std::to_string(hours);  
    }
    
    int minutes = seconds / 60;
    if(minutes < 10){
        sMin = "0" + std::to_string(minutes);
    } else {
        sMin = std::to_string(minutes);
    }

    int sec = seconds % 3600;
  	sec = sec % 60;

    if(sec < 10){
        sSec = "0" + std::to_string(sec);
    } else {
        sSec = std::to_string(sec);
    }
    
    time = sHours + ":" + sMin + ":" + sSec;
    return time; 

}