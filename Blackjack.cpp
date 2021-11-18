/*
 * Lab 8 #1
 * This program defines the member functions of class Course
 * CECS 275 - Fall 2021
 * @author Zane Navarro
 * @auhtor MacKenzee Gormican-Navarro
 * @version 1.0
 */
#include "Blackjack.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map> //for dictionary equivalent in c++  
#include <sstream>
#include <locale> 
#include <algorithm>
#include <cctype>
#include <ctime>
#include <cstdlib>
#include <iomanip>
// update split and vector of char cards 

// split fixx
using namespace std;
    void Blackjack::startGame() const{
        string decision;
        deck = {1,2,3,4,5,6,7,8,9,10,11,10,10,10,1,2,3,4,5,6,7,8,9,10,11,10,10,10,1,2,3,4,5,6,7,8,9,10,11,10,10,10,1,2,3,4,5,6,7,8,9,10,11,10,10,10};
        deck_face = {'1','2','3','4','5','6','7','8','9','T','A','J','Q','K','1','2','3','4','5','6','7','8','9','T','A','J','Q','K','1','2','3','4','5','6','7','8','9','T','A','J','Q','K','1','2','3','4','5','6','7','8','9','T','A','J','Q','K'};
        //select tweo cards for user and show them (random and brand new deck 52 cards random)
        //select 2 cards again this time out of 50 and show one card
        
        this->add_cards(2,numbers_player);      // adding 2 cards to player deck
        this->add_cards(2,numbers_dealer);      // adding 2 cards to dealer hand

        this->update_sum(numbers_dealer);       //updating sum variable 
        this->update_sum(numbers_player);
        this->reveal_hand("player",numbers_player);     // show both players cards
        this->show_one_Dealer();                        // reveal one of dealers cards
        
        decision_choice(numbers_player);
        this->determine_winner(numbers_player);  // determine winner
        games_played+=1;

    }
    void Blackjack::new_game() const{
        // new deck and clear hands of dealer and players (as well as split hand)
        deck = {1,2,3,4,5,6,7,8,9,10,11,10,10,10,1,2,3,4,5,6,7,8,9,10,11,10,10,10,1,2,3,4,5,6,7,8,9,10,11,10,10,10,1,2,3,4,5,6,7,8,9,10,11,10,10,10};
        deck_face = {'1','2','3','4','5','6','7','8','9','T','A','J','Q','K','1','2','3','4','5','6','7','8','9','T','A','J','Q','K','1','2','3','4','5','6','7','8','9','T','A','J','Q','K','1','2','3','4','5','6','7','8','9','T','A','J','Q','K'};
        numbers_player.hand.erase(numbers_player.hand.begin(),numbers_player.hand.end());
        numbers_dealer.hand.erase(numbers_dealer.hand.begin(),numbers_dealer.hand.end());
        numbers_player_split.hand.erase(numbers_player_split.hand.begin(),numbers_player_split.hand.end());

        numbers_player.char_value.erase(numbers_player.char_value.begin(),numbers_player.char_value.end());
        numbers_dealer.char_value.erase(numbers_dealer.char_value.begin(),numbers_dealer.char_value.end());
        numbers_player_split.char_value.erase(numbers_player_split.char_value.begin(),numbers_player_split.char_value.end());
    }

    Blackjack::Blackjack(){  
        // when called automatically parses data from account.txt
        vector<string> info;
        fstream ifstream;
        fstream ofstream;
        string strNumber,input;
        ifstream.open("account.txt", ios::in);
        ofstream.open("logs.txt", ios::out);


        if (!ifstream){
            ofstream << "Failed to open file.";
        }
        
        int i = 0;
        for( std::string line; getline( ifstream, line); ){   // going through every line in txt file
            string x = line.substr(line.find(": ") + 1); 
            for(int y=0; y<x.size();y++){                     // erasing '$' in string 
                if(x[y] == '$'){
                    x.erase(x.begin()+y);
                }
            }
            info.push_back(x);                          // adding list to 
            i++;
        }
        //updates varaibles with values found in text file
        account_num = info.at(0);
        balance = stof(info.at(1));
        games_played = 0;
        //total_loss = stof(info.at(4));
        //total_won = stof(info.at(3));
        total_loss = 0;
        total_won = 0;

        for(int y=0; y<account_num.size();y++){                     // erasing weird space in account_num 
                if(account_num[y] == ' '){
                    account_num.erase(account_num.begin()+y);
                }
        }
    
    }

    void Blackjack::decision_choice(Person &person) const{
        string decision = HitStandSplit();
        transform(decision.begin(), decision.end(), decision.begin(),[](unsigned char c){ return std::tolower(c); });  // lower case decision string
    

            if(decision == "hit"){
                this->hit(person);
            }
            else if(decision=="stand"){
                this->stand();
            }
            else if(decision == "split"){
                this->split();
            }
            
    }
    void Blackjack::determine_winner(Person &person) const{
        // determininfg winner comparing sums of player and dealer
        // reason it is sum instead of sum_player is so i can resuse this function for split_hand and stil determine winner with one function 
        // updates global bet_money variable with either negative or positive number depending on winnning or losing so can easily just add to balance varibale and append to txt file
        // calls to update balance function which
        this->update_sum(person);
        this->update_sum(numbers_dealer);
        if(numbers_dealer.sum < 22 & (person.sum < 22) & (21-numbers_dealer.sum < 21-person.sum)){
            cout << "dealer wins"<<endl;
            bet_money = bet_money * -1;
            updateBalance();
        }
        else if((person.sum < 22 & (numbers_dealer.sum < 22) & (21-person.sum < 21-numbers_dealer.sum))){
            cout << "you win"<<endl;
            updateBalance();
        }
        else if(numbers_dealer.sum == person.sum){
            cout << "Tie"<<endl;
            bet_money =  -1 * (bet_money / 2);
            updateBalance();
             
        }
        else if(person.sum > 21 & numbers_dealer.sum <22){
            cout << "dealer wins"<<endl;
            bet_money = bet_money * -1;
            updateBalance();
        }
        else if(numbers_dealer.sum > 21 & person.sum <22){
            cout << "you win"<<endl;
        }
        else if(numbers_dealer.sum > 21 & person.sum > 21)
            if(numbers_dealer.sum < sum_player){
                cout << "dealer wins"<<endl;
                bet_money = bet_money * -1;
                updateBalance();
            }
            else if(person.sum < numbers_dealer.sum){
                cout << "you win."<<endl;
                updateBalance();
            }
    }
    void Blackjack::setBet(float bet) const{
        // setting bet_money variable
        bet_money = bet;
    }
    
    string Blackjack::HitStandSplit() const{
        // asking if hit stand or split and getting decision
        string decision;
        if(numbers_player_split.hand.size() == 0){
            cout << "Hit Stand or Split?"<<endl;
        }
        else{
            cout << "Hit or Stand"<<endl;
        }
        cin >> decision;
        return decision;
    }

    void Blackjack::hit(Person &person) const{
        // hit function takes parameter vector<int> so can use one function for hit of either split hand or main hand 
        // updates sum 
        int sum = 0;
        this->add_cards(1,person);            // adding 1 card to player deck
        this->update_sum(person);
        this->reveal_hand("player",person);


        if(person.sum <= 21 ){
            char hit_again;
            cout << "Hit Again? (y/n)"<<endl;
            cin >> hit_again;

            if(hit_again == 'y'){
                this->hit(person);    // hit again 
            }
            else{
                this->reveal_hand("dealer",numbers_dealer);         // reveals cards of dealer
                this->reveal_hand("player",person);                   // reveal cards of player
            }

        }
        else{
            this->reveal_hand("dealer",numbers_dealer);             // reveals dealers hand if over 21
        }   
    }
    void Blackjack::stand() const{
        // reveal everyones hands
        this->reveal_hand("dealer",numbers_dealer);
        this->reveal_hand("player",numbers_player);
        if(numbers_player_split.hand.size() != 0){
            this->reveal_hand("split",numbers_player_split);
        }
    }
    void Blackjack::split() const{
        this->add_cards(2,numbers_player_split);                  // adding 2 cards to split hand vector
        this->show_one_Dealer();                                  // reveal one of dealers cards        
        this->reveal_hand("player",numbers_player);
        this->reveal_hand("split",numbers_player_split);


        cout << "Hand Two: ";
        this->decision_choice(numbers_player_split); 
        this->update_sum(numbers_player_split);
        this->determine_winner(numbers_player_split); 



        this->update_sum(numbers_player);
        cout << "Hand One: ";
        this->reveal_hand("player",numbers_player);
        this->decision_choice(numbers_player);          
    }

    void Blackjack::updateBalance() const{   
        if(bet_money > 0){
            total_won += bet_money;
        }
        else if(bet_money < 0){
            total_loss += (-1*bet_money);
        }
        balance = balance + bet_money;
        
    }
    void Blackjack::updateinfo() const{         // updating account.txt file with info

        fstream ofstream;
        ofstream.open("account.txt", ios::out);
        map<string, float>::iterator it;
        ofstream << "Account Number"<< ": "<< account_num << endl;
        ofstream.precision(2);
        ofstream << "Current Balance"<< ": $"<<fixed<< balance << endl;
        ofstream.precision(0);
        ofstream << "Game Played"<< ": "<<games_played << endl;
        ofstream.precision(2);
        ofstream << "Total Amount Won"<< ": $"<< fixed<<total_won<< endl;
        ofstream << "Total Amount Loss"<< ": $"<<total_loss << endl;    
    }
    void Blackjack::displayaccount() const{         // updating account.txt file with info

        // fstream ofstream;
        // ofstream.open("account.txt", ios::out);
        // map<string, float>::iterator it;
        cout << "Account Number"<< ": "<< account_num << endl;
        cout.precision(2);
        cout << "Current Balance"<< ": $"<<fixed<< balance << endl;
        cout.precision(0);
        cout << "Game Played"<< ": "<<games_played << endl;
        cout.precision(2);
        cout << "Total Amount Won"<< ": $"<< fixed<<total_won<< endl;
        cout << "Total Amount Loss"<< ": $"<<total_loss << endl;    
    }
 
    
    void Blackjack::show_one_Dealer()const{
        cout << "Dealer's cards: " << endl;
        cout << "----------" << endl;
        cout << "| " << numbers_dealer.hand.at(0) << setw(7) << "|" << endl;
        cout << "|" << setw(9) << "|" << endl;
        cout << "|" << setw(9) << "|" << endl;
        cout << "|" << setw(9) << "|" << endl;
        cout << "|" << setw(9) << "|" << endl;
        cout << "|" << setw(8) << numbers_dealer.hand.at(0) << "|" << endl;
        cout << "----------" << endl;
    }

    int Blackjack::randnum() const{
        srand((unsigned) time(0));
        int randomNumber;
        for (int index = 0; index < 1000; index++) {
            randomNumber = (rand() % deck.size()) ;
        }
        return randomNumber;
    }
    void Blackjack::add_cards(int num, Person &person ) const{
        for (int i=0;i<num;i++){
            int value = this->randnum();          // picking index of rest of deck left
            person.hand.push_back(deck.at(value));                  // add players number to vector hand
            person.char_value.push_back(deck_face.at(value));       // add players value to char_value vector
            deck.erase(deck.begin()+value);                         // erasing deck value from deck so not to be reused 
            deck_face.erase(deck_face.begin()+value);               // erasing deck value from deck so not to be reused 
        }
    }
    void Blackjack::reveal_hand(string person,Person &person_hand) const{
        if(person == "dealer"){ 
            cout << "Dealers Cards: ";
        }
        else if(person == "player"){
            cout << "Your Cards: ";
        }
        else if(person == "split"){
            cout << "Your Other Cards: ";
        }

        for(int i=0;i<person_hand.char_value.size();i++){
            if(person_hand.char_value.at(i) == 'T'){
                cout << "10" << " ";
            }
            else{
                cout << endl;
                cout << "----------" << endl;
                cout << "| " << person_hand.char_value.at(i) << setw(7) << "|" << endl;
                cout << "|" << setw(9) << "|" << endl;
                cout << "|" << setw(9) << "|" << endl;
                cout << "|" << setw(9) << "|" << endl;
                cout << "|" << setw(9) << "|" << endl;
                cout << "|" << setw(8) << person_hand.char_value.at(i) << "|" << endl;
                cout << "----------" << endl;
            }
            
        }
        cout <<endl;  
    }
    void Blackjack::update_sum(Person &person)const{
        person.sum = 0;
        for(int i=0; i<person.hand.size();i++){
            if(person.char_value.at(i) == 'A'){
                if(person.sum += person.hand.at(i) > 21){
                    person.sum += 1;
                }
                else{
                    person.sum += person.hand.at(i);
                }
            }
            else{
                person.sum += person.hand.at(i);
            }
           
        }

    }

    