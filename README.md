# Philosophers (July/2022)
Eat, Sleep, Spaghetti, repeat. This project is about learning how threads work by precisely timing a group of philosophers on when to pick up forks and eat spaghetti without dying from hunger. The dining philosophers problem in c :person_white_hair:



        
# Usage

- Clone the project in your environment
~~~shell
git clone git@github.com:Danimdf/Philosophers.git
~~~
- Run the project
~~~shell
make
~~~~
- And pass the following arguments to run the program
~~~shell
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [ <must_eat> ]
~~~

- number_of_philosophers -> the number of philosophers and forks.
- time_to_die -> A philosopher dies if he doesn't start to eat time_to_die ms after the beginning of his last meal.
- time_to_eat -> The time it takes for a philosopher to eat.
- time_to_sleep -> The time it takes for a philosopher to sleep.
- must_eat (optional) -> Maximum number of meals philosophers can have, just after everyone eats must_eat times the program ends. For example with ./philo 10 500 100 200 3.

<p>If a number of meals is not specified the simulation stops at the death of any philosophers.</p>

# Allowed Functions

<table>
 <thead>
        <th>
            Functions Externals
        </th>
        <th>
            Description
        </th>
 </thead>
 <tbody>
        <tr>
            <td><a href="https://www.youtube.com/watch?v=fqCJAVW9NLY">Memset</a></td>
            <td>Copies the character c (an unsigned char) to the first n characters of the string pointed to, by the argument str. </td>
        </tr>
        <tr>
            <td><a href="https://man7.org/linux/man-pages/man3/usleep.3.html">Usleep</a></td>
            <td>Suspends execution of the calling thread for (at least) usec microseconds.  The sleep may be lengthened slightly by any system activity or by the time                 spent processing the call or by the granularity of system timers. </td>
        </tr>
        <tr>
            <td><a href="https://man7.org/linux/man-pages/man2/gettimeofday.2.html">Gettimeofday</a></td>
            <td>Can get and set the time as well as a timezone. </td>
        </tr>
        <tr>
            <td><a href="https://man7.org/linux/man-pages/man3/pthread_create.3.html">Pthread_create</a></td>
            <td>Starts a new thread in the calling process.  </td>
        </tr>
        <tr>
            <td><a href="https://www.geeksforgeeks.org/thread-functions-in-c-c/">pthread_detach</a></td>
            <td>Used to detach a thread. A detached thread does not require a thread to join on terminating. The resources of the thread are automatically released                     after terminating if the thread is detached. </td>
        </tr>
        <tr>
            <td><a href="https://man7.org/linux/man-pages/man3/pthread_join.3.html">pthread_join</a></td>
            <td>Waits for the thread specified by thread to terminate.  If that thread has already terminated, then pthread_join() returns immediately.  The thread                     specified by thread must be joinable.ed to detach a thread. A detached thread does not require a thread to join on terminating. The resources of the                   thread are automatically released after terminating if the thread is detached. </td>
        </tr>
         <tr>
            <td><a href="https://man7.org/linux/man-pages/man3/pthread_mutex_init.3p.html">pthread_mutex_init</a></td>
            <td>Destroy and initialize a mutex </td>
        </tr>
        <tr>
            <td><a href="https://man7.org/linux/man-pages/man3/pthread_mutex_destroy.3p.html">pthread_mutex_destroy</a></td>
            <td>Shall destroy the mutex object referenced by mutex; the mutex object becomes, in effect, uninitialized. An implementation may cause                                     thread_mutex_destroy() to set the object referenced by mutex to an invalid value.</td>
        </tr>
         <tr>
            <td><a href="https://linux.die.net/man/3/pthread_mutex_lock">pthread_mutex_lock</a></td>
            <td>Lock a mutex</td>
        </tr>
        <tr>
            <td><a href="https://linux.die.net/man/3/pthread_mutex_unlock">pthread_mutex_unlock</a></td>
            <td>Unlock a mutex</td>
        </tr>
</tbody>
