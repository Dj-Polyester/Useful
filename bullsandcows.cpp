#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>


using namespace std;

class game
{
    size_t levels,attempts,lettercount,score,bulls,cows;
    string word;
    
     
    public:
        game(size_t lwls,size_t attmpts,size_t lttrcnt);
        bool play();
        ~game();
        string choose(size_t data);
        size_t Bulls(string str,string wrd);
        size_t Cows(string str,string wrd);
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
/* 
bool game::check_repeat(string str)
{
    vector<size_t> repeat;
    for(size_t i=0;i<str.size();++i)
    {
        //in repeat
        if(find(repeat.begin(), repeat.end(), str[i]) != repeat.end()) return true;
        repeat.push_back(str[i]);
    }

    return false;
}
*/
string game::choose(size_t data)
{
    size_t count;
    string three[20]={"hob","hat","icy","tip","rho","wet","beg","tom","vow","ohm","him","dis","fob","fry","aye","fig","net","nib","hot","can"};
    string four[13]={"lair","time","dunk","idea","lute","trap","clam","desk","lyre","maze","rice","moat","take"};
    string five[13]={"magic","voice","venom","blame","warps","adopt","foamy","cumin","daily","gourd","brawn","scalp","stunt"};
    string six[10]={"resign","linage","piracy","diaper","preach","fridge","modify","gazebo","unmask","squeak"};
    string seven[5]={"grimace","swathed","wearily","raceway","several"};
    string eight[4]={"thursday","thousand","chipotle","violence"};
    string nine[5]={"tremulous","something","dangerous","masculine","wrestling"};
    string ten[14]={"instalment","rediscover"};
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
        cout << endl << "You won!" << endl;
    }
    else
    {
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
    
    word=choose(lettercount);
    cout << "Guess the " << lettercount << " letter hidden word: " << endl;
    cout << "You have " << attempts << " attempts: " << endl;
	
    cout << word << endl;
    getline(cin,guess);

    

   
   
    //continue playing
     if(guess!=word)
    {
        
        while (guess!=word)
        {
            bulls=Bulls(guess,word);
    	    cows=Cows(guess,word);

    	    cout << endl << cows << " cows" << endl;
    	    cout << bulls << " bulls" << endl;
    	    
            --attempts;
            if(!attempts) break;
            cout << "Incorrect answer. Try again. " << attempts << " attempts remaining." << endl;
            getline(cin,guess);
        }
        
        if(attempts) attempts=tmp;
    }
    
    if(guess==word)
    {
        cout << "Congratulations. Correct answer." << endl;
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
