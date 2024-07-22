#ifndef BOUNDED_QUEUE_BLOCKING_H
#define BOUNDED_QUEUE_BLOCKING_H

#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>

struct ClosedQueue: public std::runtime_error {
    ClosedQueue(): std::runtime_error("The queue is closed") {}
};

class BoundedQueueBlocking {
private:
    std::queue<std::string> q;
    const unsigned int max_size;

    bool closed;

    std::mutex mtx;
    std::condition_variable is_not_full;
    std::condition_variable is_not_empty;

public:
    explicit BoundedQueueBlocking(const unsigned int max_size);


    bool try_push(const std::string& val);

    bool try_pop(std::string& val);

    void push(const std::string& val);

    std::string pop();

    void close();

private:
    BoundedQueueBlocking(const BoundedQueueBlocking&) = delete;
    BoundedQueueBlocking& operator=(const BoundedQueueBlocking&) = delete;
};

#endif
