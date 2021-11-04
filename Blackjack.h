/*
 * Lab 8 #1
 * This program will define class Course
 * CECS 275 - Fall 2021
 * @author Zane Navarro
 * @auhtor MacKenzee Gormican-Navarro
 * @version 1.0
 */
#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
using namespace std;

const int QUIZ_SCORES = 10;

/*
 * This C++ program displays a message.
 * CECS 275 - Fall 2021
 * Author: Zane Navarro
 * Author: MacKenzee Gormican-Navarro
 *
 */
#include <iostream>
#include <string> 
#include <map> //for dictionary equivalent in c++  
using namespace std;

class Blackjack{
    public:

        Blackjack();
        mutable string account_num;
        mutable float balance;
        mutable int games_played;
        mutable float total_loss,total_won; 
        mutable int sumDealer,sumPlayer,total;
        mutable float bet_money;
        mutable map<string,float> data;
        //void setAccount(int) const;
        void setBet(float) const;
        void hit() const;
        void stand() const;
        void split() const;
        void startGame() const;
        string HitStandSplit() const;
        void continueGame() const;
        void updateBalance() const;
        void getAccountInfo() const;
        void updateinfo() const;



    private:

        
};
#endif