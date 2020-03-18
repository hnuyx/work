
/**
 * hl-utils.h
 * utils
 * Henry 2019-05-14
 * */

#ifndef __HL_UTILS_H__
#define __HL_UTILS_H__

#include <mutex>

// auto locker
class HLAutoLocker
{
public:
    HLAutoLocker(std::mutex *_mtx) : mtx(_mtx)
    {
        mtx->lock();
    }

    ~HLAutoLocker()
    {
        mtx->unlock();
    }

private:
    std::mutex *mtx;
};


#endif
