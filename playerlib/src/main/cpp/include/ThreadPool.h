//
// Created by greensun on 2020/4/7.
//

#ifndef LYJPLAYER_THREADPOOL_H
#define LYJPLAYER_THREADPOOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <stdexcept>
#include <logger.h>
#include <SafeQueue.h>

class ThreadPool {
public:
    ThreadPool(size_t);

    void enqueue(std::function<void()> && task);

    ~ThreadPool();

private:
    // need to keep track of threads so we can join them
    std::vector <std::thread> workers;
    // the task queue
    std::queue <std::function<void()>> tasks;

    // synchronization
    std::mutex queue_mutex;
    std::condition_variable condition;
    atomic_bool stop = {false};
};
#endif //LYJPLAYER_THREADPOOL_H
