/*
* guidance: class guidance base
* SdtElectronics 2021.3
*/

#pragma once
#include <thread>
#include <mutex>

#include "../quiver.h"

class guidance{
  public:
    using taskPtr = void(guidance::*)(quiver&);
    guidance(taskPtr task);
    //Start looping task process
    void start(quiver& subject);
    //Pause task process loop
    void pause();
    // Run task process once
    void once(quiver& subject);
    inline void waitFinish();
    ~guidance();

  private:
    //Pointer to task process
    //Initialize during derived class construction
    const taskPtr _task;
    bool run;
    std::thread taskThread;

};

void guidance::waitFinish(){
    taskThread.join();
}

//The activation of asyncGuidance is deferred 
//until a specific event is triggered.
//A signal indicating the activation 
//can be waited by the main thread
//and sequential scheduling of guidances
//can thereby be accomplished.
class asyncGuidance: public guidance{
  public:
    asyncGuidance(taskPtr task);
    void asyncStart(quiver&);

    //Call in main thread
    //Blocks until guidance is started
    inline void waitGuide();

  private:
    std::mutex lock;

    //Call in task thread when guidance is started
    inline void startGuide();
    
};

void asyncGuidance::waitGuide(){
    lock.lock();
    lock.unlock();
}

void asyncGuidance::startGuide(){
    lock.unlock();
}