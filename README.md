# Labs 3-4
by Oleg Sidorenkov BSE204

## Task 1:

### Guide:
- Write ***gcc task1.c -o get_user_info*** to compile the project
- And now write ***./task1*** to run it

### Observations:

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

### Guide:
- Write ***gcc task2.c -o get_user_info*** to compile the project
- And now write ***./task2*** to run it

### Observations:

Looks like task2 is ran by 2 processes: both child and parent.

    >HW % gcc -o task2 task2.c
    >HW % ./task2
    Hello, I am a parent process!
    Process ID is 9847, process parent's ID is 9375!
    Hey there, I am a child process!
    Process ID is 9848, process parent's ID is 1!
    >HW % ./task2
    Hello, I am a parent process!
    Process ID is 9849, process parent's ID is 9375!
    Hey there, I am a child process!
    Process ID is 9850, process parent's ID is 1!
    >HW % ./task2
    Hello, I am a parent process!
    Process ID is 9851, process parent's ID is 9375!
    Hey there, I am a child process!
    Process ID is 9852, process parent's ID is 1!
