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
        int bestElevatorIndex = -1;
        int minDistance = std::numeric_limits<int>::max();

        for (int i = 0; i < elevators.size(); ++i)
        {
            Elevator &elevator = elevators[i];

            if (elevator.isIdle())
            {
                int distance = elevator.distanceToFloor(from);
                if (distance < minDistance)
                {
                    bestElevatorIndex = i;
                    minDistance = distance;
                }
            }
        }

        if (bestElevatorIndex == -1)
        {
            for (int i = 0; i < elevators.size(); ++i)
            {
                Elevator &elevator = elevators[i];
                int distance = elevator.distanceToFloor(from);
                if (distance < minDistance)
                {
                    bestElevatorIndex = i;
                    minDistance = distance;
                }
            }
        }

        if (bestElevatorIndex != -1)
        {
            Elevator &elevator = elevators[bestElevatorIndex];
            elevator.addStop(from);
            elevator.addStop(to);
            numVisitors++;
        }
    }

    void updateElevators()
    {
        for (auto &elevator : elevators)
        {
            int move = elevator.move();
            totalEnergyConsumed += move;
            totalWaitingTime += move * elevator.passengers;
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