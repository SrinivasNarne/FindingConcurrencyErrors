DEADLOCK TESTS

FOURTH TEST

Type = Not a Real Deadlock
Number of Threads Used = 2

Deadlock Scenario:

When the first thread calls open() in mode 1 like in test C, it increments the count and holds the semaphore sem2. As a result when the second thread calls open it increments the value of count1 and stops as the semaphore sem2 is being held by thread1. Then if the first thread is killed, this results in a deadlock as the semaphore is not released by the thread that got killed.
