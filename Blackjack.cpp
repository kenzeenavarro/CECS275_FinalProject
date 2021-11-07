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

using namespace std;
    void Blackjack::startGame() const{
        string decision;
        deck = {1,2,3,4,5,6,7,8,9,10,11,10,10,1,2,3,4,5,6,7,8,9,10,11,10,10,1,2,3,4,5,6,7,8,9,10,11,10,10,1,2,3,4,5,6,7,8,9,10,11,10,10};
        //already asked for bet_money
        // NOTE deck value global count
        // NOTE sum of users card global
        // NOTE
        //select tweo cards for user and show them (random and brand new deck 52 cards random)
        //select 2 cards again this time out of 50 and show one card
        
       
        this->add_cards(2,numbers_player);      // adding 2 cards to player deck
        this->add_cards(2,numbers_dealer);      //adding 2 cards to dealer hand
        this->update_sum_player();              // updating sum varibale from player
        this->update_sum_dealer();
        this->reveal_hand("player",numbers_player);            // show both players cards
        this->show_one_Dealer();                // reveal one of dealers cards
        
        decision_choice(numbers_player);
        this->determine_winner(sum_player);  // determine winner
        
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
        total_loss = stof(info.at(4));
        total_won = stof(info.at(3));

        for(int y=0; y<account_num.size();y++){                     // erasing weird space in account_num 
                if(account_num[y] == ' '){
                    account_num.erase(account_num.begin()+y);
                }
        }
    
    }
    // void Blackjack::setAccount(int num) const{
    //     account_num = num;
    // }
    void Blackjack::decision_choice(vector<int> &hand) const{
        string decision = HitStandSplit();
        transform(decision.begin(), decision.end(), decision.begin(),[](unsigned char c){ return std::tolower(c); });  // lowering decision
        

        if(decision == "hit"){
            this->hit(hand);
        }
        else if(decision=="stand"){
            this->stand();
        }
        else if(decision == "split"){
            this->split();
        }
        
    }
    void Blackjack::determine_winner(int sum) const{
        // this->update_sum_dealer();
        // this->update_sum_player();
        // this->update_sum_player_split();


        if(sum_dealer < 22 & (sum < 22) & (21-sum_dealer < 21-sum)){
            cout << "dealer wins"<<endl;
            bet_money = bet_money * -1;
            updateBalance();
        }
        else if((sum < 22 & (sum_dealer < 22) & (21-sum < 21-sum_dealer))){
            cout << "you win"<<endl;
            updateBalance();
        }
        else if(sum_dealer == sum){
            cout << "Tie"<<endl;
            bet_money =  -1 * (bet_money / 2);
            updateBalance();
             
        }
        else if(sum > 21 & sum_dealer <22){
            cout << "dealer wins"<<endl;
            bet_money = bet_money * -1;
            updateBalance();
        }
        else if(sum_dealer > 21 & sum <22){
            cout << "you win"<<endl;
        }
        else if(sum_dealer > 21 & sum > 21)
            if(sum_dealer < sum_player){
                cout << "dealer wins"<<endl;
                bet_money = bet_money * -1;
                updateBalance();
            }
            else if(sum < sum_dealer){
                cout << "you win."<<endl;
                updateBalance();
            }
    }
    void Blackjack::setBet(float bet) const{
        bet_money = bet;
    }
    
    string Blackjack::HitStandSplit() const{
        string decision;
        cout << "Hit Stand or Split?"<<endl;
        cin >> decision;
        return decision;
    }
    void Blackjack::hit(vector<int> &hand) const{
        int sum =0;
        this->add_cards(1,hand);            // adding 1 card to player deck
        this->update_sum_player();          // updating sum varibale from player
        this->update_sum_player_split();
        this->reveal_hand("player",hand);
        for(int i =0;i<hand.size();i++){
            sum += hand.at(i);
        }

        if(sum <= 21 ){
            char hit_again;
            cout << "Hit Again? (y/n)"<<endl;
            cin >> hit_again;

            if(hit_again == 'y'){
                this->hit(hand);    // hit again 
            }
            else{
                //this->reveal_dealer();     // reveal remaining cards of dealer
                this->reveal_hand("dealer",numbers_dealer);
                //this->reveal_hand("player",numbers_player);
                this->reveal_hand("player",hand);
                //this->determine_winner();  // determine winner
            }

        }
        else{
            //this->reveal_dealer();     // reveal remaining cards of dealer
            this->reveal_hand("dealer",numbers_dealer);
            //this->determine_winner();  // determine winner

        }
        // if sum hand < 21 then select another card from deck value (rest of whatever is left of deck)
        // then if sum of al 3 cards are above 21 reveal remaining card of dealer and determine winnenr
        
    }
    void Blackjack::stand() const{
        //this->reveal_player();
        //this->reveal_dealer();     // reveal remaining cards of dealer
        this->reveal_hand("dealer",numbers_dealer);
        this->reveal_hand("player",numbers_player);
        this->reveal_hand("split",numbers_player_split);

        //this->determine_winner();  // determine winner
    }
    void Blackjack::split() const{
        this->add_cards(2,numbers_player_split);      //adding 2 cards to dealer hand
        this->reveal_hand("dealer",numbers_dealer);
        this->reveal_hand("player",numbers_player);
        this->reveal_hand("split",numbers_player_split);


        cout << "Hand Two: ";
        this->decision_choice(numbers_player_split); 
        this->update_sum_player_split();
        this->determine_winner(sum_player_split); 


        this->update_sum_player();
        cout << "Hand One: ";
        this->reveal_hand("player",numbers_player);
        this->decision_choice(numbers_player);          
    }

    void Blackjack::continueGame() const{

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
    void Blackjack::update_sum_player()const{
        sum_player = 0;
        for(int i=0; i<numbers_player.size();i++){
            sum_player += numbers_player.at(i);
            
        }

    }
    void Blackjack::update_sum_player_split()const{
        sum_player_split = 0;
        for(int i=0; i<numbers_player_split.size();i++){
            sum_player_split += numbers_player_split.at(i);
        }
    }
    
    void Blackjack::show_one_Dealer()const{
        cout << "Dealers Card: "<<numbers_dealer.at(0)<<endl;
    }

    void Blackjack::update_sum_dealer()const{
        sum_dealer = 0;
        for(int i=0; i<numbers_dealer.size();i++){
            sum_dealer += numbers_dealer.at(i);
        }
    }
    
    void Blackjack::getAccountInfo()const{
        
    }
    int Blackjack::randnum() const{
        srand((unsigned) time(0));
        int randomNumber;
        for (int index = 0; index < 1000; index++) {
            randomNumber = (rand() % deck.size()) ;
        }
        return randomNumber;
    }
    void Blackjack::add_cards(int num, vector <int> &hand ) const{
        for (int i=0;i<num;i++){
            int value = this->randnum();          // picking index of rest of deck left
            hand.push_back(deck.at(value));       // add players number
            deck.erase(deck.begin()+value);                 // erasing deck value from deck so not to be reused 
        }
    }
    void Blackjack::reveal_hand(string person,vector<int> &hand) const{
        if(person == "dealer"){ 
            cout << "Dealers Cards: ";
        }
        else if(person == "player"){
            cout << "Your Cards: ";
        }
        else if(person == "split"){
            cout << "Your Other Cards: ";
        }

        for(int i=0;i<hand.size();i++){
            cout << hand.at(i) << " ";
        }
        cout <<endl;
        
    }

    