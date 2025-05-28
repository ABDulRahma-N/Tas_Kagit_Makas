#include <iostream>
#include<string>
#include <cstdlib> 
#include <ctime>
#include<cmath>
using namespace std;

enum engamechoice
{
    Stone = 1, Paper = 2, Scissors = 3,
};
enum enwinner
{
    Computer = 1, Player = 2, Draw = 3
};
struct stroundinfo
{
    short roundnumber = 0;
    engamechoice playerchoice;
    engamechoice computerchoice;
    enwinner winner;
    string winnername;

};

struct stgameresult
{
    short gameriund = 0;
    short playerwontimes = 0;
    short computerwontimes = 0;
    short drawtimes = 0;
    enwinner gamewinner;
    string winnername;
};

int getrandomnumber(int from, int to)
{
    int randomnum;

    randomnum = rand() % (to - from + 1) + from;

    return randomnum;
}
string winnername(enwinner winner)
{
    string arrwinnername[3] = { "Computer","Player","No one(Draw)" };

    return arrwinnername[winner - 1];
}

enwinner howwontheround(stroundinfo roundinfo)
{
    if (roundinfo.playerchoice == roundinfo.computerchoice)
    {
        return enwinner::Draw;
    }
    switch (roundinfo.playerchoice)
    {
    case engamechoice::Stone:
        if (roundinfo.computerchoice == engamechoice::Paper)
        {
            return enwinner::Computer;
        }
        break;

    case engamechoice::Paper:
        if (roundinfo.computerchoice == engamechoice::Scissors)
        {
            return enwinner::Computer;
        }
        break;

    case engamechoice::Scissors:
        if (roundinfo.computerchoice == engamechoice::Stone)
        {
            return enwinner::Computer;
        }
        break;
    }
    return enwinner::Player;
}
string Choicename(engamechoice choice)
{
    string arrygamechoice[3] = { "Stone","Paper","Scissors" };

    return arrygamechoice[choice - 1];
}
void setwinnerscreencolor(enwinner winner)
{
    switch (winner)
    {
    case enwinner::Player:
        system("color 2F");
        break;
    case enwinner::Computer:
        system("color 4F");
        break;

    case enwinner::Draw:
        system("color 6F");
        break;

    }

}

void printroundresult(stroundinfo roundinfo)
{

    cout << "\n------------Round [" << roundinfo.roundnumber << "]------------\n";
    cout << "\nPlayer choice: " << roundinfo.playerchoice;
    cout << "\nComputer choice: " << roundinfo.computerchoice;
    cout << "\nRound winner : " << roundinfo.winnername;
    cout << "\n\n---------------------------------\n";

    setwinnerscreencolor(roundinfo.winner);

}

enwinner howwonthegame(short Player1WinTimes, short ComputerWinTimes)
{
    if (Player1WinTimes > ComputerWinTimes)
    {
        return enwinner::Player;
    }
    else if (ComputerWinTimes > Player1WinTimes)
    {
        return enwinner::Computer;

    }
    else
    {
        return enwinner::Draw;
    }
}

stgameresult Fillgameresult(int gameround, short playerwontimes, short computerwontimes, short drawtimes)
{
    stgameresult gameresult;

    gameresult.gameriund = gameround;
    gameresult.computerwontimes = computerwontimes;
    gameresult.playerwontimes = playerwontimes;
    gameresult.drawtimes = drawtimes;
    gameresult.gamewinner = howwonthegame(playerwontimes, computerwontimes);
    gameresult.winnername = winnername(gameresult.gamewinner);

    return gameresult;


}

engamechoice ReadPlayer1Choice()
{
    short Choice = 1;
    do
    {
        cout << "\nYour Choice: [1]:Stone, [2]:Paper, [3]:Scissors ? ";
        cin >> Choice;

    } while (Choice < 1 || Choice >3);

    return (engamechoice)Choice;



}
engamechoice getcomputerchoice()
{
    return (engamechoice)getrandomnumber(1, 3);
}

stgameresult playgame(short howmanyrounds)
{
    stroundinfo roundinfo;
    short playerwontimes = 0, computerwontimes = 0, drawtimes = 0;

    for (short gameround = 1; gameround <= howmanyrounds; gameround++)
    {
        roundinfo.roundnumber = gameround;
        cout << "\nRound [" << roundinfo.roundnumber<< "] Started:\n";
        roundinfo.roundnumber = gameround;
        roundinfo.playerchoice = ReadPlayer1Choice();
        roundinfo.computerchoice = getcomputerchoice();
        roundinfo.winner = howwontheround(roundinfo);
        roundinfo.winnername = winnername(roundinfo.winner);

        if (roundinfo.winner == enwinner::Player)
        {
            playerwontimes++;

        }
        else if (roundinfo.winner == enwinner::Computer)
        {
            computerwontimes++;
        }
        else
        {
            drawtimes++;
        }
        printroundresult(roundinfo);
    }

    return Fillgameresult(howmanyrounds, playerwontimes, computerwontimes, drawtimes);

}

string tabs(short numberoftabs)
{
    string t = "";
    for (int i = 1; i < numberoftabs; i++)
    {
        t = t + "\t";
        cout << t;
    }

    return t;
}

void ShowGameOverScreen() {
    cout << tabs(2) << "__________________________________________________________\n\n";
    cout << tabs(2) << "                 +++ G a m e  O v e r +++\n";
    cout << tabs(2) << "__________________________________________________________\n\n";
}
void ShowFinalGameResults(stgameresult GameResults) {
    cout << tabs(2) << "_____________________ [Game Results ]_____________________\n\n";
    cout << tabs(2) << "Game Rounds        : " << GameResults.gameriund << endl;
    cout << tabs(2) << "Player1 won times  : " << GameResults.playerwontimes << endl;
    cout << tabs(2) << "Computer won times : " << GameResults.computerwontimes << endl;
    cout << tabs(2) << "Draw times         : " << GameResults.drawtimes << endl;
    cout << tabs(2) << "Final Winner       : " << GameResults.winnername << endl;
    cout << tabs(2) << "___________________________________________________________\n";
    setwinnerscreencolor(GameResults.gamewinner);
}

short ReadHowManyRounds()
{
    short GameRounds = 1;
    do {
        cout << "How Many Rounds 1 to 10 ? \n";
        cin >> GameRounds;
    } while (GameRounds < 1 || GameRounds > 10);

    return GameRounds;
}
void ResetScreen()
{
    system("cls");

    system("color f0");
}

void startgame()
{
    char playagain = 'y';

    do
    {
        ResetScreen();
        stgameresult gameresult = playgame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(gameresult);

        cout << endl << tabs(3) << "Do you want to play again? Y/N? ";
        cin >> playagain;


    } while (playagain == 'Y' || playagain == 'y');

}
int main()
{


    srand((unsigned)time(NULL));


    startgame();



    return 0;
}