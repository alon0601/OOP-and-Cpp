//
// Created by spl211 on 09/11/2021.
//

#include "../include/Workout.h"
#include <iostream>

Workout::Workout(int w_id, std::string w_name, int w_price, WorkoutType w_type):id(w_id),name(w_name),price(w_price),type(w_type) {
}

int Workout::getId() const {
    return id;
}

std::string Workout::getName() const {
    return name;
}

int Workout::getPrice() const {
    return price;
}

WorkoutType Workout::getType() const {
    return type;
}

std::string Workout::toString() const {
    std::cout << "id " << getId() << std::endl;
    std::cout << "name " << getName() << std::endl;
    std::cout << "type " << getType() << std::endl;
    std::cout << "price" << getPrice() << std::endl;
    std::cout << "-----------------------------------" << std::endl;
}







