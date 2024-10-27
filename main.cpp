#include "ElevatorSystem.cpp"

int main()
{
    int numFloors = 20;
    double visitorFrequency = 0.5;
    int totalTime = 100;
    int numElevators = 5;
    int startingFloor = 0;
    int maxCapacity = 10;
    int alpha = 1; // Weight for waiting time
    int beta = 2; // Weight for energy consumed

    ElevatorSystem elevatorSystem(numElevators, startingFloor, maxCapacity, alpha, beta);
    elevatorSystem.runSimulation(numFloors, visitorFrequency, totalTime);

    return 0;
}