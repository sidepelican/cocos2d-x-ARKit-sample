#include "ARHelper.h"

#import "arkit_sample_mobile-Swift.h"
#import "platform/ios/CCEAGLView-ios.h"

USING_NS_CC;

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
