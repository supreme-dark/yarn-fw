#include "guidance.h"

guidance::guidance(taskPtr task): _task(task){

}

void guidance::start(quiver& subject){
    run = true;
    taskThread = std::thread([this](quiver& _subject){
        while(run){
            (this->*_task)(_subject);
        }
    }, subject);
    
}

void guidance::pause(){
    run = false;
}

void guidance::once(quiver& subject){
    taskThread = std::thread([this](quiver& _subject){
            (this->*_task)(_subject);
    }, subject);
}

guidance::~guidance(){
    taskThread.join();
}

asyncGuidance::asyncGuidance(taskPtr task): guidance(task){
    
}

void asyncGuidance::asyncStart(quiver& subject){
    lock.lock();
    start(subject);
}