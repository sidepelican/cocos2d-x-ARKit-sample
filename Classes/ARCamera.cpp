#include "ARCamera.h"

#include "CameraBackgroundDepthBrushClear.h"
#include "AREvent.h"

USING_NS_CC;

namespace
{
    float extractFov(const Mat4& projectionMatrix)
    {
        return CC_RADIANS_TO_DEGREES(2.f * atanf(1.f / projectionMatrix.m[5]));
    }
}

ARCamera::ARCamera()
{
    this->setBackgroundBrush(CameraBackgroundDepthBrushClear::create(1.f));
    
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    eventDispatcher->addCustomEventListener(AREvent::EventName, [this](EventCustom* e){
        if (!this->isRunning()) return;
        auto arEvent = static_cast<AREvent*>(e);
        
        this->updateCameraTransform(arEvent->getCameraWorldTransform(), arEvent->getCameraProjectionMatrix());
    });
}

ARCamera::~ARCamera()
{}

ARCamera* ARCamera::create()
{
    ARCamera* p = new (std::nothrow)ARCamera();
    if (p && p->initDefault()) p->autorelease();
    else CC_SAFE_DELETE(p);
    
    return p;
}

ARCamera* ARCamera::createPerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
    ARCamera* p = new (std::nothrow)ARCamera();
    if (p && p->initPerspective(fieldOfView, aspectRatio, nearPlane, farPlane)) p->autorelease();
    else CC_SAFE_DELETE(p);
    
    return p;
}

void ARCamera::setFieldOfView(float fov)
{
    if (_type == Type::PERSPECTIVE)
    {
        _fieldOfView = fov;
        Mat4::createPerspective(_fieldOfView, _aspectRatio, _nearPlane, _farPlane, &_projection);
        _viewProjectionDirty = true;
        _frustumDirty        = true;
    }
}

void ARCamera::updateCameraTransform(const cocos2d::Mat4& worldTransform, const cocos2d::Mat4& projectionMatrix)
{
    // update world transform
    Vec3 position;
    Quaternion quat;
    
    worldTransform.getTranslation(&position);
    worldTransform.getRotation(&quat);
    
    // find the best world scale ratio between native 3D scene and cocos2d-x 3D scene.
    const Size& winSize = Director::getInstance()->getWinSize();
    const float scale = fmin(winSize.width, winSize.height) * 1.4f;
    this->setPosition3D(position * scale);
    this->setRotationQuat(quat);
    
    // update FOV
    const float fov { extractFov(projectionMatrix) };
    this->setFieldOfView(fov);
}
