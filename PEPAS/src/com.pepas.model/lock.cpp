 #include "../../headers/com.pepas.model/lock.h"

Lock::Lock(std::mutex &m) : m(m){
    m.lock();
}

Lock::~Lock() {
    m.unlock();
}