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
#include <vector>
#include <string> 
#include <map> //for dictionary equivalent in c++  
using namespace std;

class Blackjack{
    public:
        struct Person{
            mutable int sum;
            mutable vector<int> hand;
            mutable vector<char> char_value;
        };
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
        void hit(Person &) const;
        void stand() const;
        void split() const;
        void startGame() const;
        string HitStandSplit() const;
        void updateBalance() const;
        void updateinfo() const;
        int randnum() const;
        void determine_winner(Person &) const;
        void new_game() const;
        void displayaccount() const;



    private:
        mutable vector<int> deck;
        mutable vector<char> deck_face;
        mutable int sum_player,sum_player_split,sum_dealer;
        //mutable vector<int> numbers_player, numbers_player_split,numbers_dealer;

        // struct Person{
        //     mutable vector<int> hand;
        //     mutable vector<char> char_value;
        // };

        mutable Person numbers_player;
        mutable Person numbers_player_split;
        mutable Person numbers_dealer;
        

        // mutable vector<char> numbers_player_value;
        // mutable vector<char> numbers_player_split_value;
        // mutable vector<char> numbers_dealer_value;


        // void update_sum_player() const;
        // void update_sum_dealer() const;
        void show_one_Dealer() const;
        void add_cards(int, Person &) const;
        void reveal_hand(string,Person &) const;
        //void decision_choice(vector<int> &) const;
        void decision_choice(Person &) const;
        //void update_sum_player_split() const;
        void update_sum(Person &) const;
        
        
        

        
};
#endif