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
using namespace std;

class Blackjack{
    public:

        Blackjack();
        mutable string account_num;
        mutable int bet_money,sumDealer,sumPlayer,total;
        void setAccount(string) const;
        void setBet(int) const;
        void startGame() const;
        string HitStandSplit() const;
        void continueGame() const;
        void updateBalance(int) const;


    private:

        
};
#endif