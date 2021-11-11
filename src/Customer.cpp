//
// Created by spl211 on 10/11/2021.
//

#include "../include/Customer.h"

Customer::Customer(std::string c_name, int c_id):id(c_id),name(c_name) {

}

std::string Customer::getName() const {
    return std::__cxx11::string();
}

int Customer::getId() const {
    return 0;
}

SweatyCustomer::SweatyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> SweatyCustomer::order(const std::vector<Workout> &workout_options) {
    return std::vector<int>();
}

std::string SweatyCustomer::toString() const {
    return std::__cxx11::string();
}

CheapCustomer::CheapCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> CheapCustomer::order(const std::vector<Workout> &workout_options) {
    return std::vector<int>();
}

std::string CheapCustomer::toString() const {
    return std::__cxx11::string();
}

HeavyMuscleCustomer::HeavyMuscleCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> HeavyMuscleCustomer::order(const std::vector<Workout> &workout_options) {
    return std::vector<int>();
}

std::string HeavyMuscleCustomer::toString() const {
    return std::__cxx11::string();
}

FullBodyCustomer::FullBodyCustomer(std::string name, int id) : Customer(name, id) {

}

std::vector<int> FullBodyCustomer::order(const std::vector<Workout> &workout_options) {
    return std::vector<int>();
}

std::string FullBodyCustomer::toString() const {
    return std::__cxx11::string();
}
