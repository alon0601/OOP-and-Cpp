#ifndef CUSTOMER_H_
#define CUSTOMER_H_

#include <vector>
#include <string>
#include "Workout.h"

class Customer{
public:
    Customer(std::string c_name, int c_id);
    virtual std::vector<int> order(const std::vector<Workout> &workout_options)=0;
    virtual ~Customer() = default;
    virtual std::string toString() const = 0;
    virtual Customer* copy() = 0;
    std::string getName() const;
    int getId() const;
private:
    const std::string name;
    const int id;
};


class SweatyCustomer : public Customer {
public:
    SweatyCustomer(std::string name, int id);
    ~SweatyCustomer();
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    Customer* copy();
private:
};


class CheapCustomer : public Customer {
public:
    CheapCustomer(std::string name, int id);
    ~CheapCustomer();
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    Customer* copy();
private:
};


class HeavyMuscleCustomer : public Customer {
public:
    HeavyMuscleCustomer(std::string name, int id);
    ~HeavyMuscleCustomer();
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    Customer* copy();
private:
};


class FullBodyCustomer : public Customer {
public:
    FullBodyCustomer(std::string name, int id);
    ~FullBodyCustomer();
    std::vector<int> order(const std::vector<Workout> &workout_options);
    std::string toString() const;
    Customer* copy();
private:
};


#endif