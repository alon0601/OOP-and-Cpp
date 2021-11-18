//
// Created by spl211 on 09/11/2021.
//

#include "../include/Studio.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
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
            SplitString(lin,words); //check!!
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
                Workout work(count - 3,words[0],stoi(words[2]),type);
                this->workout_options.push_back(work);
            }
            count++;
            words.clear();
        }
    }
    //test!
    cout << "num of trainers - " + to_string(this->trainers.size()) << endl;
    for (int i = 0; i < this->trainers.size(); ++i) {
        cout << "trainer num - " + to_string(i) + " capacity: " + to_string(this->trainers[i]->getCapacity()) << endl;
    }
    for (int i = 0; i < workout_options.size(); ++i) {
        cout << workout_options[i].toString() << endl;
        cout <<"****************"<< endl;
    }

}

int Studio::getNumOfTrainers() const {
    return 0;
}

void Studio::start() {
}

Trainer *Studio::getTrainer(int tid) {
    return nullptr;
}

const std::vector<BaseAction *> &Studio::getActionsLog() const {
    return this->actionsLog;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    return workout_options;
}

bool Studio::isTrainerExist(int id) {
    return false;
}

void Studio::SplitString(string s, vector<string> &v){

	string temp = "";
	for(int i=0;i<s.length();i++){
		if(s[i] == ','){
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
