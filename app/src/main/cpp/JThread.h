//
// Created by jinsn on 2022/8/21.
//

#ifndef GODMYC_JTHREAD_H
#define GODMYC_JTHREAD_H

#include <thread>
#include <mutex>
#include <chrono>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std::chrono_literals;

class JThread { //header only
public:

    virtual void run() = 0; //thread running logic
    int stop();  //release reources
    int start();
public:
    std::thread *t = nullptr;
    int stopFlag = 0;
};

int JThread::stop() { //called from any thread , stop this thread
    if (t != nullptr) {
        stopFlag = 1;
        t->join();
        delete t;
        t = nullptr;
    }
    return 0;
}

int JThread::start() {
    if (t == nullptr) {
        stopFlag = 0;
        t = new std::thread(&JThread::run, this);
    }
    return 0;
}

namespace SAMPLE {
    class SampleThread : public JThread {
    public:
        SampleThread() {};
        std::string m_params;
        std::mutex mutexForControl; //mutex for synchronization , so it works as if these code are queued
        void run() override {
            int count = 0;
            while (!stopFlag) {
                count++;
                std::this_thread::sleep_for(10s);
                //do some work;
                if (count >= 10) {
                    break;
                }
            }
        };

        void start(std::string &&params) {
            std::lock_guard<std::mutex> lockGuard(mutexForControl);
            m_params = std::forward<std::string>(params); //在 线程一次 start 到一次stop 都使用这个参数。
            JThread::start();
        };

        void stop() {
            std::lock_guard<std::mutex> lockGuard(mutexForControl);
            JThread::stop();
        };
    };


}


#endif //GODMYC_JTHREAD_H
