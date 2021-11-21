//
// Created by spl211 on 09/11/2021.
//

#include "../include/Studio.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <error.h>
#include "boost/algorithm/string.hpp"

using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::ostringstream;

using namespace std;

Studio::Studio() {

}

Studio::Studio(const std::string &configFilePath) {
    int numOfTrainers;
    ifstream input_file(configFilePath);
    if (!input_file.is_open()) {
        cerr << "Could not open the file - '"
             << configFilePath << "'" << endl;
        exit(EXIT_FAILURE);
    }
    string input((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
    std::vector<std::string> lines;
    std::stringstream stream(input);
    std::string line;
    int count = 1;
    while (std::getline(stream, line)) {
        lines.push_back(line);
    }
    for (string lin:lines){
        vector<string> words;
        if (lin.size() != 0 && lin[0] != '#'){
            SplitString(lin,words,','); //check!!
            if (count == 1){
                numOfTrainers = (stoi(words[0]));
            }
            if (count == 2){
                for (string word:words) {
                    Trainer* pt = new Trainer(stoi(word));
                    this->trainers.push_back(pt);
                }
            }
            if (count >= 3){
                WorkoutType type;
                boost::to_upper(words[1]);
                if (words[1] == "ANAEROBIC"){
                    type = ANAEROBIC;
                }
                else if(words[1] == "MIXED"){
                    type = MIXED;
                }
                else type = CARDIO;
                string name;
                name.push_back((words[0][0]));
                for (int i = 1; i < words[0].size() ; ++i) {
                    if (isupper(words[0][i])){
                        name.push_back(' ');
                    }
                    name.push_back(words[0][i]);
                }
                Workout work(count - 3,name,stoi(words[2]),type);
                this->workout_options.push_back(work);
            }
            count++;
            words.clear();
        }
    }

}

int Studio::getNumOfTrainers() const {
    return this->trainers.size();
}

void Studio::start() {
    cout << "Studio is now open!" << endl;
    string input;
    BaseAction *action;
    int ids = 0;
    while(input != "CloseAll") {
        cout << "please enter an action" << endl;
        vector<string> words;
        getline(cin, input);
        SplitString(input, words, ' ');
        if (words[0] == "open"){
            vector<Customer*> customer;
            vector<string> cus;
            for (int i = 2; i < words.size(); i++){
                SplitString(words[i],cus,',');
                if (cus[1] == "swt"){
                    customer.push_back(new SweatyCustomer(cus[0],ids));
                    ids++;
                }
                if (cus[1] == "chp"){
                    customer.push_back(new CheapCustomer(cus[0],ids));
                    ids++;
                }
                if (cus[1] == "mcl"){
                    customer.push_back(new HeavyMuscleCustomer(cus[0],ids));
                    ids++;
                }
                if (cus[1] == "fbd"){
                    customer.push_back(new FullBodyCustomer(cus[0],ids));
                    ids++;
                }
                cus.clear();
            }
            action = new OpenTrainer(stoi(words[1]),customer);
        }
        if(words[0] == "order"){
            action = new Order(stoi(words[1]));
        }
        if (words[0] == "move") {
            action = new MoveCustomer(stoi(words[1]), stoi(words[2]), stoi(words[3]));
        }
        if (words[0] == "close") {
            action = new Close(stoi(words[1]));
        }
        if(words[0] == "workout_options"){
            action = new PrintWorkoutOptions();
        }
        if(words[0] == "status"){
            action = new PrintTrainerStatus(stoi(words[1]));
        }
        if(words[0] == "log"){
            action = new PrintActionsLog();
        }
        if(words[0] == "backup"){
            action = new BackupStudio();
        }
        action->act(*this);
        this->actionsLog.push_back(action);
    }
    action = new CloseAll();
    action->act(*this);
}

Trainer *Studio::getTrainer(int tid) {
    if (tid >= this->trainers.size()){
        return nullptr;
    }
    return this->trainers.at(tid);
}

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return this->actionsLog;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;
}

bool Studio::isTrainerExist(int id) {
    if(getTrainer(id) == nullptr)
        return false;
    return true;
}

void Studio::SplitString(string s, vector<string> &v,char check){

	string temp = "";
	for(int i=0;i<s.length();i++){
        if(s[i] == check){
            if (temp != "") {
                v.push_back(temp);
                temp = "";
            }
		}
		else if (s[i] != ' '){
			temp.push_back(s[i]);
		}
	}
	v.push_back(temp);

}

Studio::Studio(const Studio& other):open(other.open) {
    for(Workout w: this->workout_options)
        this->workout_options.push_back(w);
    for(Trainer* t: this->trainers){
        this->trainers.push_back(new Trainer(*t));
    }
    for(BaseAction* action: this->actionsLog){
        this->actionsLog.push_back(action);
    }

}
