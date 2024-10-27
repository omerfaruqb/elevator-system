#include "ElevatorSystem.cpp"

int main()
{
    int numFloors = 100;
    double visitorFrequency = 0.5;
    int totalTime = 100;
    int numElevators = 5;
    int startingFloor = 0;
    int maxCapacity = 10;

    ElevatorSystem elevatorSystem(numElevators, startingFloor, maxCapacity);
    elevatorSystem.runSimulation(numFloors, visitorFrequency, totalTime);

    return 0;
}