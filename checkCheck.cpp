bool checkCheck()
{
int x;
int y;
ChessPiece temp;

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

for (int i=0;i<8;i++, x=getPosX(),y=getPosY())
{


	while (!board->isEmpty(x,y))        // Move to Each Direction
		checkMove(&x,&y,i);


	if((x>7)||(x<0)||(y<0)||(x>7))		// Search Next Direction
		continue;						

	
	temp = board->getPiece(x,y);

	if(temp->getOwner() == this->getOwner())
		continue;

	switch(i%2)
	{
		case 0:			// ROOK && QUEEN
			if((temp->getType()==ROOK)||(temp->getType() == QUEEN))
				return 1;
			break;
		case 1:			// BISHOP && QUEEN
			if((temp->getType()==BISHOP)||(temp->getType() == QUEEN))
				return 1;
			break;
	}


}




return 0;


}


//QUEEN

checking 8 direction from king
and get first piece for each direction

if the piece is otherside's queen, return 1



//BISHOP

checking 4 direction from king ( cross direction )
and get first piece for each direction

if the piece is otherside's queen, return 1

//ROOK

checking 4 direction from king ()


checkCheck()

