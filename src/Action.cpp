//
// Created by spl211 on 16/11/2021.
//
#include "../include/Action.h"
#include "../include/Studio.h"
using namespace std;

BaseAction::BaseAction() {

}

ActionStatus BaseAction::getStatus() const {
    return status;
}

void BaseAction::complete() {
    this->status = COMPLETED;
}

void BaseAction::error(std::string errorMsg) {
    this->status = ERROR;
    this->errorMsg = "error: <" + errorMsg + ">";
}

std::string BaseAction::getErrorMsg() const {
    return this->errorMsg;
}

OpenTrainer::OpenTrainer(int id, vector<Customer *> &customersList): trainerId(id), customers(customersList) {

}

void OpenTrainer::act(Studio &studio) {
    Trainer* t = studio.getTrainer(this->trainerId);
        if (!studio.isTrainerExist(trainerId)) {
            error("this trainer isn't exist");
        }
        else{
            if(!t->isOpen()){
                error("this trainer has an open session");
            }
            if(t->getCapacity() < this->customers.size())
                error("this trainer can't have more then " + t->getCapacity());
            else {
                t->closeTrainer();
                for(Customer* c : this->customers)
                {
                    t->addCustomer(c);
                }
            }
        }
}

std::string OpenTrainer::toString() const {
    return "a";
}

Order::Order(int id) : trainerId(id) {

}

void Order::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    if (!studio.isTrainerExist(trainerId)) {
        error("this trainer isn't exist");
    }
    else{
        for(Customer* c : t->getCustomers()){
            t->order(c->getId(),c->order(studio.getWorkoutOptions()),studio.getWorkoutOptions());
        }
    }

}

std::string Order::toString() const {
    return "23";
}

//MoveCustomer::MoveCustomer(int src, int dst, int customerId) {
//
//}
//
//void MoveCustomer::act(Studio &studio) {
//
//}
//
//std::string MoveCustomer::toString() const {
//    return std::__cxx11::string();
//}
//
//Close::Close(int id) {
//
//}
//
//void Close::act(Studio &studio) {
//
//}
//
//std::string Close::toString() const {
//    return std::__cxx11::string();
//}
//
//CloseAll::CloseAll() {
//
//}
//
//void CloseAll::act(Studio &studio) {
//
//}
//
//std::string CloseAll::toString() const {
//    return std::__cxx11::string();
//}
//
//PrintWorkoutOptions::PrintWorkoutOptions() {
//
//}
//
//void PrintWorkoutOptions::act(Studio &studio) {
//
//}
//
//std::string PrintWorkoutOptions::toString() const {
//    return std::__cxx11::string();
//}
//
//PrintTrainerStatus::PrintTrainerStatus(int id) {
//
//}
//
//void PrintTrainerStatus::act(Studio &studio) {
//
//}
//
//std::string PrintTrainerStatus::toString() const {
//    return std::__cxx11::string();
//}
//
//PrintActionsLog::PrintActionsLog() {
//
//}
//
//void PrintActionsLog::act(Studio &studio) {
//
//}
//
//std::string PrintActionsLog::toString() const {
//    return std::__cxx11::string();
//}
//
//BackupStudio::BackupStudio() {
//
//}
//
//void BackupStudio::act(Studio &studio) {
//
//}
//
//std::string BackupStudio::toString() const {
//    return std::__cxx11::string();
//}
//
//RestoreStudio::RestoreStudio() {
//
//}
//
//void RestoreStudio::act(Studio &studio) {
//
//}
//
//std::string RestoreStudio::toString() const {
//    return std::__cxx11::string();
//}
