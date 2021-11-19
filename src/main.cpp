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

    vector<Workout> w;

    for (int i = 0; i < 10; ++i) {
        string a("momi");
        a.append(to_string(i));
        Workout b(i, a, i * 5, static_cast<WorkoutType>(i % 3));
        w.push_back(b);
    }
    Customer* heavy = new HeavyMuscleCustomer("momi", 0);
    Customer* cheep = new CheapCustomer("tzipi", 1);
    Customer* full = new FullBodyCustomer("avi", 2);
    Customer* swa = new SweatyCustomer("meni",3);
    vector<Customer*> v = {heavy,cheep,full,swa};

    Customer* h1 = new HeavyMuscleCustomer("momi2", 4);
    Customer* c1 = new CheapCustomer("tzipi2", 5);
    Customer* f1 = new FullBodyCustomer("avi2", 6);
    Customer* s1 = new SweatyCustomer("meni2",7);
    vector<Customer*> v2 = {h1,c1,f1,s1};
    std::cout << "******************" << std::endl;
    std::cout <<"open trainer 0 " << std::endl;

    BaseAction* ot = new OpenTrainer(0,v);
    ot->act(studio);
    BaseAction* ord = new Order(0);
    ord->act(studio);
    std::cout << "******************" << std::endl;
    std::cout << "open trainer 1" << std::endl;

    BaseAction* ot2 = new OpenTrainer(1,v2);
    ot2->act(studio);
    BaseAction* ord2 = new Order(1);
    ord2->act(studio);
    std::cout << "******************" << std::endl;
    std::cout << "moce cus 2 from 0 to 1" << std::endl;

    BaseAction* move = new MoveCustomer(0,1,2);
    move->act(studio);
    ord2->act(studio);
    std::cout << "print 0 trainer" << std::endl;
    ord->act(studio);

    std::cout << "_________" << std::endl;
    BaseAction* close = new Close(0);
    close->act(studio);
    BaseAction* print = new PrintWorkoutOptions();
    print->act(studio);

    return 0;
}