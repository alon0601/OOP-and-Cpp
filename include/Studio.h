#ifndef STUDIO_H_
#define STUDIO_H_

#include <vector>
#include <string>
#include "Workout.h"
#include "Trainer.h"
#include "Action.h"


class Studio{		
public:
	Studio();
    Studio(const Studio& other);
    Studio(const std::string &configFilePath);
    Studio& operator=(const Studio& other);
    ~Studio();
    void start();
    int getNumOfTrainers() const;
    Trainer* getTrainer(int tid);
    bool isTrainerExist(int id);
	const std::vector<BaseAction*>& getActionsLog() const; // Return a reference to the history of actions
    std::vector<Workout>& getWorkoutOptions();

private:
    void SplitString(std::string s, std::vector<std::string> &v,char c);
    bool open;
    std::vector<Trainer*> trainers;
    std::vector<Workout> workout_options;
    std::vector<BaseAction*> actionsLog;
};



#endif