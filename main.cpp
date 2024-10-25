#include "ElevatorSystem.cpp"

int main()
{
    int numFloors = 10;
    int visitorFrequency = 10;
    int totalTime = 1000;
    int numElevators = 5;
    int startingFloor = 0;

    ElevatorSystem elevatorSystem(numElevators, startingFloor);
    elevatorSystem.runSimulation(numFloors, visitorFrequency, totalTime);

    return 0;
}