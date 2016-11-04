DEADLOCK TESTS

SECOND TEST

Type = Real Deadlock
Number of Threads Used = 2

Deadlock Scenario:

Like in the first scenario, here both the threads call open() in mode 2. The count2 is incremented by both the threads when they are opened. Then the first thread is killed which results in its exit without decrementing the count2. Then the second thread calls ioctl in mode 1 and switches to "sleep" as the value of count2 is greater than one. As a result the value of count2 never goes back to 1 and no other thread can change the mode.
