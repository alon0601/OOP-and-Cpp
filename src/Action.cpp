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
    this->errorMsg = errorMsg;
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
        if(t->isOpen()){
            error("this trainer has an open session");
        } else {
            t->openTrainer();//open new session
            if (t->getCapacity() < this->customers.size()){//if we have more costumers then the capacity
                for(int i = 0; i < t->getCapacity();i++){
                    t->addCustomer(this->customers[i]);
                }
            }
            else {
                for(Customer* c : this->customers){
                    t->addCustomer(c);
                }//adding the costumers to the trainer's list
            }
        }
    }
}

std::string OpenTrainer::toString() const {
    return "Open trainer " + to_string(trainerId) + to_string(this->getStatus()) + " " + this->getErrorMsg();
}

Order::Order(int id) : trainerId(id) {

}

void Order::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    if (!studio.isTrainerExist(trainerId)) {
        error("this trainer isn't exist");
    }
    else{
        vector<Workout> w(studio.getWorkoutOptions());
        for(Customer* c : t->getCustomers()){
            vector<int>* orderId = new vector<int>(c->order(w));
            t->order(c->getId(),*orderId,w);//ordering workout for the trainer's costumer
        }
    }
    t->print();

}

std::string Order::toString() const {
    return "order" + to_string(this->getStatus()) + " " + this->getErrorMsg();
}

MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTrainer(src) , dstTrainer(dst) , id(customerId) {

}

void MoveCustomer::act(Studio &studio) {
    Trainer* tSrc = studio.getTrainer(srcTrainer);
    Trainer* tDst = studio.getTrainer(dstTrainer);
    if(tDst->getCapacity() > tDst->getCustomers().size() + 1) {
        Customer* move = tSrc->getCustomer(id);
        tDst->addCustomer(move);
        tSrc->removeCustomer(id);
        //should add all the cus order
        tDst->order(id,move->order(studio.getWorkoutOptions()),studio.getWorkoutOptions()); //add the orders for the customer
    }
    else{
        error("this trainer can't have more costumers");
    }
    if(tSrc->getCustomers().size() == 0){
        tSrc->closeTrainer();
    }
}

std::string MoveCustomer::toString() const {
    return "Move customer" + to_string(srcTrainer) + to_string(dstTrainer) +  to_string(this->getStatus()) + " " + this->getErrorMsg();
}

Close::Close(int id):trainerId(id) {
}

void Close::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    if (!t->isOpen() || !studio.isTrainerExist(trainerId))
        error("trainer doesnt open or exist");
    else {
        t->updateSalary();
        t->getCustomers().clear();
        t->getOrders().clear();
        t->closeTrainer();
        string s = "Trainer ";
        s.append(to_string(trainerId));
        s.append(" closed. Salary ");
        s.append(to_string(t->getTotalSalary()));
        s.append("NIS");
        cout << s << endl;
    }
}

std::string Close::toString() const {
    return "Close" + to_string(this->getStatus()) + " " + this->getErrorMsg();
}

CloseAll::CloseAll() {

}

void CloseAll::act(Studio &studio) {
    for (int i = 0; i < studio.getNumOfTrainers() ; i++){
        Trainer* t = studio.getTrainer(i);
        if (t->isOpen()){
            Close clos(i);
            clos.act(studio);
        }
    }
}

std::string CloseAll::toString() const {
    return "close all" + to_string(this->getStatus()) + " " + this->getErrorMsg();
}

PrintWorkoutOptions::PrintWorkoutOptions() {

}

void PrintWorkoutOptions::act(Studio &studio) {
    for(Workout w : studio.getWorkoutOptions())
        cout << w.toString() + ", " + to_string(w.getType()) + ", " + to_string(w.getPrice()) << endl;
}

std::string PrintWorkoutOptions::toString() const {
    return "Print Workout Options " + to_string(this->getStatus()) + " " + this->getErrorMsg();
}

PrintTrainerStatus::PrintTrainerStatus(int id) : trainerId(id) {

}

void PrintTrainerStatus::act(Studio &studio) {
    Trainer* t = studio.getTrainer(trainerId);
    string s = "Trainer ";
    s.append(to_string(trainerId));
    if(t->isOpen()) {
        s.append(" status : open \n");
        s.append("costumers:\n");
        bool afterCostumers = true;
        for (Customer *c: studio.getTrainer(trainerId)->getCustomers()) {
            s.append(c->toString() + "\n");
        }
        s.append("orders: \n");
//        for (Customer *c: studio.getTrainer(trainerId)->getCustomers()) {
//            for (OrderPair pair: studio.getTrainer(trainerId)->getOrders())
//                s.append(pair.second.getName() + " " + to_string(pair.second.getPrice()) + "NIS " + to_string(pair.first) +
//                         "\n");
//        }
        s.append(t->printOrderList());
        s.append("current trainer's salary: " + to_string(t->getSalary()) + "NIS");
    }
    else
        s.append(" status : close");
    cout << s << endl;
}

std::string PrintTrainerStatus::toString() const {
    return "print Trainer status " + this->getStatus();
}

PrintActionsLog::PrintActionsLog() {

}

void PrintActionsLog::act(Studio &studio) {
    for(BaseAction* baseAction : studio.getActionsLog()){
        baseAction->toString();
    }
}

std::string PrintActionsLog::toString() const {
    return "print actions log";
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
