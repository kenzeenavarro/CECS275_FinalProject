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

using namespace std;
    void Blackjack::startGame() const{
        string decision;
        //already asked for bet_money
        // NOTE deck value global count
        //select tweo cards for user and show them (random and brand new deck 52 cards random)
        //select 2 cards again this time out of 50 and show one card
        decision = HitStandSplit();
        transform(decision.begin(), decision.end(), decision.begin(),[](unsigned char c){ return std::tolower(c); });  // lowering decision
        if(decision == "hit"){
            this->hit();
        }
        else if(decision=="stand"){
            this->stand();
        }
        else if(decision == "split"){
            this->split();
        }
        
        //show value again and ask if user wants to hit or stand or split HitStandSplit()
        // split it up into 3 different fuinctions
        // take string and have if statement for each function of hit stand split 

    }

    Blackjack::Blackjack(){
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
        
        account_num = info.at(0);
        balance = stof(info.at(1));
        games_played = stoi(info.at(2));
        total_loss = stof(info.at(3));
        total_won = stof(info.at(4));

        for(int y=0; y<account_num.size();y++){                     // erasing weird space in account_num 
                if(account_num[y] == ' '){
                    account_num.erase(account_num.begin()+y);
                }
        }
    
    }
    // void Blackjack::setAccount(int num) const{
    //     account_num = num;
    // }
    void Blackjack::setBet(float bet) const{
        bet_money = bet;
    }
    
    string Blackjack::HitStandSplit() const{
        string decision;
        cout << "Hit Stand or Split?"<<endl;
        cin >> decision;
        return decision;
    }
    void Blackjack::hit() const{

    }
    void Blackjack::stand() const{

    }
    void Blackjack::split() const{

    }
    void Blackjack::continueGame() const{

    }
    void Blackjack::updateBalance() const{   



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
        ofstream << "Total Amount Won"<< ": $"<< fixed<<total_loss<< endl;
        ofstream << "Total Amount Loss"<< ": $"<<total_won << endl;    
    }

    
    void Blackjack::getAccountInfo()const{
        
    }

    