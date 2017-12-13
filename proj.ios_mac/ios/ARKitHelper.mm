#include "ARKitHelper.h"

#include <cocos2d.h>
#include "ARHelper.h"

USING_NS_CC;

@implementation ARKitHelper

+ (void) cameraMatrixUpdated: (SCNMatrix4) worldTransform projection:(SCNMatrix4) projection {
    Mat4 cocosWorldTransform { SCNMatrix4ToGLKMatrix4(worldTransform).m };
    Mat4 cocosProjection { SCNMatrix4ToGLKMatrix4(projection).m };
    
    ARHelper::cameraMatrixUpdated(cocosWorldTransform, cocosProjection);
}

@end
