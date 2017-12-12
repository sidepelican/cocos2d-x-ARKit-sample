#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

bool HelloWorld::init()
{
    if (!Scene::init()) return false;

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    auto camera = Camera::createPerspective(60, visibleSize.width/visibleSize.height, .1f, 1000.f);
    camera->setBackgroundBrush(CameraBackgroundColorBrush::create({ .176f, .522f, .937f, 1.f }, 1.f));
    camera->setPosition3D({ 0.f, 150.f, 250.f });
    camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(camera);
    
    auto human = Sprite3D::create("girl.c3b");
    human->setCameraMask(static_cast<int>(CameraFlag::USER1));
    this->addChild(human);
    
    if (auto animation = Animation3D::create("girl.c3b", "Take 001"))
    {
        auto animate = Animate3D::create(animation);
        human->runAction(RepeatForever::create(animate));
    }
    
    auto floor = Sprite::create("HelloWorld.png");
    floor->setRotation3D({ -90.f, 0.f, 0.f });
    floor->setCameraMask(static_cast<int>(CameraFlag::USER1));
    human->addChild(floor);
    
    camera->lookAt(Vec3::UNIT_Y * 100.f);
    
    return true;
}
