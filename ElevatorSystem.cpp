#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <limits>
#include "Elevator.cpp"

#define DEBUG 1

#if DEBUG
#define debug(x) std::cerr << x << std::endl
#else
#define debug(x)
#endif

class ElevatorSystem
{
private:
    std::vector<Elevator> elevators;
    int totalEnergyConsumed;
    int totalWaitingTime;
    int numVisitors;

public:
    ElevatorSystem(int numElevators, int startingFloor, int maxCapacity)
        : totalEnergyConsumed(0), totalWaitingTime(0), numVisitors(0)
    {
        for (int i = 0; i < numElevators; ++i)
        {
            elevators.emplace_back(startingFloor, maxCapacity);
        }
    }

    // A basic algorithm to assign a new call to an elevator
    void newCall(int from, int to)
    {
        debug("[SYSTEM] New call: " << from << " -> " << to);
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
                debug("[SYSTEM] Elevator " << bestElevator->id << " is selected!");
                return;
            }
        }

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

    void updateElevators()
    {
        for (auto &elevator : elevators)
        {
            int numTotalPassengers = elevator.numPassengersPickedUp + elevator.numPassengersWaiting;
            if (elevator.move())
            {
                totalEnergyConsumed++;
                totalWaitingTime += numTotalPassengers;
            }
        }
    }

    void runSimulation(int numFloors, double visitorFrequency, int totalTime)
    {
        std::srand(std::time(0));
        int currentTime = 0;

        while (currentTime < totalTime)
        {
            if (std::rand() % 100 < (visitorFrequency * 100))
            {
                int from = std::rand() % numFloors;
                int to = std::rand() % numFloors;
                // Ensure that the from and to floors are different
                while (from == to)
                {
                    to = std::rand() % numFloors;
                }
                newCall(from, to);
                numVisitors++;
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
        std::cout << "Total Visitors: " << numVisitors << "\n";
        std::cout << "Average Waiting Time: " << (numVisitors > 0 ? totalWaitingTime / numVisitors : 0) << " seconds\n";
    }
};