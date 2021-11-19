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
    Studio studio(configurationFile);
    studio.start();
    if(backup!=nullptr){
    	delete backup;
    	backup = nullptr;
    }
    HeavyMuscleCustomer* c = new HeavyMuscleCustomer("ss" , 0);
    CheapCustomer* c1 = new CheapCustomer("aa",1);
    CheapCustomer* c2 = new CheapCustomer("bb",0);
    vector<Customer*> cu;
    vector<Customer*> cu1;
    cu.push_back(c);
    cu.push_back(c1);
    cu1.push_back(c2);
    OpenTrainer p(0,cu);
    OpenTrainer l(1,cu1);
    Order o(0);
    p.act(studio);
    o.act(studio);
    MoveCustomer m(1,0,0);
    m.act(studio);
    CloseAll* cA = new CloseAll();
    cA->act(studio);
    return 0;
}