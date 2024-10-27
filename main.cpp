#include "ElevatorSystem.cpp"

int main()
{
    int numFloors = 10;
    double visitorFrequency = 0.5;
    int totalTime = 100;
    int numElevators = 5;
    int startingFloor = 0;

    ElevatorSystem elevatorSystem(numElevators, startingFloor);
    elevatorSystem.runSimulation(numFloors, visitorFrequency, totalTime);

    return 0;
}