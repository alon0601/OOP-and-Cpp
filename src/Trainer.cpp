//
// Created by spl211 on 09/11/2021.
//
using namespace std;
#include<iostream>
#include <iterator> // for iterators
#include <vector> // for vectors
#include "../include/Trainer.h"

Trainer::Trainer(int t_capacity):capacity(t_capacity){
    open = false;
    salary = 0;
}
Trainer::Trainer(const Trainer& other):open(other.open),salary(other.salary),capacity(other.capacity) { //copy constructor
    for(Customer* c:other.customersList)
        this->customersList.push_back(c->copy());
    for (OrderPair p:other.orderList){
        this->orderList.push_back(p);
    }
}
int Trainer::getCapacity() const {
    return capacity;
}

void Trainer::addCustomer(Customer *customer) {
    if(capacity > this->customersList.size()){
        customersList.push_back(customer);
    }
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
            removePair(id);

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
    bool orderd = false;
    for(OrderPair ord : orderList){
        if(ord.first == customer_id)
            orderd = true;
    }
    if(!orderd) {
        for (int i = 0; i < workout_ids.size(); i++) {
            for (Workout w: workout_options) {//fot each workout add it if he is in the costumer's workout ids list
                if (workout_ids.at(i) == w.getId()) {
                    OrderPair p(customer_id, w);
                    this->orderList.push_back(p);
                }
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
    int sum = 0;
    vector<OrderPair>::iterator it;
    for (it = orderList.begin(); it != orderList.end() ; it++) {
        sum = sum + ((it->second.getPrice()));
    }
    return sum;
}

bool Trainer::isOpen() {
    return open;
}

void Trainer::removePair(int id) {  //remove from orderList all the orders by 'id' customer
    vector<OrderPair> order;
    for (OrderPair p:this->orderList) {
        if (p.first != id){
            order.push_back(p);
        }
    }
    this->orderList.clear();
    for (OrderPair p:order) {
        this->orderList.push_back(p);
    }
}

void Trainer::print() {
    for (OrderPair o:orderList) {
        string s = getCustomer(o.first)->getName();
        s.append(" is doing ");
        s.append(o.second.toString());
        std::cout << s << endl;
    }
}

string Trainer::printOrderList() {
    string s;
    for (OrderPair p: this->orderList){
        s.append(p.second.getName() + " " + to_string(p.second.getPrice()) + "NIS " + to_string(p.first) + "\n");
    }
    return s;
}

void Trainer::updateSalary() {
    this->salary = this->salary + getSalary();
}

int Trainer::getTotalSalary() {
    return this->salary;
}

void Trainer::removeAllCustomer() {
    for(Customer* c: this->customersList) {
        if (c){
            delete c;
            c = nullptr;
        }
    }
    this->customersList.clear();
    this->orderList.clear();
}

Trainer::~Trainer() { //destructor
    removeAllCustomer();
}

Trainer &Trainer::operator=(const Trainer &other) {
    if (this == &other){
        return *this;
    }
    else{
        this->orderList.clear();
        for (Customer* cus:this->customersList){
            delete cus;
        }
        this->customersList.clear();
        for (Customer* cus:other.customersList){
            this->customersList.push_back(cus);
        }
        for (OrderPair p:other.orderList){
            this->orderList.push_back(p);
        }
        this->open = other.open;
        this->salary = other.salary;
        this->capacity = other.capacity;
    }
}

Trainer::Trainer(Trainer &&other) :open(other.open),salary(other.salary),capacity(other.capacity),orderList(move(other.orderList)),customersList(move(other.customersList)){
}

Trainer &Trainer::operator=(Trainer &&t){
    this->customersList = move(t.customersList);
    this->orderList = move(t.orderList);
    this->salary= t.salary;
    this->open = t.open;
}





