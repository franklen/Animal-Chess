//
//  GameScene.h
//  Animal
//
//  Created by yang_xiong on 16/4/7.
//
//

#ifndef GameScene_h
#define GameScene_h
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocos-ext.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "HelloWorldScene.h"
#include "LevelSelectLayer.h"
#include "Evolution.h"
#include <time.h>

#include "Board.h"
#include "AI_Min_Max.h"

USING_NS_CC;

class GameScene :public Layer{
public:
    static Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    Board* board;
	bool gameOverDetect();
	AI_Min_Max *MinMax;
    void menuRestartCallback(cocos2d::Ref* pSender);
    void menuBackToMainCallback(cocos2d::Ref* pSender);
    
    void operatePieceVsPeople(PointXY chosenBlock);
    void operatePieceVsAI(PointXY chosenBlock);
    virtual void onceUpdate(float dt);
    
    void firstAIPlay();
    void secondAIPlay();
    void startUpdate(float dt);
    virtual void update(float dt);
    
    void startEvolutionPrcess();
    void finishEvolutionProcess();
    



private:
    void gameOverProcess(int winner);
};

#endif /* GameScene_h */
