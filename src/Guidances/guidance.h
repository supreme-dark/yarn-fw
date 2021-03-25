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
    void start(quiver& subject);
    void pause();
    void once(quiver& subject);
    ~guidance();

  private:
    const taskPtr _task;
    bool run;
    std::thread taskThread;

};

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