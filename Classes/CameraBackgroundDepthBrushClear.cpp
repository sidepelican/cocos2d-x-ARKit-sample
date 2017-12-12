#include "CameraBackgroundDepthBrushClear.h"

USING_NS_CC;

CameraBackgroundDepthBrushClear* CameraBackgroundDepthBrushClear::create(float depth)
{
    auto ret = new (std::nothrow) CameraBackgroundDepthBrushClear();
    if (ret && ret->init(depth))
    {
        ret->autorelease();
        return ret;
    }
    else
    {
        delete ret;
        ret = nullptr;
        return nullptr;
    }
}

CameraBackgroundDepthBrushClear::CameraBackgroundDepthBrushClear()
{}

CameraBackgroundDepthBrushClear::~CameraBackgroundDepthBrushClear()
{}

bool CameraBackgroundDepthBrushClear::init(float depth)
{
    if (!CameraBackgroundBrush::init()) return false;

    this->clearDepth = depth;

    return true;
}

void CameraBackgroundDepthBrushClear::drawBackground(cocos2d::Camera* camera)
{
    glDepthMask(true);
    glClearDepth(this->clearDepth);
    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//    glFlush();
    glDepthMask(false);

    cocos2d::RenderState::StateBlock::_defaultState->setDepthWrite(false);
}
