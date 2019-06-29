#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class game
{
    int levels,attempts,lettercount,score;

    vector<vector<int> > scoreboard;
     vector<string> answers;
    public:
        game(int lwls,int attmpts,int lttrcnt);
        bool play();
        ~game();
        void choose(string str,int data);
        int Bulls(string str,string wrd);
        int Cows(string str,string wrd);

};

void game::choose(string str,int data)
{
    string three[24]={"hob","bee","hat","icy","tip","rho","wet","beg","tom","vow","ohm","him","all","dis","fee","fob","fry","aye","fig","net","nib","wee","hot","can"};
    string four[15]={"lair","time","dunk","idea","lute","trap","clam","desk","lyre","maze","rice","moat","take","ammo","good"};
    string five[20]={"magic","voice","sooth","venom","cakes","blame","aurae","refer","based","warps","adopt","foamy","cumin","daily","gourd","abbey","kayak","brawn","scalp","stunt"};
    string six[20]={"resign","ticket","wheels","linage","piracy","diaper","uterus","grungy","caches","tamale","preach","delays","fridge","upkeep","modify","gazebo","plaids","unmask","peddle","squeak"};
    string seven[12]={"grimace","swathed","foolery","walkers","tempter","kumquat","kernels","lazying","wearily","raceway","several","sellout"};
    string eight[5]={"leniency","practice","apposite","automate","tutorial"};
    string nine[8]={"tremulous","mortgagor","anomalous","bombastic","guarantee","fluctuate","malicious","rapacious"};
    string ten[14]={"monsignori","instalment","nincompoop","conversion","knighthood","forerunner","crossbreed","insecurity","settlement","likelihood","amateurism","rediscover","theocratic","enchiladas"};
    string* strvar;
    int size=str.size(),count;

    if(size==3)
    {
        strvar=three;
        count=24;
    }
    else if(size==4) 
    {
         strvar=four;
          count=15;
    }
   
    else if(size==5) 
    {
        strvar=five;
         count=20;
    }
    else if(size==6) 
    {
         strvar=six;
          count=20;
    }
    else if(size==7) 
    {
        strvar=seven;
         count=12;
    }
    else if(size==8) 
    {
        strvar=eight;
         count=5;
    }
    else if(size==9) 
    {
        strvar=nine;
        count=8;
    }
    else if(size==10) 
    {
        strvar=ten;
        count=14;
    }

    int i=rand()%count;
    str=strvar[i];  
}

game::game(int lwls,int attmpts,int lttrcnt)
{
     srand(time(NULL));
     // 0<=levels<=7               0<=lettercount<=7
    levels=rand()%lwls,attempts=attmpts,lettercount=lttrcnt,score=0;

    while(play());

}

game::~game()
{
    if(score==levels)
    {
        cout << "You won!" << endl;
    }
    else
    {
        cout << "You lost!" << endl;
    }
    cout << "Correct answers:" << endl;
    for(int i=0;i<levels;++i)
    {
        cout << answers[i];
        if(i<=score) cout << "Q" << i+1 << "      Bulls: " << scoreboard[i][0] <<  "Cows: " << scoreboard[i][1] ;
        if(i==score) cout << "<-your score" ;
        cout << endl;
    }

}


bool game::play()
{
     //lose or win
     int tmp=attempts;
     string word,guess;
    if(!attempts || score==levels)
    {
         return 0;   
    }
    
    choose(word,lettercount);
    cout << "Guess the" << lettercount << "letter hidden word: " << endl;
    cout << "You have" << attempts << "attempts remaining: " << endl;

    getline(cin,guess);

    int bulls=Bulls(guess,word);
    int cows=Cows(guess,word);

    cout << endl << cows << "cows" << endl;
    cout << bulls << "bulls" << endl;

   
   
    //continue playing
    if(guess==word)
    {
        score++;
        if(!(score%2)) attempts+=2;
        vector<int> temp;
        temp.push_back(bulls);
        temp.push_back(cows);
        answers.push_back(word);

        return 1;
    }
    else
    {
        --attempts;
        while (guess!=word )
        {
            cout << "Wrong answer. Try again." << attempts << "Attempts remaining." << endl;
            getline(cin,guess);
        }
        if(attempts) attempts=tmp;

        return 1;
    }
    
    
    return 1;
}


int game::Bulls(string str,string wrd)
{
    int count=0;
    for(int i=0;i<str.size();++i)
    {
        if(str[i]==wrd[i]) ++count;

    }

    return count;
}

int game::Cows(string str,string wrd)
{
    int count=0;
    vector<int> table;

    for(int i=0;i<str.size();++i)
    {
        for(i=0;i<wrd.size();++i)
        {
             if(str[i]==wrd[i] && find(table.begin(), table.end(), i) == table.end())
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
    
    game Game(8,2,3);
    cin.get();
    return 0;
}