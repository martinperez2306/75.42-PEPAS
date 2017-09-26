#ifndef LOCK_H
#define LOCK_H


#include <mutex>

class Lock {
private:
    std::mutex &m;

public:
    explicit Lock(std::mutex  &m);

    ~Lock();
};


#endif //LOCK_H