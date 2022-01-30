# Labs 3-4
by Oleg Sidorenkov BSE204

## Task 1:

Tried running a program a several times.
Looks like after every launch the same parent process forks a new child, who's ID is 1 bigger than previous launch child's.

    >HW % gcc -o task1 task1.c
    >HW % ./task1 
    Process ID is 9445, Process parent's ID is 9375!
    >HW % ./task1
    Process ID is 9446, Process parent's ID is 9375!
    >HW % ./task1
    Process ID is 9447, Process parent's ID is 9375!
    >HW % ./task1
    Process ID is 9448, Process parent's ID is 9375!
    >HW % ./task1
    Process ID is 9449, Process parent's ID is 9375!
    >HW % ./task1
    Process ID is 9450, Process parent's ID is 9375!
    >HW % ./task1
    Process ID is 9451, Process parent's ID is 9375!
    >HW % ./task1
    Process ID is 9452, Process parent's ID is 9375!
    >HW % ./task1
    Process ID is 9453, Process parent's ID is 9375!
    >HW % ./task1
    Process ID is 9454, Process parent's ID is 9375!

## Task2: