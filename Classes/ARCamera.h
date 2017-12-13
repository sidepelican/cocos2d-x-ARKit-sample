#ifndef __ARCamera__
#define __ARCamera__

#include <cocos2d.h>

class ARCamera: public cocos2d::Camera
{
public:
    static ARCamera* createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
    static ARCamera* create();

private:
    ARCamera();
    ~ARCamera();
    
public:
    void setFieldOfView(float fov);
    
private:
    void updateCameraTransform(const cocos2d::Mat4& worldTransform, const cocos2d::Mat4& projectionMatrix);
};

#endif /* __ARCamera__ */
