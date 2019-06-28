#include "snake.h"

#define GROWCHECKP 1
#define DELAYCHECKP 5

snakepart::snakepart(int col,int row)
{
	x=col;
	y=row;
}

snakepart::snakepart()
{
	x=0;
	y=0;
}

snakeclass::snakeclass()
{
	initscr();
	nodelay(stdscr,true);
	keypad(stdscr,true);
	noecho();
	curs_set(0);//cursor invisible
	getmaxyx(stdscr,maxheight,maxwidth);
	//init variables
	partchar='@';
	foo='*';
	food.x=0;food.y=0;
	
	srand(time(NULL));
	
	points=0;
	del=110000;
	get=false;
	direction=rand()%4;
	int tmpx,tmpy;
	switch(direction)
	{
		case 0:
			direction='l';
			tmpx=rand()%(maxwidth-15)+10;
			tmpy=rand()%(maxheight-2)+1;
			for(int i=0;i<5;i++)
			{
				snake.push_back(snakepart(tmpx+i,tmpy));
			}
			break;
		case 1:
			direction='r';
			tmpx=rand()%(maxwidth-15)+5;
			tmpy=rand()%(maxheight-2)+1;
			for(int i=0;i<5;i++)
			{
				snake.push_back(snakepart(tmpx-i,tmpy));
			}
			break;
		case 2:
			direction='u';
			tmpx=rand()%(maxwidth-2)+1;
			tmpy=rand()%(maxheight-15)+10;
			for(int i=0;i<5;i++)
			{
				snake.push_back(snakepart(tmpx,tmpy+i));
			}
			break;
		case 3:
			direction='d';
			tmpx=rand()%(maxwidth-2)+1;
			tmpy=rand()%(maxheight-15)+5;
			for(int i=0;i<5;i++)
			{
				snake.push_back(snakepart(tmpx,tmpy-i));
			}
			break;		
	}
	
	
	
	
	
	
	putfood();
	
	box(stdscr,0,0);
	
	for(int i=0;i<snake.size();++i)
	{
		move(snake[i].y,snake[i].x);
		addch(partchar);
	}
	move(maxheight-1,0); printw("score: %d",points);
	move(food.y,food.x); addch(foo); refresh();
}

snakeclass::~snakeclass()
{
	nodelay(stdscr,false);
	//getch();
	endwin();
}

void snakeclass::putfood()
{
	while(1)
	{
		int tmpxfood=rand()%(maxwidth-2)+1;
		int tmpyfood=rand()%(maxheight-2)+1;
		for(int i=0;i<snake.size();++i)
		{
			if(snake[i].x==tmpxfood && snake[i].y==tmpyfood)
				continue;
		}
		if(tmpxfood>=maxwidth-2 || tmpyfood>=maxheight-3)
			continue;
		food.x=tmpxfood; food.y=tmpyfood; 
		break;
	}
	move(food.y,food.x); addch(foo); refresh();
}

bool snakeclass::collision()
{
	if(snake[0].x==0 || snake[0].x==maxwidth-1 || snake[0].y==0 || snake[0].y==maxheight-1)
		return true;
		
	for(int i=2;i<snake.size();++i)
	{
		if(snake[0].x==snake[i].x && snake[0].y==snake[i].y)
			return true;
	}
	
	if(snake[0].x==food.x && snake[0].y==food.y)
	{
		get=true;
		putfood();
		points+=1;
		move(maxheight-1,0);
		printw("score: %d",points);
		if(points%GROWCHECKP==0)
		{
			int tempx,tempy;
			
			switch(direction)
			{
				case 'l': 
					tempx=snake[snake.size()-2].x+1;
					tempy=snake[snake.size()-2].y;
					break;
				case 'r': 
					tempx=snake[snake.size()-2].x-1;
					tempy=snake[snake.size()-2].y;
					break;
				case 'u': 
					tempx=snake[snake.size()-2].x;
					tempy=snake[snake.size()-2].y-1;
					break;
				case 'd': 
					tempx=snake[snake.size()-2].x;
					tempy=snake[snake.size()-2].y+1;
					break;
			
			}
			snake.push_back(snakepart(tempx,tempy));
			
		}
		
		if(points%DELAYCHECKP==0) del-=10000;
	}
	
	get=false;
	return false;

}

void snakeclass::movesnake()
{
	int tmp=getch();
	
	switch(tmp)
	{
		case KEY_UP: 
			if(direction!='d') direction='u'; break;
		case KEY_DOWN:
			if(direction!='u') direction='d'; break;
		case KEY_LEFT:
			if(direction!='r') direction='l'; break;
		case KEY_RIGHT:
			if(direction!='l') direction='r'; break;
		case 'q':
			direction='q'; break;
		case 'r':
			direction='z'; break;
	}
	if(!get)
	{
		move(snake[snake.size()-1].y,snake[snake.size()-1].x);
		addch(' ');
		refresh();
		
		snake.pop_back();
	
	}
	if(direction=='l')//****///
		snake.insert(snake.begin(),snakepart(snake[0].x-1,snake[0].y));
//		snake.push_front(snakepart(snake[0].x-1,snake[0].y));
	else if(direction=='r')//****///
		snake.insert(snake.begin(),snakepart(snake[0].x+1,snake[0].y));
//		snake.push_front(snakepart(snake[0].x+1,snake[0].y));
	else if(direction=='u')//****///
		snake.insert(snake.begin(),snakepart(snake[0].x,snake[0].y-1));	
//		snake.push_front(snakepart(snake[0].x,snake[0].y-1));
	else if(direction=='d')//****///
		snake.insert(snake.begin(),snakepart(snake[0].x,snake[0].y+1));
//		snake.push_front(snakepart(snake[0].x,snake[0].y+1));
	move(snake[0].y,snake[0].x);
	addch(partchar);
	refresh();
}

void snakeclass::start()
{
	while(1)
	{
		if(collision())
		{
			int tmp=getch();
	
			switch(tmp)
			{
				case 'q':
					direction='q'; break;
				case 'r':
					direction='z'; break;
			}
			
			move(12,36);
			printw("game over");
			
			
			if(direction=='q') break;
			else if(direction=='z')
			{
				//getch();
				system("./snake");
				break;
			}
			else continue;
		}
		movesnake();
		if(direction=='q') break;
		else if(direction=='z')
		{
			//getch();
			system("./snake");
			break;
		}
		usleep(del);
	}
}







