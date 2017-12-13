#ifndef __ARHelper__
#define __ARHelper__

#include <cocos2d.h>

class ARHelper
{
public:
    static bool isAvailable();
    static void showTestTableView();
    static void startARSession();
    static void cameraMatrixUpdated(const cocos2d::Mat4& worldTransform, const cocos2d::Mat4& projection);
    static void hitTest(const cocos2d::Vec2& worldPosition);
    
private:
    ARHelper() = delete;
    ~ARHelper() = delete;
};

#endif /* __ARHelper__ */
