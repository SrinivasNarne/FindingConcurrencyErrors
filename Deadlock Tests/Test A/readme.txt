DEADLOCK TESTS

FIRST TEST

Type = Real Deadlock
Number of Threads Used = 2

Deadlock Scenario:

In this scenario both the threads call open() in Mode 2 one after the another. Each open() call increments the "count2". As a result the result the count2 value is greater than 1 (2 in this case). In this situation both the threads call ioctl in mode 1 resulting in both the threads switching to the wait state. Both the threads keep on waiting and none of them gets released. Hence the value of count2 will never go back to 1. As a result no other thread will be able to change the mode.
