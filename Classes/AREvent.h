#ifndef __AREvent__
#define __AREvent__

#include <cocos2d.h>

class AREvent: public cocos2d::EventCustom
{
public:
    static std::string EventName;
    
    CREATE_FUNC(AREvent);
    
private:
    cocos2d::Mat4 cameraWorldTransform { cocos2d::Mat4::IDENTITY };
    cocos2d::Mat4 cameraProjectionMatrix { cocos2d::Mat4::IDENTITY };
    
public:
    AREvent(): cocos2d::EventCustom(EventName) {}
    bool init() { return true; }
    
    void dispatchOnCocosThread();
    void scheduleHandler(float);
    
    void setCameraWorldTransform(const cocos2d::Mat4& m) { cameraWorldTransform = m; }
    cocos2d::Mat4 getCameraWorldTransform() const { return cameraWorldTransform; }
    void setCameraProjectionMatrix(const cocos2d::Mat4& m) { cameraProjectionMatrix = m; }
    cocos2d::Mat4 getCameraProjectionMatrix() const { return cameraProjectionMatrix; }
};

#endif /* __AREvent__ */
