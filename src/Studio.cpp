//
// Created by spl211 on 09/11/2021.
//

#include "../include/Studio.h"


Studio::Studio() {

}

Studio::Studio(const std::string &configFilePath) {
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
    std::vector<BaseAction*> b;
    return b;
}

std::vector<Workout> &Studio::getWorkoutOptions() {
    std::vector<Workout> b;
    return b;
}

bool Studio::isTrainerExist(int id) {
    return false;
}

