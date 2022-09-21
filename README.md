# Philosophers
42 Philosophers project

## About
This project is a version of the [Dining Philosophers Problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem).

The goal of this project was to learn to avoid deadlock and race conditions when creating multithreaded applications.

### Rules
The program takes the following arguments:

`./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]`

- `number_of_philosophers`: The number of philosophers and also the number
of forks.
- `time_to_die` (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
- `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
- `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
- `number_of_times_each_philosopher_must_eat` (optional argument): If all philosophers have eaten at least `number_of_times_each_philosopher_must_eat` times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

### Output
The output of the program is in the format `<timestamp> <philosopher (1 to number_of_philosophers)> <action>`

Each philosopher logs the following actions:
- Taking a fork
- Eating
- Sleeping
- Thinking
- Dying

The logged messages are always in sequential order.

## Installation
The program is compiled into a `philo` executable using `make all`

## Example usage
The following example shows the result of 5 philosophers, that take 800ms to die, 200ms to eat, 200ms to sleep and will eat a minimum of 3 times (`./philo 5 800 200 200 3`):

[![asciicast](https://asciinema.org/a/x25lCkgZv10xPRuwVU1HBQvWq.svg)](https://asciinema.org/a/x25lCkgZv10xPRuwVU1HBQvWq)

Visually, it looks something like this (screenshot from [philosophers-vizualizer](https://nafuka11.github.io/philosophers-visualizer/)):

<img width="962" alt="Screen Shot 2022-09-21 at 11 57 32 AM" src="https://user-images.githubusercontent.com/21006147/191492157-92668c00-d92e-4407-8036-058ed61b6fec.png">
