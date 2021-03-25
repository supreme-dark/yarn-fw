#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#include "tracer.h"

tracer::tracer(bool rhs, lightSS& ssLhs, lightSS& ssRhs): 
    guidance(static_cast<guidance::taskPtr>(&tracer::tracerTask)),
    ssl(ssLhs),
    ssr(ssRhs),
    deviation(static_cast<int>(rhs) * devBase){

}

void tracer::tracerTask(quiver& subject){
    
}
