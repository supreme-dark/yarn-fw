#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <vector>

#include "tracer.h"

tracer::tracer(bool rhs, lightSS& sensor, size_t filterLen = 8): 
    guidance(static_cast<guidance::taskPtr>(&tracer::tracerTask)),
    _sensor(sensor),
    filter(filterLen),
    deviation(static_cast<int>(rhs) * devBase),
    deviating(false){
}

void tracer::sCalibrate(quiver& subject){

}

void tracer::tracerTask(quiver& subject){
    unsigned int curSQUAL = _sensor.getSQUAL();
    if(curSQUAL + sRippleMargin > sRippleUL || curSQUAL - sRippleMargin < sRippleLL){
        subject.yaw(deviation);
        deviating = true;
    }else if(deviating == true){
        subject.forth();
        deviating = false;
    }

}
