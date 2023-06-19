# philosophers

The "philosophers" repository contains the C implementation of a program that simulates the classic dining philosophers problem. The program takes arguments such as the number of philosophers, the time it takes to die, eat, and sleep, and optionally, the number of times they need to eat.

The project is divided into two folders: "philo" and "philo_bonus." The "philo" folder contains the implementation using a single multi-threaded process and the utilization of mutexes. The "philo_bonus" folder contains the implementation using multiple processes and the utilization of semaphores.

This project was developed as part of the curriculum at 42School and has achieved a score of 125 out of 100.

## Description

The dining philosophers problem is a classic example used in computer science to illustrate the issues of resource allocation and synchronization in concurrent systems. The problem involves a group of philosophers sitting around a table, each with a plate of spaghetti and a fork between each pair of adjacent philosophers. The philosophers alternate between thinking and eating. To eat, a philosopher must acquire the two forks adjacent to them.

The goal of the project is to implement a solution that allows the philosophers to dine without encountering issues such as deadlocks or starvation. The program handles the synchronization between the philosophers' actions (eating, sleeping, and thinking) and ensures that they adhere to the rules of acquiring forks.

## Usage

1. Clone the repository to your local system:
	```shell
	git clone https://github.com/stenterello/philosophers.git

2. Navigate to the desired folder (`philo` or `philo_bonus`) in the main directory:
	```shell
	cd philosophers/philo

or  
```shell
	cd philosophers/philo_bonus
```

3. Compile the program using the provided Makefile:
	```shell
	make

Note: If you encounter compilation errors related to printing, you can modify the formatting from %llu to %lu or vice versa. This adjustment may be necessary due to differences in compilation between macOS and Linux platforms.

4. Execute the program with the desired arguments:
	```shell
	./philo arg1 arg2 arg3 arg4 [arg5]

- arg1: number of philosophers
- arg2: time to die (in milliseconds)
- arg3: time to eat (in milliseconds)
- arg4: time to sleep (in milliseconds)
- arg5 (optional): number of times each philosopher must eat before they stop


## Folder Structure

Folder Structure
The repository has the following folder structure:

- philo/: Contains the code for the dining philosophers problem implementation using a single multi-threaded process and mutexes.
- philo_bonus/: Contains the code for the dining philosophers problem implementation using multiple processes and semaphores.