#ifndef __MemoryUsedMetor__
#define __MemoryUsedMetor__

#include <iostream>
#include "cocos2d.h" 
USING_NS_CC;

class MemoryUsedMetor : public CCLabelTTF {
private:
bool init();
void update(float delta);
double getAvailableBytes();
double getAvailableKiloBytes();
double getAvailableMegaBytes();
public:
CREATE_FUNC(MemoryUsedMetor);
~MemoryUsedMetor();
};

#endif /* defined(__MemoryUsedMetor__) */