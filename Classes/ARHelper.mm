#include "ARHelper.h"

#include "ARManager.h"
#include "AREvent.h"

#import <ARKit/ARKit.h>
#import "arkit_sample_mobile-Swift.h"
#import "platform/ios/CCEAGLView-ios.h"

USING_NS_CC;

namespace
{
    UIViewController* findARViewController()
    {
        if (@available(iOS 11.0, *)) {
            UIViewController* rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
            for (UIViewController* vc in rootViewController.childViewControllers)
            {
                if ([vc isKindOfClass: [ARViewController class]])
                {
                    return vc;
                }
            }
        }
        
        return nil;
    }
}

bool ARHelper::isAvailable()
{
    if (@available(iOS 11.0, *))
    {
        return [ARWorldTrackingConfiguration isSupported];
    }
    
    return false;
}

void ARHelper::startARSession()
{
    if (@available(iOS 11.0, *))
    {
        // enable alpha blending
        CCEAGLView* eaglview = (__bridge CCEAGLView*)Director::getInstance()->getOpenGLView()->getEAGLView();
        eaglview.opaque = NO;
        
        UIViewController* rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
        
        // insert ARViewController behind the cocos view
        ARViewController* arvc = [[ARViewController alloc] init];
        [rootViewController addChildViewController: arvc];
        [rootViewController.view addSubview: arvc.view];
        [rootViewController.view bringSubviewToFront: eaglview];
    }
}

void ARHelper::closeARSession()
{
    if (@available(iOS 11.0, *))
    {
        ARViewController* ar = (__bridge ARViewController*)findARViewController();
        if (!ar) return;
        
        [ar.view removeFromSuperview];
        [ar removeFromParentViewController];
        
        // disable alpha blending
        CCEAGLView* eaglview = (__bridge CCEAGLView*)Director::getInstance()->getOpenGLView()->getEAGLView();
        eaglview.opaque = NO;
    }
}

void ARHelper::hitTest(const Vec2& worldPosition)
{
    if (@available(iOS 11.0, *))
    {
        ARViewController* ar = (__bridge ARViewController*)findARViewController();
        if (!ar) return;
        
        // normalize
        CGPoint pos = CGPointMake(worldPosition.x, worldPosition.y);
        pos.x /= Director::getInstance()->getWinSize().width;
        pos.y /= Director::getInstance()->getWinSize().height;
        
        [ar hitTestWithGlNormalizedPoint: pos];
    }
}

void ARHelper::cameraMatrixUpdated(const Mat4& worldTransform, const Mat4& projection)
{
    // NOTICE: this function called async with cocos thread.
    auto event = ARManager::getInstance()->getEvent();
    event->setCameraWorldTransform(worldTransform);
    event->setCameraProjectionMatrix(projection);
}
