//
// Created by spl211 on 16/11/2021.
//
#include "../include/Studio.h"
#include "../include/Trainer.h"
#include "../include/Workout.h"
#include <iostream>
#include "../include/testing.h"
using namespace std;

int testing(int argc, char** argv) {
    vector<Workout> w;

    for (int i = 0; i < 10; ++i) {
        string a("momi");
        a.append(to_string(i));
        Workout b(i, a, i * 5, static_cast<WorkoutType>(i % 3));
        w.push_back(b);
    }
    HeavyMuscleCustomer c("menahem", 3);
    vector<int> d = c.order(w);
    for (Workout w1: w) {
        w1.toString();
    }
    std::cout << "************************" << std::endl;
    for (int i; i < d.size(); ++i) {
        std::cout << d[i] << std::endl;
    }
    return 0;
}