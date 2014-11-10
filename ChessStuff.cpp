#include <iostream>
#include "ChessStuff.h"

ChessBoard* ChessBoard::instance = NULL;

ChessBoard* board;

//------------------------------------------------------------------Board Part---------------------------------------------------------------------
ChessBoard::ChessBoard() // ChessBoard Constructor
{
	for(int row=0; row<8; row++)
	{
		switch(row)
		{
			case 0: //WHITE, Set Not Pawn Row
				Map[0][row] = new Rook(0, row, WHITE);
				Map[7][row] = new Rook(7, row, WHITE);

				Map[1][row] = new Knight(1, row, WHITE);
				Map[6][row] = new Knight(6, row, WHITE);

				Map[2][row] = new Bishop(2, row, WHITE);
				Map[5][row] = new Bishop(5, row, WHITE);

				Map[3][row] = new Queen(3, row, WHITE);

				Map[4][row] = new King(4, row, WHITE);

				break;
			case 1: //WHITE, Set Pawn Row
				for(int col=0; col<8; col++)
				{
					Map[col][row] = new Pawn(col, row, WHITE);
				}
				break;

			case 7: //BLACK, Set Not Pawn Row
				Map[0][row] = new Rook(0, row, BLACK);
				Map[7][row] = new Rook(7, row, BLACK);

				Map[1][row] = new Knight(1, row, BLACK);
				Map[6][row] = new Knight(6, row, BLACK);

				Map[2][row] = new Bishop(2, row, BLACK);
				Map[5][row] = new Bishop(5, row, BLACK);

				Map[3][row] = new Queen(3, row, BLACK);

				Map[4][row] = new King(4, row, BLACK);

				break;

			case 6: //BLACK, Set Pawn Row
				for(int col=0; col<8; col++)
				{
					Map[col][row] = new Pawn(col, row, BLACK);
				}
				break;

			default: //row 2~5, Empty Row
				for(int col=0; col<8; col++)
				{
					Map[col][row] = NULL;
				}
		}
	}
}

ChessBoard::~ChessBoard() // ChessBoard Destructor
{
	for(int row=0; row<8; row++)
	{
		for(int col=0; col<8; col++)
		{
			if(Map[col][row]!=NULL)
			{
				delete Map[col][row];
			}
		}
	}
}

bool ChessBoard::isEmpty(int x, int y) // (x, y) is Empty?
{
	if(Map[x][y] == NULL) // is Empty
		return true;
	else // Not Empty
		return false;
}

bool ChessBoard::isEmpty(int index) // (index) is Empty?
{
	int x = index%8; int y = index/8;
	
	if(Map[x][y] == NULL) // is Empty
		return true;
	else // Not Empty
		return false;
}

void ChessBoard::move(int posX, int posY, int moveX, int moveY) // Move Piece from (posX, posY) to (moveX, moveY), if (moveX, moveY) is Not Empty, delete it.
{
	ChessPiece* piece = Map[posX][posY];
	if(piece == NULL)
		return;
	
	bool canMove = false;

	switch(piece->getType())
	{
		case PAWN: canMove = ((Pawn*)piece)->canMove(moveX, moveY); break;
		case ROOK: canMove = ((Rook*)piece)->canMove(moveX, moveY); break;
		case KNIGHT: canMove = ((Knight*)piece)->canMove(moveX, moveY);	break;			
		case BISHOP: canMove = ((Bishop*)piece)->canMove(moveX, moveY); break;
		case QUEEN: canMove = ((Queen*)piece)->canMove(moveX, moveY); break;
		case KING: canMove = ((King*)piece)->canMove(moveX, moveY); break;
	}

	if(canMove)
	{
		if( !isEmpty(moveX, moveY) ) // is Not Empty, delete it
			delete Map[moveX][moveY];

		Map[moveX][moveY] = Map[posX][posY]; // Move Piece from (posX, posY) to (moveX, moveY)
		Map[posX][posY] = NULL;

		Map[moveX][moveY]->setPosition(moveX, moveY); // Set Position Data

		if(Map[moveX][moveY]->getType()==PAWN)
		{
			if( (moveY==7 && Map[moveX][moveY]->getOwner()==WHITE) || (moveY==0 && Map[moveX][moveY]->getOwner()==BLACK) )
				promotion(moveX, moveY);
		}
	}
}

void ChessBoard::move(int posIndex, int moveIndex) // Move Piece from (posX, posY) to (moveX, moveY), if (moveX, moveY) is Not Empty, delete it.
{
	if(posIndex < 0 || moveIndex < 0)
		return;

	int posX = posIndex%8; int posY = posIndex/8;
	int moveX = moveIndex%8; int moveY = moveIndex/8;

	ChessPiece* piece = Map[posX][posY];
	if(piece == NULL)
		return;

	bool canMove = false;

	switch(piece->getType())
	{
		case PAWN: canMove = ((Pawn*)piece)->canMove(moveX, moveY); break;
		case ROOK: canMove = ((Rook*)piece)->canMove(moveX, moveY); break;
		case KNIGHT: canMove = ((Knight*)piece)->canMove(moveX, moveY);	break;			
		case BISHOP: canMove = ((Bishop*)piece)->canMove(moveX, moveY); break;
		case QUEEN: canMove = ((Queen*)piece)->canMove(moveX, moveY); break;
		case KING: canMove = ((King*)piece)->canMove(moveX, moveY); break;
	}

	if(canMove)
	{
		if( !isEmpty(moveX, moveY) ) // is Not Empty, delete it
			delete Map[moveX][moveY];

		Map[moveX][moveY] = Map[posX][posY]; // Move Piece from (posX, posY) to (moveX, moveY)
		Map[posX][posY] = NULL;

		Map[moveX][moveY]->setPosition(moveX, moveY); // Set Position Data

		if(Map[moveX][moveY]->getType()==PAWN)
		{
			if( (moveY==7 && Map[moveX][moveY]->getOwner()==WHITE) || (moveY==0 && Map[moveX][moveY]->getOwner()==BLACK) )
				promotion(moveX, moveY);
		}
	}
}

void ChessBoard::promotion(int x, int y)
{
	ChessPiece* pawn = Map[x][y];

	int Ptype = PAWN;

	bool notChanged = true;
	do{
		std::cin >> Ptype;

		switch(Ptype)
		{
			case ROOK: Map[x][y] = new Rook(x, y, pawn->getOwner()); notChanged = false; break;
			case KNIGHT: Map[x][y] = new Knight(x, y, pawn->getOwner()); notChanged = false; break;
			case BISHOP: Map[x][y] = new Bishop(x, y, pawn->getOwner()); notChanged = false; break;
			case QUEEN: Map[x][y] = new Queen(x, y, pawn->getOwner()); notChanged = false; break;
		}
	}while(notChanged);

	delete pawn;
}

//-----------------------------------------------------------Piece Part-----------------------------------------------------------------------------------------

bool Pawn::enPassant() // Special Rule 1. En Passant.
{
	return false;
}

bool Pawn::canMove(int moveX, int moveY) // this Pawn can move to (moveX, moveY)?
{
	if(moveX < 0 || moveY < 0 || moveX > 7 || moveY > 7) // if moveX or moveY is out of board
		return false;

	switch(getOwner()) // who is the owner of this pawn
	{
		case WHITE: // if WHITE(upside player)
			if(moveX == getPosX() && (moveY - getPosY()) == 2) // if move 2 in the Y-direction
			{
				if(isMove)
					return false;
				else if(!board->isEmpty(getPosX(), getPosY()+1))
					return false;
				else
				{
					isMove = true;
					return true;
				}
			}

			else if( (moveY <= getPosY() || moveY > getPosY()+1) || (moveX > getPosX()+1 || moveX < getPosX()-1) ) // if move Backword Or move over 1 in the Y-direction Or move over 1 in the X-direction Or move over -1 in the X-direction
				return false;

			else if(moveX == getPosX()){ // if not move in the X-direction -> can move if empty
				if(board->isEmpty(moveX, moveY)) // if (moveX, moveY) is Empty -> can move
				{
					isMove = true;
					return true;
				}
				else // or not -> can't move
					return false;
			}

			else if(moveX != getPosX()){ // if move in the X-direction -> can move if enemy exist
				if(board->isEmpty(moveX, moveY)) // if (moveX, moveY) is empty -> can't move
					return false;

				else if(board->isSameOwner(getPosX(), getPosY(), moveX, moveY)) // if Piece of (moveX, moveY) is same owner -> can't move
					return false;

				else // or not = (moveX, moveY) is enemy -> can move
				{
					isMove = true;
					return true;
				}
			}

		case BLACK: // if BLACK(downside player)
			if(moveX == getPosX() && (moveY - getPosY()) == -2)// if move 2 in the Y-direction
			{
				if(isMove)
					return false;
				else if(!board->isEmpty(getPosX(), getPosY()-1))
					return false;
				else
				{
					isMove = true;
					return true;
				}
			}

			else if( (moveY >= getPosY() || moveY < getPosY()-1) || (moveX > getPosX()+1 || moveX < getPosX()-1) ) // if move Backword Or move over 1 in the Y-direction Or move over 1 in the X-direction Or move over -1 in the X-direction
				return false;

			else if(moveX == getPosX()){ // if not move in the X-direction -> can move if empty
				if(board->isEmpty(moveX, moveY)) // if (moveX, moveY) is Empty -> can move
				{
					isMove = true;
					return true;
				}
				else // or not -> can't move
					return false;
			}
			else if(moveX != getPosX()){ // if move in the X-direction -> can move if enemy exist
				if(board->isEmpty(moveX, moveY)) // if (moveX, moveY) is empty -> can't move
					return false;

				else if(board->isSameOwner(getPosX(), getPosY(), moveX, moveY)) // if Piece of (moveX, moveY) is same owner -> can't move
					return false;

				else // or not = (moveX, moveY) is enemy -> can move
				{
					isMove = true;
					return true;
				}
			}
	}
}

bool Rook::canMove(int moveX, int moveY) // this Rook can move to (moveX, moveY)?
{
	if(moveX < 0 || moveY < 0 || moveX > 7 || moveY > 7) // out of board
		return false;

	if(moveX != getPosX() && moveY != getPosY()) // not move on a row or column
		return false;
	else if(moveX == getPosX() && moveY == getPosY()) // not move( move on (posX, posY) )
		return false;

	if(moveX == getPosX()) // moveX == posX -> move in the Y-direction
	{
		if(getPosY() < moveY) // moveY > posY
		{
			for(int i=1; getPosY()+i < moveY; i++)
			{
				if(!board->isEmpty(getPosX(), getPosY()+i)) // Check posY+1 ~ moveY-1 is Empty
					return false;
			}
		}
		else if(getPosY() > moveY) // moveY < posY
		{
			for(int i=1; getPosY()-i > moveY; i++)
			{
				if(!board->isEmpty(getPosX(), getPosY()-i)) // Check posY-1 ~ moveY+1 is Empty
					return false;
			}
		}

		if(!board->isEmpty(moveX, moveY) && board->isSameOwner(getPosX(), getPosY(), moveX, moveY)) // Check (moveX, moveY) of owner, if same
			return false;
	}

	else if(moveY == getPosY()) // moveY == posY -> move in the X-direction
	{
		if(getPosX() < moveX) // moveX > posX
		{
			for(int i=1; getPosX()+i < moveX; i++)
			{
				if(!board->isEmpty(getPosX()+i, getPosY())) // Check posX+1 ~ moveX-1 is Empty
					return false;
			}
		}
		else if(getPosX() > moveX) // moveX < posX
		{
			for(int i=1; getPosX()-i > moveX; i++)
			{
				if(!board->isEmpty(getPosX()-i, getPosY())) // Check posX-1 ~ moveX+1 is Empty
					return false;
			}
		}

		if(!board->isEmpty(moveX, moveY) && board->isSameOwner(getPosX(), getPosY(), moveX, moveY)) // Check (moveX, moveY) of owner, if same
			return false;
	}

	// from current position to move position is empty and move position is empty or enemy
	
	isMove = true; // set isMove true
	return true;
}

bool Knight::canMove(int moveX, int moveY) // this Knight can move to (moveX, moveY)?
{
	if(moveX < 0 || moveY < 0 || moveX > 7 || moveY > 7) // out of board
		return false;

	int movepos = (moveX - getPosX()) * (moveY - getPosY());

	if(movepos != 2 && movepos != -2) // if not Knight move rule
		return false;
	else if(!board->isEmpty(moveX, moveY) && board->isSameOwner(getPosX(), getPosY(), moveX, moveY)) // (moveX, moveY) is same owner
		return false;
	else // (moveX, moveY) is empty or enemy
		return true;
}
	
bool Bishop::canMove(int moveX, int moveY) // this Bishop can move to (moveX, moveY)?
{
	if(moveX < 0 || moveY < 0 || moveX > 7 || moveY > 7) // out of board
		return false;

	if(moveX == getPosX()) // if moveX == posX (Equal to moveY == posY)
		return false;

	if( (moveX - getPosX()) == (moveY - getPosY()) ) // move on Positive Diagonal
	{
		if(getPosX() < moveX) // moveX > posX
		{
			for(int i=1; getPosX()+i < moveX; i++)
			{
				if(!board->isEmpty(getPosX()+i, getPosY()+i)) // Check (posX+1, posY+1) ~ (moveX-1, moveY-1) is Empty
					return false;
			}
		}
		else if(getPosX() > moveX) // moveX < posX
		{
			for(int i=1; getPosX()-i > moveX; i++)
			{
				if(!board->isEmpty(getPosX()-i, getPosY()-i)) // Check (posX-1, posY-1) ~ (moveX+1, moveY+1) is Empty
					return false;
			}
		}

		if(!board->isEmpty(moveX, moveY) && board->isSameOwner(getPosX(), getPosY(), moveX, moveY)) // if (moveX, moveY) is same owner
			return false;
		else // (moveX, moveY) is Empty or Enemy
			return true;
	}

	else if( (moveX - getPosX()) + (moveY - getPosY()) == 0 ) // move on Negative Diagonal
	{
		if(getPosX() < moveX) // moveX > posX
		{
			for(int i=1; getPosX()+i < moveX; i++)
			{
				if(!board->isEmpty(getPosX()+i, getPosY()-i)) // Check (posX+1, posY+1) ~ (moveX-1, moveY-1) is Empty
					return false;
			}
		}
		else if(getPosX() > moveX) // moveX < posX
		{
			for(int i=1; getPosX()-i > moveX; i++)
			{
				if(!board->isEmpty(getPosX()-i, getPosY()+i)) // Check (posX-1, posY-1) ~ (moveX+1, moveY+1) is Empty
					return false;
			}
		}

		if(!board->isEmpty(moveX, moveY) && board->isSameOwner(getPosX(), getPosY(), moveX, moveY)) // if (moveX, moveY) is same owner
			return false;
		else // (moveX, moveY) is Empty or Enemy
			return true;
	}

	else
		return false;
}
	
bool Queen::canMove(int moveX, int moveY) // this Queen can move to (moveX, moveY)?
{
	if(moveX < 0 || moveY < 0 || moveX > 7 || moveY > 7) // out of board
		return false;

	if(moveX == getPosX() && moveY == getPosY()) // not move( move on (posX, posY) )
		return false;

	if( (moveX - getPosX()) == (moveY - getPosY()) ) // move on Positive Diagonal
	{
		if(getPosX() < moveX) // moveX > posX
		{
			for(int i=1; getPosX()+i < moveX; i++)
			{
				if(!board->isEmpty(getPosX()+i, getPosY()+i)) // Check (posX+1, posY+1) ~ (moveX-1, moveY-1) is Empty
					return false;
			}
		}
		else if(getPosX() > moveX) // moveX < posX
		{
			for(int i=1; getPosX()-i > moveX; i++)
			{
				if(!board->isEmpty(getPosX()-i, getPosY()-i)) // Check (posX-1, posY-1) ~ (moveX+1, moveY+1) is Empty
					return false;
			}
		}

		if(!board->isEmpty(moveX, moveY) && board->isSameOwner(getPosX(), getPosY(), moveX, moveY)) // if (moveX, moveY) is same owner
			return false;
		else // (moveX, moveY) is Empty or Enemy
			return true;
	}

	else if( (moveX - getPosX()) + (moveY - getPosY()) == 0 ) // move on Negative Diagonal
	{
		if(getPosX() < moveX) // moveX > posX
		{
			for(int i=1; getPosX()+i < moveX; i++)
			{
				if(!board->isEmpty(getPosX()+i, getPosY()-i)) // Check (posX+1, posY+1) ~ (moveX-1, moveY-1) is Empty
					return false;
			}
		}
		else if(getPosX() > moveX) // moveX < posX
		{
			for(int i=1; getPosX()-i > moveX; i++)
			{
				if(!board->isEmpty(getPosX()-i, getPosY()+i)) // Check (posX-1, posY-1) ~ (moveX+1, moveY+1) is Empty
					return false;
			}
		}

		if(!board->isEmpty(moveX, moveY) && board->isSameOwner(getPosX(), getPosY(), moveX, moveY)) // if (moveX, moveY) is same owner
			return false;
		else // (moveX, moveY) is Empty or Enemy
			return true;
	}

	else if(moveX == getPosX()) // moveX == posX -> move in the Y-direction
	{
		if(getPosY() < moveY) // moveY > posY
		{
			for(int i=1; getPosY()+i < moveY; i++)
			{
				if(!board->isEmpty(getPosX(), getPosY()+i)) // Check posY+1 ~ moveY-1 is Empty
					return false;
			}
		}
		else if(getPosY() > moveY) // moveY < posY
		{
			for(int i=1; getPosY()-i > moveY; i++)
			{
				if(!board->isEmpty(getPosX(), getPosY()-i)) // Check posY-1 ~ moveY+1 is Empty
					return false;
			}
		}

		if(!board->isEmpty(moveX, moveY) && board->isSameOwner(getPosX(), getPosY(), moveX, moveY)) // Check (moveX, moveY) of owner, if same
			return false;
		else
			return true;
	}
	else if(moveY == getPosY()) // moveY == posY -> move in the X-direction
	{
		if(getPosX() < moveX) // moveX > posX
		{
			for(int i=1; getPosX()+i < moveX; i++)
			{
				if(!board->isEmpty(getPosX()+i, getPosY())) // Check posX+1 ~ moveX-1 is Empty
					return false;
			}
		}
		else if(getPosX() > moveX) // moveX < posX
		{
			for(int i=1; getPosX()-i > moveX; i++)
			{
				if(!board->isEmpty(getPosX()-i, getPosY())) // Check posX-1 ~ moveX+1 is Empty
					return false;
			}
		}

		if(!board->isEmpty(moveX, moveY) && board->isSameOwner(getPosX(), getPosY(), moveX, moveY)) // Check (moveX, moveY) of owner, if same
			return false;
		else
			return true;
	}

	else
		return false;
}
	
bool King::castling(int type) // Special Rule 2. Castling
{
	switch(type)
	{
		case KING:
			return false;
			break;
		case QUEEN:
			return false;
			break;

		default: return false;
	}
}

bool King::checkCheck()
{
	return isCheck;
}

bool King::canMove(int moveX, int moveY) // this King can move to (moveX, moveY)?
{
	if(moveX < 0 || moveY < 0 || moveX > 7 || moveY > 7) // out of board;
		return false;

	if(moveX == getPosX() && moveY == getPosY()) // not move( move to (posX, posY) )
		return false;

	if(!isMove) // this King never moved
	{
		if(moveY == getPosY() && moveX - getPosX() == 2) // King Side Castling
			return castling(KING);
		else if(moveY == getPosY() && moveX - getPosX() == -2) // Queen Side Castling
			return castling(QUEEN);
	}

	if(moveX > getPosX()+1 || moveX < getPosX()-1 || moveY > getPosY()+1 || moveY < getPosY()-1) // if move more than 1
		return false;
	else if( !board->isEmpty(moveX, moveY) && board->isSameOwner(getPosX(), getPosY(), moveX, moveY) ) // (moveX, moveY) is same owner;
		return false;
	else // (moveX, moveY) is Empty or Enemy
	{
		isMove = true; // Set isMove true
		return true;
	}
}