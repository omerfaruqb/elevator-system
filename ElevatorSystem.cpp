#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>
#include "Elevator.cpp"

class ElevatorSystem
{
private:
    std::vector<Elevator> elevators;
    int totalEnergyConsumed;
    int totalWaitingTime;
    int numVisitors;

public:
    ElevatorSystem(int numElevators, int startingFloor)
        : totalEnergyConsumed(0), totalWaitingTime(0), numVisitors(0)
    {
        for (int i = 0; i < numElevators; ++i)
        {
            elevators.emplace_back(startingFloor);
        }
    }

    void newCall(int from, int to)
    {
        Elevator *bestElevator = nullptr;
        int bestElevatorCost = std::numeric_limits<int>::max();

        for (Elevator &elevator : elevators)
        {
            int shouldAscend = from < to;
            bool onTheWay = (elevator.isAscending() == shouldAscend) &&
                            ((shouldAscend && elevator.currentFloor <= from) || (!shouldAscend && elevator.currentFloor >= from));
            
            if (elevator.isIdle() || onTheWay)
            {
                int waitingTime = elevator.distanceToFloor(from) + abs(to - from);
                int energyConsumed = elevator.isIdle() ? elevator.distanceToFloor(from) : 0;
                int score = waitingTime + energyConsumed;

                if (score < bestElevatorCost)
                {
                    bestElevator = &elevator;
                    bestElevatorCost = score;
                }
            }

            if (bestElevator != nullptr)
            {
                bestElevator->addPassenger(from, to);
                // numVisitors++;
            }
            else
            {
                for (Elevator &elevator : elevators)
                {
                    int waitingTime = elevator.distanceToLastStop() +
                                      abs(elevator.lastStop() - from) + abs(to - from);
                    int energyConsumed = 2 * abs(elevator.lastStop() - from);
                    int cost = waitingTime + energyConsumed;

                    if (cost < bestElevatorCost)
                    {
                        bestElevator = &elevator;
                        bestElevatorCost = cost;
                    }
                }
                bestElevator->addPassengerReverse(from, to);
            }
        }
    }

    void updateElevators()
    {
        for (auto &elevator : elevators)
        {   
            int previousPassengers = elevator.passengers;
            if(elevator.move()) {
                totalEnergyConsumed++;
                totalWaitingTime += previousPassengers;
            }
            // std::cout << "Previous passengers: " << previousPassengers << std::endl;
        }
    }

    void runSimulation(int numFloors, double visitorFrequency, int totalTime)
    {
        std::srand(std::time(0));
        double currentTime = 0;

        while (currentTime < totalTime)
        {
            if (std::rand() % 100 < (visitorFrequency * 100))
            {
                int from = std::rand() % numFloors;
                int to = std::rand() % numFloors;
                if (from != to)
                {
                    newCall(from, to);
                    numVisitors++;
                }
            }
            updateElevators();
            currentTime++;
        }
        printStatistics();
    }

    void printStatistics() const
    {
        std::cout << "\nSimulation Results:\n";
        std::cout << "Total Energy Consumed: " << totalEnergyConsumed << " units\n";
        std::cout << "Average Waiting Time: " << (numVisitors > 0 ? totalWaitingTime / numVisitors : 0) << " seconds\n";
    }
};