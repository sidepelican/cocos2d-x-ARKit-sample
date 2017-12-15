#include "ARManager.h"

#include "ARHelper.h"

USING_NS_CC;

ARManager* ARManager::getInstance()
{
    static ARManager *shared = nullptr;
    if (!shared)
    {
        shared = new (std::nothrow) ARManager;
    }
    return shared;
}

void ARManager::update(float)
{
    if (this->event && !this->event->getCameraProjectionMatrix().isIdentity())
    {
        Director::getInstance()->getEventDispatcher()->dispatchEvent(this->event);
    }
}

AREvent* ARManager::getEvent() const
{
    return this->event;
}

bool ARManager::isAvailable()
{
    return ARHelper::isAvailable();
}

void ARManager::startARSession()
{
    if (!this->event)
    {
        this->event = AREvent::create();
    }
    
    ARHelper::startARSession();
    
    Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

void ARManager::closeARSession()
{
    Director::getInstance()->getScheduler()->unscheduleUpdate(this);
    
    ARHelper::closeARSession();
    
    this->event.reset();
}

void ARManager::hitTest(const Vec2& worldPosition)
{
    ARHelper::hitTest(worldPosition);
}
