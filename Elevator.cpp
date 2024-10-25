#include <iostream>
#include <vector>
#include <algorithm>

class Elevator
{
public:
    bool isMoving;
    std::vector<std::pair<int, bool>> stops; // {floor, isPickup}
    std::vector<std::pair<int, bool>> reverseStops; // {floor, isPickup}
    int currentFloor;
    int passengers;

    Elevator(int startFloor)
        : currentFloor(startFloor), isMoving(false), passengers(0) {}

    /**
     * @brief Add a passenger to the elevator with specified pickup and dropoff floors (from -> to)
     */
    void addPassenger(int from, int to)
    {
        stops.emplace_back(from, true);
        stops.emplace_back(to, false);
        std::sort(stops.begin(), stops.end());
        if (from > to) {
            std::reverse(stops.begin(), stops.end());
        }
        isMoving = true;
    }

    /**
     * @brief Variant of addPassenger for the passengers in the reverse direction 
     */
    void addPassengerReverse(int from, int to)
    {
        reverseStops.emplace_back(from, true);
        reverseStops.emplace_back(to, false);
        std::sort(reverseStops.begin(), reverseStops.end());
        if (from > to) {
            std::reverse(reverseStops.begin(), reverseStops.end());
        }
        isMoving = true;
    }

    /**
     * @brief Check if the elevator is moving up
     */
    bool isAscending() const
    {
        if (stops.empty())
        {
            return false;
        }
        return currentFloor < stops.front().first;
    }

    int distanceToFloor(int floor) const
    {
        return std::abs(currentFloor - floor);
    }

    int distanceToLastStop() const
    {
        if (stops.empty())
        {
            return 0;
        }
        return stops.back().first - stops.front().first;
    }

    int lastStop() const
    {
        if (stops.empty())
        {
            return currentFloor;
        }
        return stops.back().first;
    }

    bool isIdle() const
    {
        return !isMoving;
    }

    bool move()
    {   
        // Check if reverse stops are not empty, in case the route of the elevator is finished
        if (stops.empty() && !reverseStops.empty())
        {
            stops = reverseStops;
            reverseStops.clear();
        }
        if (stops.empty())
        {
            isMoving = false;
            return false;
        }

        int nextStop = stops.front().first;
        bool isPickup = stops.front().second;
        currentFloor += isAscending() ? 1 : -1;

        while (currentFloor == nextStop)
        {
            if (isPickup)
            {
                passengers++;
            }
            else
            {
                passengers--;
            }
            stops.erase(stops.begin());

            if (stops.empty())
            {
                isMoving = false;
                break;
            }

            nextStop = stops.front().first;
            isPickup = stops.front().second;
        }

        return true;
    }
};