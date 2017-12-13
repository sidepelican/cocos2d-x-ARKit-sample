#ifndef __ARHelper__
#define __ARHelper__

#include <cocos2d.h>

class ARHelper
{
public:
    static void showTestTableView();
    static void startARSession();
    static void cameraMatrixUpdated(const cocos2d::Mat4& worldTransform, const cocos2d::Mat4& projection);
    
private:
    ARHelper() = delete;
    ~ARHelper() = delete;
};

#endif /* __ARHelper__ */
