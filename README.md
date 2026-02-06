*This project has been created as part of the 42 curriculum by esakgul.*

# Philosophers

## Description

This project is a simulation of the classic **Dining Philosophers problem**, a well-known concurrency problem in computer science. The goal of this project is to learn the basics of multithreading, how to create and manage threads, and how to use mutexes to protect shared resources.

### The Problem

One or more philosophers sit at a round table with a large bowl of spaghetti in the middle. Philosophers alternate between three states:

- **Eating**
- **Thinking**
- **Sleeping**

Key rules of the simulation:

- There are as many forks as philosophers.
- To eat, a philosopher must hold **two forks** at the same time (left and right).
- After eating, a philosopher puts down the forks and goes to sleep.
- After sleeping, the philosopher starts thinking.
- The simulation stops when a philosopher dies of starvation.
- Philosophers do not communicate with each other.
- Philosophers do not know if another philosopher is about to die.

### Technical Constraints

- **Mandatory part**
  - Each philosopher is a thread.
  - Forks are protected by mutexes.
  - No data races allowed.
- **Bonus part (if implemented)**
  - Each philosopher is a process.
  - Forks are represented by semaphores.
- Written in **C** following the **42 Norm**.
- **Global variables are forbidden.**

---

## Instructions

### Compilation

#### Mandatory part

```bash
cd philo
make
````
---

### Execution

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

### Arguments

1. **number_of_philosophers**
   Number of philosophers and forks.

2. **time_to_die (ms)**
   If a philosopher does not start eating within this time since their last meal (or since the start of the simulation), they die.

3. **time_to_eat (ms)**
   Time a philosopher spends eating (while holding two forks).

4. **time_to_sleep (ms)**
   Time a philosopher spends sleeping.

5. **number_of_times_each_philosopher_must_eat (optional)**
   If all philosophers eat at least this many times, the simulation stops.
   If not specified, the simulation stops when a philosopher dies.

---

### Usage Example

```bash
./philo 5 800 200 200
```

This runs a simulation with:

* 5 philosophers
* 800ms time to die
* 200ms time to eat
* 200ms time to sleep

---

## Resources

### References

* Dining Philosophers Problem
  [https://en.wikipedia.org/wiki/Dining_philosophers_problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

* POSIX Threads Programming
  [https://computing.llnl.gov/tutorials/pthreads/](https://computing.llnl.gov/tutorials/pthreads/)

* pthread_mutex documentation
  [https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html](https://man7.org/linux/man-pages/man3/pthread_mutex_lock.3.html)

* gettimeofday documentation
  [https://man7.org/linux/man-pages/man2/gettimeofday.2.html](https://man7.org/linux/man-pages/man2/gettimeofday.2.html)

---

### AI Usage

AI tools were used as a **learning aid** during the development of this project.

AI was used for:

* Understanding concurrency concepts (deadlock, starvation, data races)
* Clarifying pthread and mutex usage
* Debugging synchronization issues
* General documentation guidance

AI was **not used to blindly generate the project logic.**
All synchronization strategies, design decisions, and final implementations were written and validated by the author to ensure full understanding and compliance with 42 rules.

---

## Author

esakgul
42 Istanbul Student

---
