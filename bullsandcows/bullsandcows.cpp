#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include "filelist.h"

using namespace std;

class game
{
    size_t levels,attempts,lettercount,score,bulls,cows;
    string word;
    
     
    public:
        game(size_t lwls,size_t attmpts,size_t lttrcnt);
        bool play();
        ~game();
        size_t Bulls(string str,string wrd);
        size_t Cows(string str,string wrd);
        string choose(string filename,size_t data);
        /*
        void setLevels(size_t x) {levels=x};
        void setAttempts(size_t x) {attempts=x};
       void setLettercount(size_t x) {lettercount=x};
       void setScore(size_t x) {score=x};
        size_t getLevels() {return levels};
        size_t getAttempts() {return attempts};
       size_t getLettercount() {return lettercount};
       size_t getScore() {return score};
       */

};

string game::choose(string filename,size_t data)
{
	size_t line=data-2, length=countWords(line_in_file(filename,line)), n=rand()%length;
	
	return word_in_file(filename,line,n);

}

/*
string game::choose(size_t data)
{
    size_t count;
    string three[24]={"hob","bee","hat","icy","tip","rho","wet","beg","tom","vow","ohm","him","all","dis","fee","fob","fry","aye","fig","net","nib","wee","hot","can"};
    string four[15]={"lair","time","dunk","idea","lute","trap","clam","desk","lyre","maze","rice","moat","take","ammo","good"};
    string five[20]={"magic","voice","sooth","venom","cakes","blame","aurae","refer","based","warps","adopt","foamy","cumin","daily","gourd","abbey","kayak","brawn","scalp","stunt"};
    string six[20]={"resign","ticket","wheels","linage","piracy","diaper","uterus","grungy","caches","tamale","preach","delays","fridge","upkeep","modify","gazebo","plaids","unmask","peddle","squeak"};
    string seven[12]={"grimace","swathed","foolery","walkers","tempter","kumquat","kernels","lazying","wearily","raceway","several","sellout"};
    string eight[5]={"leniency","practice","apposite","automate","tutorial"};
    string nine[8]={"tremulous","mortgagor","anomalous","bombastic","guarantee","fluctuate","malicious","rapacious"};
    string ten[14]={"monsignori","instalment","nincompoop","conversion","knighthood","forerunner","crossbreed","insecurity","settlement","likelihood","amateurism","rediscover","theocratic","enchiladas"};
    string* strvar;

    if(data==3)
    {
        strvar=three;
        count=24;
    }
    else if(data==4) 
    {
         strvar=four;
          count=15;
    }
   
    else if(data==5) 
    {
        strvar=five;
         count=20;
    }
    else if(data==6) 
    {
         strvar=six;
          count=20;
    }
    else if(data==7) 
    {
        strvar=seven;
         count=12;
    }
    else if(data==8) 
    {
        strvar=eight;
         count=5;
    }
    else if(data==9) 
    {
        strvar=nine;
        count=8;
    }
    else if(data==10) 
    {
        strvar=ten;
        count=14;
    }

    size_t i=rand()%count;  
    
    return strvar[i];
}
*/
game::game(size_t lwls,size_t attmpts,size_t lttrcnt)
{
     srand(time(NULL));
     // 0<=levels<=7               0<=lettercount<=7
    levels=lwls,attempts=attmpts,lettercount=lttrcnt,score=0;

    while(play());

}

game::~game()
{
    if(score==levels)
    {
        cout << "oooooooooooooooooooooooooooooooooooooooooooooooo";
        cout << endl << "You won!" << endl;
    }
    else
    {
        cout << "################################################";
        cout << endl << "You lost!" << " The answer was "<< word << endl;
      
    }
}


bool game::play()
{
     //lose or win
     size_t tmp=attempts;
     string guess;
    if(!attempts || score==levels)
    {
         return 0;   
    }
            
    cout << "?<<<<<<<<<<<<<<<<<<<<<<o>>>>>>>>>>>>>>>>>>>>>>>?";
    
    word=choose("words.txt",lettercount);
    cout << endl << "Guess the " << lettercount << " letter hidden word: " << endl;
    cout << endl <<  "You have " << attempts << " attempts: " << endl;
	
    cout << word << endl;
    getline(cin,guess);

    

   
   
    //continue playing
     if(guess!=word)
    {
        
        while (guess!=word)
        {
            cout << "!<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<";
            bulls=Bulls(guess,word);
    	    cows=Cows(guess,word);

    	    cout << endl << cows << " cows" << endl;
    	    cout << bulls << " bulls" << endl;
    	    
            --attempts;
            if(!attempts) break;
            else if(attempts==1)  cout << endl << "Inorrect answer. Try again. You have a single attempt left." << endl;
            else  cout << endl << "Inorrect answer. Try again. " << attempts << " attempts left." << endl;
           
            getline(cin,guess);
        }
        
        if(attempts) attempts=tmp;
    }
    
    if(guess==word)
    {
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>!";
        cout << endl << "Congratulations. Correct answer." << endl;
        ++score;
        ++lettercount;
        if(!(score%2)) attempts+=2;

        return 1;
    }
   
    
    
    return 1;
}


size_t game::Bulls(string str,string wrd)
{
    size_t count=0;
    for(size_t i=0;i<str.size();++i)
    {
        if(str[i]==wrd[i]) ++count;

    }

    return count;
}

size_t game::Cows(string str,string wrd)
{
    size_t count=0;
    vector<size_t> table;

    for(size_t i=0;i<str.size();++i)
    {
        for(size_t j=0;j<wrd.size();++j)
        {
             if(str[i]==wrd[j] && find(table.begin(), table.end(), j) == table.end() && i!=j)
             {
                 ++count;
                 table.push_back(i);
             }
             
            
        }
        
    }
    
    return count;
}

int main()
{
    size_t lwl;
    cout << "Choose your level: ";
    cin >> lwl;
    getchar();
    
    game Game(lwl,2,3);
   
    return 0;
}
