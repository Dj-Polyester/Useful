#include "clock.h"


using namespace std;

void clockmenu(clock_time* ptr); 
 

bool timer;
size_t max_x,max_y,mid_x,mid_y;
void mainmenu(clock_time* ptr)
{
    WINDOW *w;
    clock_time clock_time;
    char list[OPTIONS][MAX_LEN] = { "timer", "chronometer" };
    char item[MAX_LEN];
    size_t ch,max_len=MAX_LEN;
    int i;
    
    initscr(); // initialize Ncurses
    getmaxyx(stdscr,max_y,max_x); mid_x=max_x/2;mid_y=max_y/2;
    w = newwin( OPTIONS+2, max_len+2, mid_y-OPTIONS/2, mid_x-MAX_LEN/2); // create a new window
    box( w, 0, 0 ); // sets default borders for the window
     
// now print all the menu items and highlight the first one
    for( i=0; i<OPTIONS; i++ ) {
        if( i == 0 ) 
            wattron( w, A_STANDOUT ); // highlights the first item.
        else
            wattroff( w, A_STANDOUT );
        sprintf(item, SPRINTF(12),  list[i]);
        mvwprintw( w, i+1, 1, "%s", item );
    }
 
    wrefresh( w ); // update the terminal screen
 
    i = 0;
    noecho(); // disable echoing of characters on the screen
    keypad( w, TRUE ); // enable keyboard input for the window.
    curs_set( 0 ); // hide the default screen cursor.
     
       // get the input
    while(( ch = wgetch(w)) != 'q' ){ 
         
                // right pad with spaces to make the items appear with even width.
            sprintf(item, SPRINTF(12),  list[i]); 
            mvwprintw( w, i+1, 1, "%s", item ); 
              // use a variable to increment or decrement the value based on the input.
            switch( ch ) {
                case KEY_UP:
                            i--;
                            i = ( i<0 ) ? OPTIONS-1 : i;
                            break;
                case KEY_DOWN:
                            i++;
                            i = ( i>OPTIONS-1  ) ? 0 : i;
                            break;
                
                
            }
            // now highlight the next item in the list.
            wattron( w, A_STANDOUT );
             
            sprintf(item, SPRINTF(12),  list[i]);
            mvwprintw( w, i+1, 1, "%s", item);
            wattroff( w, A_STANDOUT );
            ///////////////////////specific
            
            
            if(ch==10)
            {
            	timer=i;
            	werase(w);
            	wrefresh(w);
            	delwin( w );
            	clockmenu(ptr);
            }
            ///////////////////////
    }
 
   
    endwin();


}

void clockmenu(clock_time* ptr)
{
	WINDOW *w;
    	int list[4]={0,0,0,0};
    	clock_time clock_time;
    	size_t ch;
    	 int i;
    	 
    	w = newwin( 3, 13, mid_y-OPTIONS/2, mid_x-MAX_LEN/2); // create a new window
    	box( w, 0, 0 ); // sets default borders for the window
    	// now print all the menu items and highlight the first one
    	for( i=0; i<3; i++ ) {
        if( i == 0 ) 
            wattron( w, A_STANDOUT ); // highlights the first item.
        else
            wattroff( w, A_STANDOUT );
        
        mvwprintw( w, 1, 3*i+1, "%02d:", list[i] );
    }
	mvwprintw( w, 1, 3*i+1, "%02d", list[i] );
	
	wrefresh( w ); // update the terminal screen
	
	i = 0;
    noecho(); // disable echoing of characters on the screen
    
    keypad( w, TRUE ); // enable keyboard input for the window.
    curs_set( 0 ); // hide the default screen cursor.
    cbreak();
    
    
    
    
           while(( ch = wgetch(w)) != 'q' ){ 
         
                // right pad with spaces to make the items appear with even width.
           wrefresh( w );
            mvwprintw( w, 1, 3*i+1, "%02d", list[i] );
              // use a variable to increment or decrement the value based on the input.
            switch( ch ) {
                case KEY_UP:
                            ++list[i];
                            if(i==3) list[i] = ( list[i]>9 ) ? 0 : list[i];
                            else list[i] = ( list[i]>59 ) ? 0 : list[i];
                            break;
                case KEY_DOWN:
                            --list[i];
                            if(i==3) list[i] = ( list[i]<0  ) ? 9 : list[i];
                            else list[i] = ( list[i]<0  ) ? 59 : list[i];
                            break;
                case KEY_RIGHT:
                            i++;
                            i = ( i>3 ) ? 0 : i;
                            break;
                case KEY_LEFT:
                            i--;
                            i = ( i<0  ) ? 3 : i;
                            break;
                case 'r': remove("count.txt"); break;
               
                case ENTER:
                	   if(timer) ptr->chronomtr(list[0],list[1],list[2],list[3],true,w);
            		   else ptr->Timer(list[0],list[1],list[2],list[3],true,w);
            		   ptr->set(list[0],list[1],list[2],list[3]);
            		   ptr->print(w);
            		   break;
            	default: break;   
            }
            
            // now highlight the next item in the list.
            wattron( w, A_STANDOUT );
             
           
            mvwprintw( w, 1, 3*i+1, "%02d", list[i] );
            wattroff( w, A_STANDOUT );
            wrefresh(w);
    }
 
    endwin(); 
    mainmenu(ptr);
}

int main() {clock_time tmp; mainmenu(&tmp);}




