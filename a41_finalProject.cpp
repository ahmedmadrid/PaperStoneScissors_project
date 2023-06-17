#include <iostream>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

enum enChoice { paper = 1, stone = 2, scissors = 3 };

struct strGameData {
    int playerWinTimes{};
    int PCWinTimes{};
    int drawTimes{};
    int numberOfRounds{};
};

int howManyRounds(int from, int to, string message, string warning) {
    int n{};
    do {
        cout << endl << message << " : ";
        cin >> n;

        if (n < from || n > to)
            cout << endl << warning;
    } while (n < from || n > to);
    return n;
}

int playerChoice() {
    return howManyRounds(1, 3, "Your choice: [1]:paper, [2]: stone, [3]: scissors?","Invlaid range");
}

int getRandomNumber(int from, int to) {
    /*
    * include <cstdlib>
        srand((unsigned)time(NULL)); in main
    */
    return rand() % (to - from + 1) + from;
}

enChoice getChoice(int choice) {
    switch (choice) {
    case 1:
        return enChoice::paper;
    case 2:
        return enChoice::stone;
    case 3:
        return enChoice::scissors;
    }
}

bool playerWon (enChoice player, enChoice PC) {
    switch (player) {
    case enChoice::paper:
        if (PC == enChoice::stone)
            return true;
        break;
    case enChoice::stone:
        if (PC == enChoice::scissors)
            return true;
        break;
    case enChoice::scissors:
        if (PC == enChoice::paper)
            return true;
        break;
    }
    return false;
}

bool tie(enChoice player, enChoice PC) {
    return (player == PC);
}

void printChoice(enChoice choice) {
    string choices[] = { "paper","stone", "scissors" };
    cout << endl << "player choice: " << choices[choice-1] << endl;
}

void roundResult(enChoice player, enChoice PC, strGameData& gameData) {
    printChoice(player);
    printChoice(PC);

    if (tie(player, PC)) {
        ++gameData.drawTimes;
        system("Color 6F");
        cout << endl << "round winner: [no winner]\n";
    }
    else if (playerWon(player, PC)) {
        ++gameData.playerWinTimes;
        system("Color 2F");
        cout << endl << "round winner: player\n";
    }
    else {
        ++gameData.PCWinTimes;
        system("Color 4F");
        cout << "\a";
        cout << endl << "round winner: PC\n";
    }
}

void play(int numberofRounds, strGameData& gameData) {
    gameData.numberOfRounds = numberofRounds;
    for (int round = 0; round < numberofRounds; round++) {
        cout << endl << "____________________ round [" << round + 1 << "] begins ____________________" << endl;
        roundResult(getChoice(playerChoice()), getChoice(getRandomNumber(1, 3)), gameData);
    }
}

string printTabs(short numberOfTabs) {
    string tab{};
    for (int i = 0; i < numberOfTabs; i++)
        tab += "\t";
    return tab;
}

void showFinalWinner(strGameData gameData) {
    if (gameData.playerWinTimes > gameData.PCWinTimes)
        cout << printTabs(4) << "Final winner"<< printTabs(3) << ": Player" << endl;
    else if (gameData.PCWinTimes > gameData.playerWinTimes)
        cout << printTabs(4) << "Final winner" << printTabs(3) << ": PC" << endl;
    else
        cout << printTabs(6) << "Final winner" << printTabs(3) << ": [no winner]" << endl;
}

void gameSummary(strGameData gameData) {

    cout << endl << printTabs(6) << "---------------------------------------------------------\n";
    cout << endl << printTabs(9) << "+++ Game Over +++\n";
    cout << endl << printTabs(6) << "---------------------------------------------------------\n";
    cout << endl << printTabs(6) << "___________________ [Game Results] ___________________\n";
    cout << endl << printTabs(6) << "Game rounds" << printTabs(3) << ": " << gameData.numberOfRounds << endl;
    cout <<  printTabs(6) << "Player win times" << printTabs(2) << ": " << gameData.playerWinTimes << endl;
    cout << printTabs(6) << "PC win times" << printTabs(3) << ": " << gameData.PCWinTimes << endl;
    cout << printTabs(6) << "Draw times" << printTabs(3) << ": " << gameData.drawTimes << endl;

    showFinalWinner(gameData);
}

void resetScreen() {
    system("cls");
    system("color 0F");
}

void resetGame(strGameData& gameData) {
        gameData.numberOfRounds = 0;
        gameData.playerWinTimes = 0;
        gameData.drawTimes = 0;
        gameData.PCWinTimes = 0;
        
}

void runTheGame() {
    char ans{};
    strGameData gameData;
    do {
       play(howManyRounds(1, 10, "How many rounds do you want to play (1-10)", "Invalid range"), gameData);

       // game result
       gameSummary(gameData);

        cout << endl << printTabs(6) << "Do you want to play again (y-n)? ";
        cin >> ans;

        if (ans == 'y' || ans == 'Y') {
            resetGame(gameData);
            resetScreen();
        }
            
    } while (ans == 'y' || ans == 'Y');
}

int main()
{
    srand((unsigned)time(NULL));
    
    runTheGame();
    

}
