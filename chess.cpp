#include <iostream>
#include "ChessStuff.h"

using namespace std;

void Display(ChessBoard* board); // Capital letter : WHITE, Small letter : BLACK

int main(){
	ChessBoard board;

	char input;

	while(true)
	{
		Display(&board);

		cout << "Choose one(q, m)" << endl;
		cin >> input;

		if(input=='q')
			break;
		else if(input=='m')
		{
			cout << "Choose Piece to move" << endl;
			//int index1;
			//cin >> index1;

			int x1 = 0;
			int y1 = 0;
			cin >> x1 >> y1;

			cout << "Where to go?" << endl;
			int x2, y2;
			cin >> x2 >> y2;

			board.move(x1, y1, x2, y2);
		}
	}
}

void Display(ChessBoard* board) // Capital letter : WHITE, Small letter : BLACK
{
	for(int row=0; row<8; row++)
	{
		for(int col=0; col<8; col++)
		{
			ChessPiece* Piece = board->getPiece(col, row);
			if(Piece==NULL)
				cout << '0';
			else
			{
				switch(Piece->getType())
				{
					case PAWN: 
						if(Piece->getOwner()==WHITE)
							cout << 'P';
						else if(Piece->getOwner()==BLACK)
							cout << 'p';
						break;
					case ROOK:
						if(Piece->getOwner()==WHITE)
							cout << 'R';
						else if(Piece->getOwner()==BLACK)
							cout << 'r';
						break;
					case KNIGHT:
						if(Piece->getOwner()==WHITE)
							cout << 'K';
						else if(Piece->getOwner()==BLACK)
							cout << 'k';
						break;
					case BISHOP:
						if(Piece->getOwner()==WHITE)
							cout << 'B';
						else if(Piece->getOwner()==BLACK)
							cout << 'b';
						break;
					case QUEEN:
						if(Piece->getOwner()==WHITE)
							cout << 'Q';
						else if(Piece->getOwner()==BLACK)
							cout << 'q';
						break;
					case KING:
						if(Piece->getOwner()==WHITE)
							cout << 'K';
						else if(Piece->getOwner()==BLACK)
							cout << 'k';
						break;
				}
			}
		}

		cout << endl;
	}
}