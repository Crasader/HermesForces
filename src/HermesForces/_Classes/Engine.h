//
//  Engine.h
//  BombTerrorist
//
//  Created by Quan Rock on 1/26/16.
//
//

#ifndef Engine_h
#define Engine_h
#include "define.h"

class Engine{
public:
    static Engine* Instance()
    {
        if(_instance == NULL)
        {
            _instance = new Engine();
        }
        return _instance;
    }
    
    // init infor
    void init();
    // get type of scene
    int getSizeTypeDevice();
    
    void setDirector();
    
    void startAnimationGame();
    
    void stopAnimationGame();

    void gotoScene(Scene* scene);
    void replaceScene(Scene* scene,  const int& delaytime = DEFAULT_TRANSITION_TIME);
    
    cocos2d::Size getVisibleSize() const ;
	
	//const bool& getMissionStatus() { return _missionStt; }
	//void setMissionStatus(const bool& score) { _missionStt = score; }
    
private:
    static    Engine*    _instance;
    int _typeSizeDevice;
    cocos2d::Size _visibleSize;
    Engine();
};
#endif /* Engine_h */
