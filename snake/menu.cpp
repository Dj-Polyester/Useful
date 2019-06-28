#include <ncurses.h>
#include <string>

class page
{
	private:
		string* options;
	public:
		void page(string* choices,size_t size);
		void ~page();
}

page::choose(WINDOW* win, string chosen)
{
	werase(win);
	delwin(win);
	
	if(chosen=="play")
	{
		system("./snake");
	}
	
	else if(chosen!="quit")
	{
	
	}
	
	

}


page::page(string* choices, size_t size)
{
	initscr();
	noecho();
	cbreak();
	
	
	getmaxyx(stdscr,maxheight,maxwidth);
	
	options=choices;
	choices=NULL;
	
	WINDOW* win=newwin(0,0,0,0);
	box(win,0,0);
	refresh();
	wrefresh(win);
	
	keypad(win,true);
	
	int choice,highlight=0;
	
	while(1)
	{
		
		for(size_t i=0;i<size;++i)
		{
			if(i==highlight)
			{
				wattron(win,A_REVERSE);
				mvwprintw(win,maxwidth,maxheight/2+i,choices[i].c_str());
				wattroff(win,A_REVERSE);
			}
			choice=wgetch(win);
			int lastindex=options[highlight].length()-1;
			char last=options[lastindex]-48;
			switch(choice)
			{
				case KEY_UP: highlight--; break;
				case KEY_DOWN: highlight++; break
				case KEY_LEFT: 
					if(last<11 && last >-1) if(last!=0) --last; break;
				case KEY_RIGHT:  
					if(last<10 && last >-1) if(last!=10) ++last; break;
				case 10: page.choose(win,options[highlight]); break;
				case 'q': break;
				
			}
			
		}
	
	}

} 

page::~page()
{
	getch();
	endwin();

}


int main()
{
	page menu();





}
