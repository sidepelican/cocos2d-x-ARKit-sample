#include "AREvent.h"

USING_NS_CC;
using namespace std;

string AREvent::EventName = "ar_event_name";

void AREvent::dispatchOnCocosThread()
{
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->schedule(CC_SCHEDULE_SELECTOR(AREvent::scheduleHandler), this, 0, false);
}

void AREvent::scheduleHandler(float)
{
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->dispatchEvent(this);
    
    auto scheduler = Director::getInstance()->getScheduler();
    scheduler->unschedule(CC_SCHEDULE_SELECTOR(AREvent::scheduleHandler), this);
    
    this->release();
}
