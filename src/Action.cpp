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
            } else{
            if(t->getCapacity() < this->customers.size())//if we have more costumers then the capacity
                error("this trainer can't have more costumers");
            else {
                t->openTrainer();//open new session
                for(Customer* c : this->customers)//adding the costumers to the trainer's list
                        t->addCustomer(c);
                }
            }
        }
}

std::string OpenTrainer::toString() const {
    return "Open trainer";
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
            t->order(c->getId(),c->order(studio.getWorkoutOptions()),studio.getWorkoutOptions());//ordering workout for the trainer's costumer
        }
    }

}

std::string Order::toString() const {
    return "order";
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTrainer(src) , dstTrainer(dst) , id(customerId) {

}

void MoveCustomer::act(Studio &studio) {
    Trainer* tSrc = studio.getTrainer(srcTrainer);
    Trainer* tDst = studio.getTrainer(dstTrainer);
    if(tSrc->getCapacity() > tSrc->getCustomers().size() + 1) {
        tDst->addCustomer(tSrc->getCustomer(id));
        tSrc->removeCustomer(id);
    }
    else{
        error("this trainer can't have more costumers");
    }
    if(tSrc->getCustomers().size() == 0){
        delete tSrc;
    }
}

std::string MoveCustomer::toString() const {
    return "Move customer";
}

Close::Close(int id):trainerId(id) {
}

void Close::act(Studio &studio) {
    Trainer* t = studio.getTrainer(trainerId);
    if(t->isOpen() || studio.isTrainerExist(trainerId))
        error("trainer doesnt open or exist");
    else {
        int salary = t->getSalary();
        t->getCustomers().clear();
        t->closeTrainer();
        error( "Trainer " + to_string(trainerId) + " closed. salary " + to_string(salary));
    }
}

std::string Close::toString() const {
    return "Close";
}

CloseAll::CloseAll() {

}

void CloseAll::act(Studio &studio) {
    for(int i = 0;i<studio.getNumOfTrainers();i++){
        Close* c = new Close(i);
        c->act(studio);
    }
}

std::string CloseAll::toString() const {
    return "close all";
}

PrintWorkoutOptions::PrintWorkoutOptions() {

}

void PrintWorkoutOptions::act(Studio &studio) {
    for(Workout w : studio.getWorkoutOptions())
        cout << w.toString() << endl;
}

std::string PrintWorkoutOptions::toString() const {
    return "Print Workout Options";
}

PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id) {

}

void PrintTrainerStatus::act(Studio &studio) {
    Trainer* t = studio.getTrainer(trainerId);
    string s = "Trainer ";
    s.append(to_string(trainerId));
    if(t->isOpen()) {
        s.append(" status : open/n");
        s.append("costumers/n");
        bool afterCostumers = true;
        for (Customer *c: studio.getTrainer(trainerId)->getCustomers()) {
            s.append(c->toString() + "/n");
        }
        for (Customer *c: studio.getTrainer(trainerId)->getCustomers()) {
            for (OrderPair pair: studio.getTrainer(trainerId)->getOrders())
                s.append(pair.second.getName() + " " + to_string(pair.second.getPrice()) + " " + to_string(pair.first) +
                         "/n");
        }
        s.append("current trainer's salary :" + to_string(t->getSalary()));
    }
    else
        s.append(" status : close");
}

std::string PrintTrainerStatus::toString() const {
    return "print Trainer status";
}

PrintActionsLog::PrintActionsLog() {

}

void PrintActionsLog::act(Studio &studio) {
    for(BaseAction* baseAction : studio.getActionsLog()){

    }
}

std::string PrintActionsLog::toString() const {
    return std::__cxx11::string();
}

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
