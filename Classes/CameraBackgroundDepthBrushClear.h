#ifndef __CameraBackgroundDepthBrushClear__
#define __CameraBackgroundDepthBrushClear__

#include "cocos2d.h"

class CameraBackgroundDepthBrushClear : public cocos2d::CameraBackgroundBrush
{
public:
    static CameraBackgroundDepthBrushClear* create(float depth);
    
protected:
    float clearDepth { 1.f };

protected:
    CameraBackgroundDepthBrushClear();
    virtual ~CameraBackgroundDepthBrushClear();
    virtual bool init(float depth);

public:
    virtual void drawBackground(cocos2d::Camera* camera) override;
    virtual BrushType getBrushType() const override { return BrushType::DEPTH; }
};

#endif /* defined(__CameraBackgroundDepthBrushClear__) */
