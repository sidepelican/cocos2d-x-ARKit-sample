#ifndef __ARManager__
#define __ARManager__

#include "cocos2d.h"

#include "AREvent.h"

class ARManager
{
public:
    static ARManager* getInstance();
    
private:
    cocos2d::RefPtr<AREvent> event { nullptr };
    
private:
    ARManager() = default;
    ~ARManager() = default;
    
public:
    void update(float);
    AREvent* getEvent() const;
    
    bool isAvailable();
    void startARSession();
    void closeARSession();
    void hitTest(const cocos2d::Vec2& worldPosition);
};

#endif /* __ARManager__ */
