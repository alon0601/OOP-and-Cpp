//
// Created by spl211 on 10/11/2021.
//
#include "algorithm"
#include "../include/Customer.h"
using namespace std;

Customer::Customer(std::string c_name, int c_id):id(c_id),name(c_name) {
}

std::string Customer::getName() const {
    return name;
}

int Customer::getId() const {
    return id;
}

SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id) {
}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> orders;
    int i = 0;
    for (Workout val: workout_options) {
        if (val.getType() == 2){
            orders.push_back(i);
        }
        i++;
    }
    return orders;
}

std::string SweatyCustomer::toString() const {
    return to_string(getId()) + " " + getName();
}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> orders;
    int min = workout_options.begin()->getPrice();
    int i = 0;
    for (Workout cheap: workout_options) {
        int price = cheap.getPrice();
        if (min > price){
            min = price;
            i = cheap.getId();
        }
    }
    orders.push_back(i);
    return orders;
}

std::string CheapCustomer::toString() const {
    return "";
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    vector<Workout> aner;
    vector<int> ans;
    for (Workout w: workout_options){
        if (w.getType() == 0){
            aner.push_back(w);
        }
    }
    int j;
    for (int i = 0; i < aner.size(); i++) {
        j = most(true,aner);
        ans.push_back(aner.at(j).getId());
        aner.erase(aner.begin()+j);
    }
    return ans;
}

std::string HeavyMuscleCustomer::toString() const {
    return "";
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    return std::vector<int>();
}

std::string FullBodyCustomer::toString() const {
    return std::__cxx11::string();
}

int Customer::most (bool high, vector<Workout> &workouts){
    int comp = workouts.begin()->getPrice();
    int ans = 0;
    int i = 0;
    for (Workout work:workouts) {
        if (high){
            if (comp < work.getPrice()){
                ans = i;
                comp = work.getPrice();
            }
        }
        else{
            if (comp > work.getPrice()) {
                ans = i;
                comp = work.getPrice();
            }
        }
        i++;
    }
    return ans;
}
