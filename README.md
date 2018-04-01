# dining_philosophers

Benjamin A. Slack
CS5541, hw5
04/01/2018
benjamin.a.slack@wmich.edu

Summary:
A C++ 11 implementation of the dining philosopher problem, using thread and mutex classes

Description:
This is a CMAKE project, created in Microsoft Visual Studio C++, implementing the 
dining philosphers problem for mutual exclusion. It uses C++ 11 thread and mutex
classes, as well as roll your own barrier class I discovered on Stack Overflow
(URL credits in the header file). There are three executables in the package: 
dining_philosophers, deadlocked_philosophers and starving_philosophers. These
illustrate mutual exclusions proper use, use resulting a deadlock of threads and
finally use in which initial threads holding the holding locks are allowed to
starve threads who make it last to "picking up the forks" as it were.

Usage:
<executable name> [-h] [-v] [...]

[-h] prints the usage message above
[-v] runs in verbose mode, showing all actions of the dinner. Without flag,
  as summary of the dinner is given after it completes.
[...] an arbitrary list of philospher names who will participate in the dinner

Make:
A CMAKE project is provide as well as custom Makefile for simplicities sake.
