//
//  Player.cpp
//  Animal
//
//  Created by yang_xiong on 16/4/11.
//
//
#include "Player.h"




vector<Move> Player::genAllMoves(Board & board)
{
	vector<Move> ret;
	for (int type = Pieces::ELEPHANT; type > Pieces::NIL; type--) {
		auto onePieceMove = genAMove(board, board.allPieces[type * 2 + board.currentPlayer]);
		for (auto a : onePieceMove) {
			ret.push_back(a);
		}
	}
	return ret;
}

float Player::eval(Board& board) {
	//Pieces::getDistanceToEnemyBase() 获取棋子离敌方base的距离
	//pieces::getChessPower() 获取子力

	if (board.getWinner() == 0)
		return -INF;
	else if (board.getWinner() == 1)
		return INF;

	float sumPower[2] = { 0,0 };
    float sumDistanceValue[2] = { 0,0 };
    float threatento[2] = { 0,0 };
    float eval = 0.0f;

    auto whichPlayersGene = board.whoWillMove;
	// for each pieces
    for (auto ps = board.allPieces.begin() + 2; ps < board.allPieces.end(); ps++) {
        auto piece = *ps;
        int player = piece->getPlayer();
        if (!board.hasPiece(piece->getType(), player))
            continue;
        // pieces power
        if (piece->getType() == Pieces::RAT && board.hasPiece(Pieces::ELEPHANT, !player))
            sumPower[player] += piece->getChessPowerValue(whichPlayersGene) * 0.5;
        //else
        sumPower[player] += piece->getChessPowerValue(whichPlayersGene);
        if (TLBesideRiver(board, *ps))
            sumPower[player] += piece->riverBounus[whichPlayersGene];
        // Distance
        sumPower[player] += piece->getDistanceValue(piece->getDistanceToEnemyBase(), whichPlayersGene);
        // threaten
        auto possibleMoves = genAMove(board, piece);
        for (auto mv : possibleMoves) {
            auto toPieces = board.getPiece(mv.to);
            if (toPieces->getType() != Pieces::NIL)
                sumPower[player] += toPieces->getChessPowerValue(whichPlayersGene) / piece->threatenFraction[whichPlayersGene];
        }
    }
	eval = sumPower[1] - sumPower[0];


	return eval;


}

vector<Move> Player::genAMove(Board &board, Pieces * fromPiece) {
	if (fromPiece->isEaten()) {
		return vector<Move>();
	}

	PointXY fromXY = fromPiece->getPositionBlock();
	vector<Move> potentialMoves;
	Move potentialMove;
	potentialMove.from = fromXY;

	if (fromPiece->getType() == Pieces::TypePiece::LION || fromPiece->getType() == Pieces::TypePiece::TIGER) {
		if (board.getTerrain(PointXY(fromXY.x + 1, fromXY.y)) == Board::TypeTerrain::RIVER) {//右边有河
			potentialMove.to = PointXY(fromXY.x + 4, fromXY.y);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x - 1, fromXY.y);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x, fromXY.y + 1);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x, fromXY.y - 1);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
		} else if (board.getTerrain(PointXY(fromXY.x - 1, fromXY.y)) == Board::TypeTerrain::RIVER) {//左边有河
			potentialMove.to = PointXY(fromXY.x + 1, fromXY.y);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x - 4, fromXY.y);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x, fromXY.y + 1);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x, fromXY.y - 1);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
		} else if (fromXY.y == 0 && board.getTerrain(PointXY(fromXY.x, fromXY.y + 1)) == Board::TypeTerrain::RIVER) {//下面有河
			potentialMove.to = PointXY(fromXY.x + 1, fromXY.y);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x - 1, fromXY.y);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x, fromXY.y + 3);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			//已经在上边缘不用考虑向上走
		} else if (fromXY.y == 6 && board.getTerrain(PointXY(fromXY.x, fromXY.y - 1)) == Board::TypeTerrain::RIVER) {//上面有河
			potentialMove.to = PointXY(fromXY.x + 1, fromXY.y);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x - 1, fromXY.y);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x, fromXY.y - 3);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			//已经在下边缘不用考虑向下走
		} else if (fromXY.y == 3 && board.getTerrain(PointXY(fromXY.x, fromXY.y - 1)) == Board::TypeTerrain::RIVER && board.getTerrain(PointXY(fromXY.x, fromXY.y + 1)) == Board::TypeTerrain::RIVER) {//在河之间
			potentialMove.to = PointXY(fromXY.x + 1, fromXY.y);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x - 1, fromXY.y);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x, fromXY.y + 3);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x, fromXY.y - 3);
			if (board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
		} else {
			potentialMove.to = PointXY(fromXY.x + 1, fromXY.y);
			if (fromXY.x + 1 <= 8 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x - 1, fromXY.y);
			if (fromXY.x - 1 >= 0 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x, fromXY.y + 1);
			if (fromXY.y + 1 <= 6 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x, fromXY.y - 1);
			if (fromXY.y - 1 >= 0 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
		}
	} else {//其他动物
			//优先生成向前的move
		if (fromPiece->getPlayer()) {
			potentialMove.to = PointXY(fromXY.x - 1, fromXY.y);
			if (fromXY.x - 1 >= 0 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x + 1, fromXY.y);
			if (fromXY.x + 1 <= 8 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
		} else {
			potentialMove.to = PointXY(fromXY.x + 1, fromXY.y);
			if (fromXY.x + 1 <= 8 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
			potentialMove.to = PointXY(fromXY.x - 1, fromXY.y);
			if (fromXY.x - 1 >= 0 && board.availableMove(potentialMove))
				potentialMoves.push_back(potentialMove);
		}
		potentialMove.to = PointXY(fromXY.x, fromXY.y + 1);
		if (fromXY.y + 1 <= 6 && board.availableMove(potentialMove))
			potentialMoves.push_back(potentialMove);
		potentialMove.to = PointXY(fromXY.x, fromXY.y - 1);
		if (fromXY.y - 1 >= 0 && board.availableMove(potentialMove))
			potentialMoves.push_back(potentialMove);
	}

	// set eatinfo
	for (auto &mv : potentialMoves) {
		auto pieceTo = board.getPiece(mv.to);
		if (pieceTo->getType() != Pieces::NIL) {
			mv.eatenIndex = board.getPieceIndex(pieceTo->getType(), pieceTo->getPlayer());
		}
	}
	return potentialMoves;
}

void Player::cancelMove(Move & mv, Board *board)
{
	auto from = mv.from;
	auto to = mv.to;
	auto toPiece = board->getPiece(to);
	board->boardPieces[from.x][from.y] = board->boardPieces[to.x][to.y];
	toPiece->setPositionBlock(from, false);
	if (mv.eatenIndex != -1) {
		auto eatenPiece = board->allPieces[mv.eatenIndex];
		board->boardPieces[to.x][to.y] = eatenPiece;
		eatenPiece->setPositionBlock(to, false);
		eatenPiece->setEatenValue(false);
		board->nPiecesExisted[eatenPiece->getPlayer()] ++;
	} else {
		board->boardPieces[to.x][to.y] = board->nul_piece;
	}
	board->currentPlayer = !board->currentPlayer;
	//board->fcoutBoard();
}

Player::Player()
{
	player = -1;
	name = string();
}

Player::~Player()
{
}

bool Player::TLBesideRiver(Board &board, Pieces *piece)
{
	auto x = piece->getPositionBlock().x;
	auto y = piece->getPositionBlock().y;
	return (
		(piece->getType() == Pieces::LION || piece->getType() == Pieces::TIGER) &&
		(
			(x && board.getTerrain({ x - 1,y }) == Board::RIVER) ||
			(y && board.getTerrain({ x,y - 1 }) == Board::RIVER) ||
			(x < 8 && board.getTerrain({ x + 1,y }) == Board::RIVER) ||
			(y < 6 && board.getTerrain({ x,y + 1 }) == Board::RIVER)
			));
}

