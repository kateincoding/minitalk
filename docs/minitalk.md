# Important knowledge for the project

## What is a signal?
Signals are standardized messages send to a running program to trigger specific behavior (such quitting or error handling). They are a limited form of inter-process communication (IPC), typically used in Unix, Unix-like, and other POSIX-compliant operating systems.

* it shows all the posible signals that we can work
```
kill -l
```

* to kill a process
```
kill -SIGSTOP <PID>
```

* to know all the open process that I have <PID>
```
ps u
```

## List of commands

* write
* [signal](https://man7.org/linux/man-pages/man2/signal.2.html)
* [sigemptyset](https://man7.org/linux/man-pages/man3/sigemptyset.3p.html)
* [sigaddset](https://man7.org/linux/man-pages/man3/sigaddset.3p.html)
* [sigaction](https://man7.org/linux/man-pages/man2/sigaction.2.html)
* kill
* getpid
* malloc
* free
* pause
* sleep
* usleep
* exit

## signal
sets the disposition of the signal signum to handler, which is either SIG_IGN, SIG_DFL, or the address of a programmer-defined function (a "signal handler").

## sigkill
finish a process
```
kill -SIGKILL <pid>
```

## sigstop
pause a process
```
kill -SIGSTOP <pid>
```

## sigcont
to continue the process that is in pause
```
kill -SIGCONT <pid>
```
