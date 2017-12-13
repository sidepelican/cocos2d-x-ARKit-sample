#ifndef __ARKitHelper__
#define __ARKitHelper__

#import <Foundation/Foundation.h>
#import <SceneKit/SceneKit.h>

@interface ARKitHelper: NSObject
+ (void) cameraMatrixUpdated: (SCNMatrix4) worldTransform projection:(SCNMatrix4) projection;
@end

#endif /* __ARKitHelper__ */
