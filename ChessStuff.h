#ifndef __CHESS_STUFF_H__
#define __CHESS_STUFF_H__

#include <iostream>

enum PCTYPE {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
enum PLAYER {WHITE, BLACK};
//WHITE is Upside Player, BLACK is Downside Player.

class ChessBoard;

class ChessPiece{
private:
	int posX;
	int posY;
	PLAYER owner;
	PCTYPE type;

public:
	void initPiece(int x, int y, PLAYER player, PCTYPE type){posX = x; posY = y; owner = player; this->type = type;} // used in Piece Constructor & promotion
	void setPosition(int x, int y){posX = x; posY = y;} // Set Position of Piece

	int getPosX(){return posX;}
	int getPosY(){return posY;}
	int getOwner(){return owner;}
	int getType(){return type;}

	virtual bool canMove(int MoveX, int moveY, ChessBoard* board) = 0;
};

class ChessBoard{
private:
	ChessPiece* Map[8][8];

public:
	ChessBoard();
	~ChessBoard();

	ChessPiece* operator[]( const int index )
	{
		if(index < 0)
			return NULL;

		int x = index%8;
		int y = index/8;
		return this->Map[x][y];
	} 

	bool isEmpty(int x, int y); // Map[x][y] is empty?
	bool isEmpty(int index); // Map[index] is empty?

	int getOwner(int x, int y){return Map[x][y]->getOwner();} // get owner of Map[x][y]
	int getOwner(int index){return (*this)[index]->getOwner();}
	
	void move(int posX, int posY, int moveX, int moveY); // move Piece of (posX, posY) to (moveX, moveY)
	void move(int posIndex, int moveIndex); // move Piece of (posIndex%8, posIndex/8) to (moveIndex%8, moveIndex/8)
	
	void promotion(int x, int y);

	ChessPiece* getPiece(int x, int y){return Map[x][y];}
	ChessPiece* getPiece(int index){return (*this)[index];}

	bool isSameOwner(int x1, int y1, int x2, int y2){return Map[x1][y1]->getOwner() == Map[x2][y2]->getOwner();} // owner of (x1, y1) and (x2, y2) is same?
	bool isSameOwner(int index1, int index2){return (*this)[index1]->getOwner() == (*this)[index2]->getOwner();} // owner of (index1) and (index2) is same?
};

class Pawn:public ChessPiece{
private:
	bool isMove;

	bool enPassant(); // Special Rule 1. En Passant

public:
	Pawn(int x, int y, PLAYER player){initPiece(x, y, player, PAWN); isMove = false;}
	void promotion(ChessBoard* board); // Pawn Promotion
	bool canMove(int moveX, int moveY, ChessBoard* board); // this Pawn can move to (moveX, moveY)?
};

class Rook:public ChessPiece{
private:
	bool isMove;

public:
	Rook(int x, int y, PLAYER player){initPiece(x, y, player, ROOK); isMove = false;}
	bool isMoved(){return isMove;}
	bool canMove(int moveX, int moveY, ChessBoard* board); // this Rook can move to (moveX, moveY)?
};

class Knight:public ChessPiece{
public:
	Knight(int x, int y, PLAYER player){initPiece(x, y, player, KNIGHT);}
	bool canMove(int moveX, int moveY, ChessBoard* board); // this Knight can move to (moveX, moveY)?
};

class Bishop:public ChessPiece{
public:
	Bishop(int x, int y, PLAYER player){initPiece(x, y, player, BISHOP);}
	bool canMove(int moveX, int moveY, ChessBoard* board); // this Bishop can move to (moveX, moveY)?
};

class Queen:public ChessPiece{
public:
	Queen(int x, int y, PLAYER player){initPiece(x, y, player, QUEEN);}
	bool canMove(int moveX, int moveY, ChessBoard* board); // this Queen can move to (moveX, moveY)?
};

class King:public ChessPiece{
private:
	bool isMove;
	bool isCheck;

	bool castling(int type); // Special Rule 2. Castling

public:
	King(int x, int y, PLAYER player){initPiece(x, y, player, KING); isMove = false; isCheck = false;}
	bool isChecked(){return isCheck;}
	bool checkCheck
	bool canMove(int moveX, int moveY, ChessBoard* board); // this King can move to (moveX, moveY)?
};

#endif