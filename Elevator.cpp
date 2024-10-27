#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define DEBUG 1

#if DEBUG
#define debug(x) std::cerr << x << std::endl
#else
#define debug(x)
#endif

class Elevator
{
public:
    static int nextId;
    enum Direction
    {
        IDLE,
        UP,
        DOWN
    };
    int id;
    Direction direction;
    std::vector<std::pair<int, bool>> stops;        // {floor, isPickup}
    std::vector<std::pair<int, bool>> reverseStops; // {floor, isPickup}
    int currentFloor;
    int numPassengersWaiting;
    int numPassengersPickedUp;
    int capacity;

    Elevator(int startFloor, int capacity = 10)
        : id(nextId++), direction(IDLE), currentFloor(startFloor), numPassengersWaiting(0), numPassengersPickedUp(0), capacity(capacity) {}

    /**
     * @brief Add a passenger to the elevator with specified pickup and dropoff floors (from -> to)
     */
    void addPassenger(int from, int to)
    {
        stops.emplace_back(from, true);
        stops.emplace_back(to, false);
        sortStops();
        numPassengersWaiting++;
    }

    /**
     * @brief Variant of addPassenger for the passengers in the reverse direction of the current elevator route
     */
    void addPassengerReverse(int from, int to)
    {
        reverseStops.emplace_back(from, true);
        reverseStops.emplace_back(to, false);

        numPassengersWaiting++;
    }

    /**
     * @brief Get the last floor of the elevator heading to
     */
    int lastStop() const
    {
        return stops.empty() ? currentFloor : stops.back().first;
    }

    bool isAscending() const
    {
        return direction == UP;
    }

    int distanceToFloor(int floor)
    {
        int distance = std::abs(currentFloor - floor);
        return distance;
    }

    int distanceToLastStop()
    {
        int distance = stops.empty() ? 0 : distanceToFloor(stops.back().first);
        return distance;
    }

    bool isIdle() const
    {
        return direction == IDLE;
    }

    void sortStops()
    {
        if (stops.size() < 2)
        {
            return;
        }

        int firstFloor = stops.front().first;
        int lastFloor = stops.back().first;

        if (firstFloor < lastFloor)
        {
            std::sort(stops.begin(), stops.end());
        } else {
            std::sort(stops.rbegin(), stops.rend());
        }
    }

    bool move()
    {
        // Check if reverse stops are not empty, in case the route of the elevator is finished
        if (stops.empty() && !reverseStops.empty())
        {
            stops = reverseStops;
            reverseStops.clear();
            sortStops();
            debug("Switched");
        }
        else if (stops.empty())
        {
            direction = IDLE;
            return false;
        }

        int nextStop = stops.front().first;
        bool isPickup = stops.front().second;
        direction = currentFloor < nextStop ? UP : DOWN;
        currentFloor += direction == UP ? 1 : -1;

        while (currentFloor == nextStop)
        {
            if (isPickup)
            {
                numPassengersWaiting--;
                numPassengersPickedUp++;
                debug("[" << id << "] Picked up at " << currentFloor << ". Total: " << numPassengersPickedUp);
            }
            else
            {
                numPassengersPickedUp--;
                debug("[" << id << "] Dropped off at " << currentFloor << ". Total: " << numPassengersPickedUp);
            }
            stops.erase(stops.begin());

            if (stops.empty())
            {
                direction = IDLE;
                break;
            }
            nextStop = stops.front().first;
            isPickup = stops.front().second;
        }

        return true;
    }
};

int Elevator::nextId = 0;
