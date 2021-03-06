//
//  Move.h
//  Animal
//
//  Created by yang_xiong on 16/4/11.
//
//

#ifndef Move_h
#define Move_h




struct PointXY {
	int x;
	int y;
	bool operator==(const PointXY &p) {
		return (x == p.x && y == p.y);
	}
	bool operator!=(const PointXY &p) {
		return (x != p.x || y != p.y);
	}
	PointXY(int _x, int _y):x(_x),y(_y){}
	PointXY() { x = -1; y = -1; }
};

class Move{
public:
    PointXY from;
    PointXY to;
	int  eatenIndex;

	Move();
	Move(PointXY f, PointXY t);
	~Move();

	inline bool operator==(const Move& cmp) {
		return (from == cmp.from && to == cmp.to);
	}


};

#endif /* Move_h */
