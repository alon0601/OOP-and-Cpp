//
// Created by spl211 on 16/11/2021.
//
#include "../include/Action.h"
#include "../include/Studio.h"
extern Studio* backup;
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
        cout << "Error : trainer doesnt exist" << endl;
    }
    else{
        if(t->isOpen()){
            error("this trainer has an open session");
            cout << "Error : trainer has an open session" << endl;
        }
        else {
            t->openTrainer();//open new session
            if (t->getCapacity() < this->customers.size()){//if we have more costumers then the capacity
                for(int i = 0; i < t->getCapacity();i++){
                    t->addCustomer(this->customers[i]->copy());
                }
                for (int i = t->getCapacity()-1; i < this->customers.size(); ++i) {

                }
            }
            else {
                for(Customer* c : this->customers){
                    t->addCustomer(c->copy());
                }//adding the costumers to the trainer's list
            }
            complete();
        }
    }
}

std::string OpenTrainer::toString() const {
    string s;
    for (Customer* c:this->customers){
        s.append(c->toString());
        s.append(" ");
    }
    return "Open trainer " +to_string(this->trainerId) + " " + s + this->getStringStatus() + getErrorMsg();
}

BaseAction *OpenTrainer::copy() {
    vector<Customer*> newCus;
    for (Customer* c:this->customers) {
        newCus.push_back(c->copy());
    }
    return new OpenTrainer(this->trainerId,newCus);
}

OpenTrainer::~OpenTrainer() {
    for (Customer* c:customers) {
        if(c != nullptr){
           delete c;
           c = nullptr;
        }
    }
    this->customers.clear();
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
            vector<int> orderId(c->order(w));
            t->order(c->getId(),orderId,w);//ordering workout for the trainer's costumer
        }
        t->print();
        complete();
    }


}

std::string Order::toString() const {
    return "order " +  this->getStringStatus() + " " + this->getErrorMsg();
}

BaseAction *Order::copy() {
    return new Order(this->trainerId);
}

Order::~Order() = default;


MoveCustomer::MoveCustomer(int src, int dst, int customerId): srcTrainer(src) , dstTrainer(dst) , id(customerId) {

}

void MoveCustomer::act(Studio &studio) {
    Trainer* tSrc = studio.getTrainer(srcTrainer);
    Trainer* tDst = studio.getTrainer(dstTrainer);
    if(tDst->getCapacity() > tDst->getCustomers().size() + 1) {
        Customer* move = tSrc->getCustomer(id);
        if (move != nullptr) {
            tDst->addCustomer(move);
            tSrc->removeCustomer(id);
            //should add all the cus order
            tDst->order(id, move->order(studio.getWorkoutOptions()),
                        studio.getWorkoutOptions()); //add the orders for the customer
            complete();
        }
        else{
            error("customer not found" );
        }
    }
    else{
        error("this trainer can't have more costumers");
        cout << getErrorMsg() << endl;
    }
    if(tSrc->getCustomers().size() == 0){
        tSrc->closeTrainer();
    }
}

std::string MoveCustomer::toString() const {
    return "Move customer" + to_string(srcTrainer) + to_string(dstTrainer) +  this->getStringStatus() + " " + this->getErrorMsg();
}

BaseAction *MoveCustomer::copy() {
    return new MoveCustomer(this->srcTrainer,this->dstTrainer,this->id);
}

MoveCustomer::~MoveCustomer() = default;

Close::Close(int id):trainerId(id) {
}

void Close::act(Studio &studio) {
    Trainer *t = studio.getTrainer(trainerId);
    if (!t->isOpen() || !studio.isTrainerExist(trainerId)){
        error("trainer doesnt open or exist");
        cout << this->getErrorMsg()<< endl;

    }
    else {
        t->updateSalary();
        t->removeAllCustomer();
        t->closeTrainer();
        string s = "Trainer ";
        s.append(to_string(trainerId));
        s.append(" closed. Salary ");
        s.append(to_string(t->getTotalSalary()));
        s.append("NIS");
        cout << s << endl;
        complete();
    }
}

std::string Close::toString() const {
    return "Close" + this->getStringStatus() + " " + this->getErrorMsg();
}

BaseAction *Close::copy() {
    return new Close(this->trainerId);
}

Close::~Close() = default;

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
    complete();
}

std::string CloseAll::toString() const {
    return "close all" + this->getStringStatus() + " " + this->getErrorMsg();
}

BaseAction *CloseAll::copy() {
    return new CloseAll();
}

CloseAll::~CloseAll() = default;

PrintWorkoutOptions::PrintWorkoutOptions() {

}

void PrintWorkoutOptions::act(Studio &studio) {
    for(Workout w : studio.getWorkoutOptions())
        cout << w.toString() + ", " + w.printType() + ", " + to_string(w.getPrice()) << endl;
    complete();
}

std::string PrintWorkoutOptions::toString() const {
    return "Print Workout Options " + this->getStringStatus() + " " + this->getErrorMsg();
}

BaseAction *PrintWorkoutOptions::copy() {
    return new PrintWorkoutOptions();
}

PrintWorkoutOptions::~PrintWorkoutOptions() = default;


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
            s.append(to_string(c->getId()) + " " + c->getName()+ "\n");
        }
        s.append("orders: \n");
        s.append(t->printOrderList());
        s.append("current trainer's salary: " + to_string(t->getSalary()) + "NIS");
    }
    else
        s.append(" status : close");
    cout << s << endl;
    complete();
}

std::string PrintTrainerStatus::toString() const {
    return "print Trainer status " + this->getStringStatus();
}

BaseAction *PrintTrainerStatus::copy() {
    return new PrintTrainerStatus(this->trainerId);
}

PrintTrainerStatus::~PrintTrainerStatus() = default;


PrintActionsLog::PrintActionsLog() {

}

void PrintActionsLog::act(Studio &studio) {
    for(BaseAction* baseAction : studio.getActionsLog()){
        cout << baseAction->toString() << endl;
    }
    complete();
}

std::string PrintActionsLog::toString() const {
    return "print actions log";
}

BaseAction *PrintActionsLog::copy() {
    return new PrintActionsLog();
}

PrintActionsLog::~PrintActionsLog() = default;



BackupStudio::BackupStudio() {

}

void BackupStudio::act(Studio &studio) {
    if (backup != nullptr){
        delete backup;
        backup = nullptr;
    }
    backup = new Studio(studio);
    complete();
}

std::string BackupStudio::toString() const {
    return "Backup Studio" + this->getStringStatus();
}

BaseAction *BackupStudio::copy() {
    return new BackupStudio();
}

BackupStudio::~BackupStudio() = default;


RestoreStudio::RestoreStudio() {

}

BaseAction *RestoreStudio::copy() {
    return new RestoreStudio();
}

void RestoreStudio::act(Studio &studio) {
    if (backup == nullptr){
        cout << "no backup available"<< endl;
        this->error("no backup available");
    }
    else{
        studio = *backup;
        complete();
    }
}

std::string RestoreStudio::toString() const {
    return "Restore Studio " + this->getStringStatus();
}

RestoreStudio::~RestoreStudio() = default;

std::string BaseAction::getStringStatus() const {
    if(to_string(this->getStatus()) == "1")
        return "ERROR";
    return "COMPLETED";
}

