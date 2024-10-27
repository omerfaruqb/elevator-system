# Elevator System Simulation

## Project Overview

This project simulates an elevator system in a building with multiple floors, where elevators respond to calls from visitors on different floors. The main objective is to optimize the elevators' performance based on waiting time and energy consumption.

## Project Structure

- **main.cpp**: Main driver of the simulation, configuring the parameters of the simulation.
- **Elevator.cpp**: Defines the `Elevator` class, representing each elevator's direction, and stop handling.
- **ElevatorSystem.cpp**: Manages the interaction between elevators, assigns calls, and records performance metrics.

## Simulation Overview

1. **Elevator Assignment**: When a new call is made, the system assigns the most suitable elevator based on:
   - Current direction.
   - Distance to the call floor.
   - Expected energy consumption and waiting time.
   
2. **Elevator Movement**: Each elevator handles stops sequentially, picking up or dropping off passengers based on the shortest route.

3. **Metrics**: The simulation tracks total waiting time, energy consumption, and number of visitors.

## Usage

1. Configure the parameters in main.cpp.


2. Compile the code:
    ```bash
    g++ main.cpp -o elevator_simulation
    ```

3. Run the simulation:
    ```bash
    ./elevator_simulation
    ```

## Sample Results

After running the simulation, results include:
- **Total Energy Consumed**: Represents the movement cost in units.
- **Average Waiting Time**: Mean waiting time per visitor (the time passed in the elevator is included)

Example output:
```plaintext
Simulation Results:
Total Energy Consumed: 437 units
Average Waiting Time: 16 seconds