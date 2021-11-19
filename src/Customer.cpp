//
// Created by spl211 on 10/11/2021.
//
#include <iostream>
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
    for (Workout cheap: workout_options) { //find the cheapes workout
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
    return to_string(getId()) + " " + getName();
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    vector<Workout*> aner;
    vector<int> ans;
    int max;
    for (int i = 0; i < workout_options.size(); i++){ //new vector of pointer of only  type 0
        if (workout_options[i].getType() == 0){
            Workout* pt = new Workout(workout_options.at(i));
            aner.push_back(pt);
        }
    }
    int id = (*aner.begin())->getId();
    while (aner.size() > 0){//sort int vector of orders
        int index = 0;
        max = (*(aner.begin()))->getPrice();
        for (int j = 0; j < aner.size(); ++j) {
            if ((*aner.at(j)).getPrice() >= max){
                index = j;
                max = (*aner.at(j)).getPrice();
                id = (*aner.at(j)).getId();
            }
        }
        ans.push_back(id);
        delete aner[index]; //check! - delete of the pointers
        aner.erase(aner.begin() + index);
    }
    return ans;
}

std::string HeavyMuscleCustomer::toString() const {
    return to_string(getId()) + " " + getName();
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {
}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    vector<int> ans;
    // cheapest cardio exercise:
    bool find = false;
    int min;
    int id;
    for (Workout w: workout_options) {
        if (w.getType() == ANAEROBIC) {
            if (!find) {
                min = w.getPrice();
                id = w.getId();
                find = true;
            } else {
                if (w.getPrice() < min) {
                    min = w.getPrice();
                    id = w.getId();
                }
            }
        }
    }
    if (find){
        ans.push_back(id);
    }
    //most expensive mix-type workout
    find = false;
    int max;
    for (Workout w: workout_options) {
        if (w.getType() == MIXED) {
            if (!find) {
                max = w.getPrice();
                id = w.getId();
                find = true;
            } else {
                if (w.getPrice() > max) {
                    max = w.getPrice();
                    id = w.getId();
                }
            }
        }
    }
    if (find){
        ans.push_back(id);
    }

    //cheapest anaerobic exercise
    find = false;
    for (Workout w: workout_options) {
        if (w.getType() == 0) {
            if (!find) {
                min = w.getPrice();
                id = w.getId();
                find = true;
            } else {
                if (w.getPrice() < min) {
                    min = w.getPrice();
                    id = w.getId();
                }
            }
        }
    }
    if (find){
        ans.push_back(id);
    }
    return ans;
}

std::string FullBodyCustomer::toString() const {
    return to_string(getId()) + " " + getName();
}
