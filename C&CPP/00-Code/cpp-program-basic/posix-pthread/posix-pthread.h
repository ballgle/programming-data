/*
 ============================================================================
 
 Author      : Ztiany
 Description : posix pthread

 ============================================================================
 */

#ifndef CPLUSPLUS_PROGRAM_POSIX_PTHREAD_H
#define CPLUSPLUS_PROGRAM_POSIX_PTHREAD_H

#include <queue>
#include <mutex>
#include <pthread.h>

class ThreadMutexParams {
public:
    std::queue<int> *queue_;
    pthread_mutex_t *mutex_;

    ThreadMutexParams(std::queue<int> *queue, pthread_mutex_t *mutex) : queue_(queue), mutex_(mutex) {
    }

};


template<typename T>
class SafeQueue {
public:
    SafeQueue() {
        pthread_mutex_init(&mutex, 0);
        pthread_cond_init(&cond, 0);
    }

    ~SafeQueue() {
        pthread_mutex_destroy(&mutex);
        pthread_cond_destroy(&cond);
    }

    //生产 加入数据
    void push(T t) {
        pthread_mutex_lock(&mutex);
        q.push(t);
        //notify
        // 由系统唤醒一个线程 控制不了
        //pthread_cond_signal(&cond);
        // 广播通知所有等待的线程
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }

    // queue为空则一直等待，直到下一次 push 生产出数据
    //消费 取数据
    void pop(T &t) {
        pthread_mutex_lock(&mutex);
        /*if (!q.empty()) {
            t = q.front();
            q.pop();
        }*/
        //等待其他地方唤醒
        // 可能被系统意外唤醒
        while (q.empty()) {
            // 挂起 释放锁
            pthread_cond_wait(&cond, &mutex);
        }
        //
        t = q.front();
        q.pop();
        pthread_mutex_unlock(&mutex);
    }

private:
    //队列
    std::queue<T> q;
    //互斥锁
    pthread_mutex_t mutex;
    //条件变量
    pthread_cond_t cond;
};

#endif //CPLUSPLUS_PROGRAM_POSIX_PTHREAD_H