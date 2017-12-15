#ifndef __ARHelper__
#define __ARHelper__

#include <cocos2d.h>

class ARHelper
{
private:
    static bool isAvailable();
    static void startARSession();
    static void closeARSession();
    static void hitTest(const cocos2d::Vec2& worldPosition);
    
public:
    static void cameraMatrixUpdated(const cocos2d::Mat4& worldTransform, const cocos2d::Mat4& projection);
    
private:
    ARHelper() = delete;
    ~ARHelper() = delete;
    
public:
    friend class ARManager;
};

#endif /* __ARHelper__ */
