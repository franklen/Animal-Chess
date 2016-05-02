//
//  Gene.h
//  Animal
//
//  Created by yang_xiong on 16/4/19.
//
//

#ifndef Gene_h
#define Gene_h

#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

#include "Move.h"
using namespace std;
class Gene {
private:
	vector<float> gene;
public:
	int winState;           // 0 not start game, 1 win game, -1 lose game
	Gene();
	~Gene();
	void generateRandomGene();
	void printGene();
	vector<float>getGene();
	void setGene(vector<float> m_gene);
    void updateGene(int pos, float value);
};

#endif /* Gene_h */