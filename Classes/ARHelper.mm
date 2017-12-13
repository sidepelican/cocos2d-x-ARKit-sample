#include "ARHelper.h"

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

void ARHelper::showTestTableView()
{
    // enable alpha blending
    CCEAGLView* eaglview = (__bridge CCEAGLView*)Director::getInstance()->getOpenGLView()->getEAGLView();
    eaglview.opaque = NO;
    
    UIViewController* rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
    
    // insert tableView behind the cocos view
    TableViewController* vc = [[TableViewController alloc] init];
    [rootViewController addChildViewController: vc];
    [rootViewController.view addSubview: vc.view];
    [rootViewController.view bringSubviewToFront: eaglview];
}

void ARHelper::startARSession()
{
    if (@available(iOS 11.0, *))
    {
        // enable alpha blending
        CCEAGLView* eaglview = (__bridge CCEAGLView*)Director::getInstance()->getOpenGLView()->getEAGLView();
        eaglview.opaque = NO;
        
        UIViewController* rootViewController = [UIApplication sharedApplication].keyWindow.rootViewController;
        
        // insert tableView behind the cocos view
        ARViewController* arvc = [[ARViewController alloc] init];
        [rootViewController addChildViewController: arvc];
        [rootViewController.view addSubview: arvc.view];
        [rootViewController.view bringSubviewToFront: eaglview];
    }
}

void ARHelper::cameraMatrixUpdated(const Mat4& worldTransform, const Mat4& projection)
{
    auto eventDispatcher = Director::getInstance()->getEventDispatcher();
    
    auto event = AREvent();
    event.setCameraWorldTransform(worldTransform);
    event.setCameraProjectionMatrix(projection);
    
    eventDispatcher->dispatchEvent(&event);
}

void ARHelper::hitTest(const Vec2& worldPosition)
{
    if (@available(iOS 11.0, *))
    {
        ARViewController* ar = (ARViewController*)findARViewController();
        if (!ar) return;
        
        // normalize
        CGPoint pos = CGPointMake(worldPosition.x, worldPosition.y);
        pos.x /= Director::getInstance()->getWinSize().width;
        pos.y /= Director::getInstance()->getWinSize().height;
        
        [ar hitTestWithGlNormalizedPoint: pos];
    }
}
