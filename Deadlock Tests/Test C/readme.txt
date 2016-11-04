DEADLOCK TESTS

THIRD TEST

Type = Real Deadlock
Number of Threads Used = 2

Deadlock Scenario:

When the first thread calls open(), it increments the value of count1 and holds the semaphore sem2. When the second thread calls open() it increments the count1 and stops as the sem2 is already being held by the first thread. Now the first thread calls ioctl in mode 2 and goes into wait state as the value of count1 is greater than one. As a result both the threads do not reach close() and there is no possibility for the value of count1 to go back to 1. As a result a deadlock arises.
