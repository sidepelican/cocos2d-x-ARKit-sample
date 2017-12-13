#include "HelloWorldScene.h"

#include "ARCamera.h"
#include "ARHelper.h"
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

    // setup camera
    auto camera = ARCamera::createPerspective(60, visibleSize.width/visibleSize.height, .1f, 1000.f);
    camera->setDepth(0);
    camera->setPosition3D({ 0.f, 150.f, 250.f });
    camera->setCameraFlag(CameraFlag::USER1);
    this->addChild(camera);
    
    camera->lookAt(Vec3::UNIT_Y * 100.f);
    
    // setup 3D objects
    auto human = Sprite3D::create("girl.c3b");
    human->setCameraMask(static_cast<int>(CameraFlag::USER1));
    this->addChild(human);
    this->human = human;
    
    if (auto animation = Animation3D::create("girl.c3b", "Take 001"))
    {
        auto animate = Animate3D::create(animation);
        human->runAction(RepeatForever::create(animate));
    }
    
    auto floor = Sprite::create("HelloWorld.png");
    floor->setRotation3D({ -90.f, 0.f, 0.f });
    floor->setCameraMask(static_cast<int>(CameraFlag::USER1));
    human->addChild(floor);
    
    // setup touch event
    auto t = EventListenerTouchOneByOne::create();
    t->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    t->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    t->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(t, this);
    
    // set background native view
    ARHelper::startARSession();
    
    return true;
}

bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    ARHelper::hitTest(touch->getLocation());
    
    return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    const float movedDistanceSq = touch->getLocation().distanceSquared(touch->getStartLocation());
    constexpr float startRotationThresholdSq = 10.f * 10.f;
    if (movedDistanceSq > startRotationThresholdSq)
    {
        Vec3 newRotation { this->human->getRotation3D() };
        newRotation.y += touch->getDelta().x;
        this->human->setRotation3D(newRotation);
    }
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
}
