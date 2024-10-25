#include <iostream>
#include <vector>

class Elevator
{
public:
    bool isMoving;
    std::vector<int> stops;
    int currentFloor;
    int passengers;

    Elevator(int startFloor)
        : currentFloor(startFloor), isMoving(false), passengers(0) {}

    void addStop(int floor)
    {
        stops.push_back(floor);
        passengers++;
        isMoving = true;
    }

    int distanceToFloor(int floor) const
    {
        return std::abs(currentFloor - floor);
    }

    bool isIdle() const
    {
        return !isMoving && stops.empty();
    }

    int move()
    {
        if (stops.empty())
        {
            isMoving = false;
            return 0;
        }

        int nextStop = stops.front();
        if (currentFloor < nextStop)
        {
            currentFloor++;
        }
        else if (currentFloor > nextStop)
        {
            currentFloor--;
        }
        else
        {
            stops.erase(stops.begin());
            passengers--;
        }

        if (stops.empty())
        {
            isMoving = false;
        }

        return 1;
    }
};