//
// Created by spl211 on 09/11/2021.
//
using namespace std;
#include<iostream>
#include<iterator> // for iterators
#include<vector> // for vectors
#include "../include/Trainer.h"

Trainer::Trainer(int t_capacity):capacity(t_capacity) {
}

int Trainer::getCapacity() const {
    return capacity;
}

void Trainer::addCustomer(Customer *customer) {
    customersList.push_back(customer);
}

Customer *Trainer::getCustomer(int id) {
    vector<Customer*>::iterator it;
    for (it = customersList.begin(); it != customersList.end(); it++) {
        if((*it)->getId() == id){
            return *it;
        }
    }
    std::cout << "no id found" << std::endl;
    return nullptr;//if id does not exist
}

void Trainer::removeCustomer(int id) { //do we need to delete the customer?!
    vector<Customer*>::iterator it;
    int i = 0;
    bool flag = false;
    for (it = customersList.begin(); it != customersList.end() && flag == false; it++) {
        if((*it)->getId() == id){
            flag = true;
            customersList.erase(it);
        }
    }
    if (!flag){
        std::cout << "no id found" << std::endl;
    }

}

std::vector<Customer*>& Trainer::getCustomers() { //check memory
    return customersList;
}

std::vector<OrderPair>& Trainer::getOrders() {//check  memory
    return orderList;
}

void Trainer::order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options) {
     for(int i =0; i < workout_ids.size(); i++){
         for(Workout w : workout_options){
             if(workout_ids.at(i) == w.getId()){
                 OrderPair p(w.getId(),w);
                 this->orderList.push_back(p);
                 std::cout <<getCustomer(customer_id)->getName() + " Is doing " + w.toString();
             }
         }
     }
}

void Trainer::openTrainer() {
    open = true;
}

void Trainer::closeTrainer() {
    open = false;
}

int Trainer::getSalary() {
    int sum;
    vector<OrderPair>::iterator it;
    for (it = orderList.begin(); it != orderList.end() ; it++) {
        sum = sum + ((it->second.getPrice()));
    }
    return sum;
}

bool Trainer::isOpen() {
    return open;
}

