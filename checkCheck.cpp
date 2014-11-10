enum DIRECTION {NORTH, NORTHEAST, EAST, SOUTHEAST, SOUTH,SOUTHWEST,WEST,NORTHWEST};

void checkMove (int &x,int &y,DIRECTION dir)
{
	switch(dir)
	{
		case 0:			//NORTH
			y++;
			break;
		case 1:
			x++;
			y++;
			break;
		case 2:			//EAST
			x++;
			break;
		case 3:
			x++;
			y--;
			break;
		case 4:			//SOUTH
			y--;
			break;
		case 5:
			x--;
			y--;
			break;
		case 6:			//WEST
			x--;
			break;
		case 7:
			x--;
			y++;
			break;

	}

}


bool checkCheck()
{
	int x;
	int y;
	ChessPiece temp;

	for (int i=0;i<8;i++, x=getPosX(),y=getPosY())
	{

		while (!board->isEmpty(x,y))        // Move to Each Direction 
			checkMove(&x,&y,i);

		if((x>7)||(x<0)||(y<0)||(x>7))		// If not found anything, search next direction
			continue;						

		temp = board->getPiece(x,y);		// Get the First Piece of that direction

		if(temp->getOwner() == this->getOwner())	// If the piece is mine, search next direction
			continue;

		switch(i%2)
		{
			case 0:							// ROOK && QUEEN
				if((temp->getType()==ROOK)||(temp->getType() == QUEEN))
					return 1;
				break;
			case 1:							// BISHOP && QUEEN
				if((temp->getType()==BISHOP)||(temp->getType() == QUEEN))
					return 1;
				break;
		}
}
return 0;								// Not found any hostile
}

