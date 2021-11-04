/*
 * Lab 8 #1
 * This program will test class Date
 * CECS 275 - Fall 2021
 * @author Zane Navarro
 * @auhtor MacKenzee Gormican-Navarro
 * @version 1.0
 */
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>
#include "Blackjack.h"


/*
* @param ex1       instance of Date class
* @param month     int month to hold user input of month
* @param day       int day to hold user input of day
* @param year      int year to hold user input of year
*/
int askAccount();
float askBet();
int main(){
    Blackjack blackjack = Blackjack();
    //blackjack.setAccount(askAccount());
    blackjack.setBet(askBet());
    cout <<  blackjack.bet_money <<endl;

    //cout << blackjack.account_num<<endl;
    //cout << blackjack.bet_money <<endl;
    //blackjack.getAccountInfo();
    blackjack.updateinfo();
    cout << "Account nuM: "<<blackjack.account_num << endl;
    cout<<"BALCANCE: "<<blackjack.balance<<endl;
    cout << "Games Played: " <<    blackjack.games_played<< endl;
    cout << "Total Loss: " <<  blackjack.total_loss << endl;
    cout << "Total Won: "<<   blackjack.total_won <<endl;
    blackjack.startGame();
}

float askBet(){
    string bet;
    cout << "What is your bet?";
    cin >> bet;
    return stof(bet); 
}
