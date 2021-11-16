#include "../include/Studio.h"
#include "../include/Trainer.h"
#include "../include/Workout.h"
#include <iostream>

using namespace std;

Studio* backup = nullptr;

int main(int argc, char** argv){
    if(argc!=2){
        std::cout << "usage config <path>" << std::endl;
        return 0;
    }
    string configurationFile = argv[1];
//    Studio studio(configurationFile);
//    studio.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }


    //testing
    vector<Workout> w;
    for (int i = 0; i < 10; ++i) {
        string a("momi");
        a.append(to_string(i));
        Workout b(i, a ,i*5, static_cast<WorkoutType>(i%3));
        w.push_back(b);
    }
    FullBodyCustomer c("menahem",3);
    vector<int> d = c.order(w);
    for (Workout w1 : w) {
        w1.toString();
    }
    std::cout << "************************" << std::endl;
    for (int i; i < d.size(); ++i) {
        std::cout << d[i] << std::endl;
    }

    return 0;
}