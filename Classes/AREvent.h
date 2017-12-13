#ifndef __AREvent__
#define __AREvent__

#include <cocos2d.h>

class AREvent: public cocos2d::EventCustom
{
public:
    static std::string EventName;
    
private:
    cocos2d::Mat4 cameraWorldTransform;
    cocos2d::Mat4 cameraProjectionMatrix;
    
public:
    AREvent(): cocos2d::EventCustom(EventName) {}
    
    void setCameraWorldTransform(const cocos2d::Mat4& m) { cameraWorldTransform = m; }
    cocos2d::Mat4 getCameraWorldTransform() const { return cameraWorldTransform; }
    void setCameraProjectionMatrix(const cocos2d::Mat4& m) { cameraProjectionMatrix = m; }
    cocos2d::Mat4 getCameraProjectionMatrix() const { return cameraProjectionMatrix; }
};

#endif /* __AREvent__ */
