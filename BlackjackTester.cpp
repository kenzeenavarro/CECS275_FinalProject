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
char decision;
int askAccount();
float askBet();
int bet_money_global;
void play_again();
string account_num();
int main(){
        decision = 'y';
        Blackjack blackjack = Blackjack();
        string account = account_num();
        while(account != blackjack.account_num){
            account = account_num();
        }
        while(decision == 'y'){
            bet_money_global = blackjack.balance;
            blackjack.setBet(askBet());
            blackjack.startGame();
            blackjack.updateinfo();
            play_again();
                if (decision == 'y'){
                    blackjack.new_game();
                }   
        }
        return 0;

        
}
    

float askBet(){
    string bet;
    cout << "What is your bet?: ";
    cin >> bet;
    while (stof(bet) > bet_money_global){
        cout << "Bet has to be less than Balance of: " << bet_money_global << endl;
        cout << "New Bet: ";
        cin >> bet;
    }
    return stof(bet); 
}
void play_again(){
    cout << "Would you like to play again (y/n)?: "<<endl;
    cin >> decision;
    
}
string account_num(){
    string num;
    cout << "What is account number: ";
    cin >> num;
    return num;
}
