#ifndef TRAINER_H_
#define TRAINER_H_

#include <vector>
#include "Customer.h"
#include "Workout.h"

typedef std::pair<int, Workout> OrderPair;

class Trainer{
public:
    Trainer(int t_capacity);
    Trainer(const Trainer& trainer);
    Trainer (Trainer &&t);
    Trainer& operator=(Trainer &&t);
    int getCapacity() const;
    void addCustomer(Customer* customer);
    void removeCustomer(int id);
    void removeAllCustomer();
    Customer* getCustomer(int id);
    std::vector<Customer*>& getCustomers();
    std::vector<OrderPair>& getOrders();
    void order(const int customer_id, const std::vector<int> workout_ids, const std::vector<Workout>& workout_options);
    void openTrainer();
    void closeTrainer();
    int getSalary(); //salary for a session
    bool isOpen();
    void print(); //print for order
    std::string printOrderList(); //string of the order
    void updateSalary(); //update the salary for the day
    int getTotalSalary(); //salary for all day
    Trainer& operator=(const Trainer& other);

    ~Trainer();

private:
    void removePair(int id); //gets the id of the customer you want to remove
    int capacity;
    bool open;
    int salary;
    std::vector<Customer*> customersList;
    std::vector<OrderPair> orderList; //A list of pairs for each order for the trainer - (customer_id, Workout)
};


#endif