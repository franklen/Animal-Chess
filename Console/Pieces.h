//
//  Pieces.h
//  Animal
//
//  Created by yang_xiong on 16/4/9.
//
//

#ifndef Pieces_h
#define Pieces_h
#include <iostream>
#include "Move.h"
#include "Gene.h"

using namespace std;
class Pieces{
public:
    enum TypePiece {NIL,RAT,CAT,WOLF,DOG,LEOPARD,TIGER,LION,ELEPHANT};
private:
    PointXY pos; //列，行
    int player;
    TypePiece type;
    float chessPower;
	bool eaten;
    
public:
    void setProperty(PointXY p, int play, TypePiece t);
    TypePiece getType();
    PointXY getPositionBlock();
    void setPositionBlock(PointXY p, bool show = true);
    int getPlayer();
	void setEatenValue( bool val );

    
	bool isEaten();
    int getDistanceToEnemyBase();
    
    float getDistanceValue(int dis);
    void setDistanceValye(Gene gene);
    void setChessPowerValue(Gene gene);
    float getChessPowerValue();

    float threatenFraction;
    vector<float> distanceValues;

	vector<vector<float> > distanceValues_Types;

    float riverBounus;
	void setGene(Gene &gen);

public:
	Pieces();
private:
    
    
};
#endif /* Pieces_h */