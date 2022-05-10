# Hell(Hanah & Edna Shell)
Implementation of a Shell in C program
## Group Members
Edna Bogdanić

Hanah Sijerčić
## Files
shell.c
## Answers from Task 1.5
## Q1:Do the following actions require the OS to use kernel mode or user mode is sufficient?
● A program wants to read from disk.

A ```read``` usually involves a hardware access.Accessing hardware is time-consuming and error-prone, and it can render the computer unusable. Drivers are used by the os  to control the hardware of the computer.

When a driver receives a ```read```(assuming it's a hard disk IO), it sends a set of directives to the disk controller, which causes it to read its output, pass it to main memory, and so on. These are risky operations that should never be left to User Mode.

● Reading the current time from the hardware clock.

If the hardware clocks include memory-mapped registers, you can view them freely from user mode as long as the mapped region contains no sensitive data (it may or may not, depends on the hardware).
## Q2:Explain the purpose of a system call. There are different sets of system calls: list them and give at least 2 examples of a system call for each category.
A system call is a communication link among a running program and the operating system. It enables the user to use the os system's services. Processes written in C, C++, and assembly language are used in these system calls. Each system call has its unique name in each operating system. Every system call is assigned a unique number to identify it.
## System Calls:
## *1.Process Control:* 
The execution of a program is a process. A process must be loaded into main memory before it can be executed. It may be necessary to wait, terminate, or establish and end child processes while it is running.

Examples in Unix/Windows

```●fork()/CreateProcess()```

```●exit()/ExitProcess()```

```●wait()/WaitForSingleObject()```
## *2.File Management:*
We can make and delete files using the system. The name of the file and other properties of the file are required for the creation and delete operations. File properties contain things like file type, size of the file, security codes, and accounting data. These properties are used by systems to conduct operations on files and directories. We can open and use the file once it has been created. Reading, writing, and relocating operations on files are also possible with the system.

Examples in Unix/Windows

```●open()/CreateFile()```

```●read()/ReadFile()```

```●write()/WriteFile()```

```●close()/CloseHandle()```
## *3.Device Management:* 
Whenever a process is operating, it requires a number of resources to do its task. Main memory, disk drives, files, and so forth are examples of these resources. The resource is allocated to the process if it is available. The process can read, write, and move the device once the resource has been allocated to it.

Examples in Unix/Windows

```●read()/ReadConsole()```

```●write()/WriteConsole()```

```●ioctl()/SetConsoleMode()```
## *4.Information Maintenance:* 
System calls are used to transfer data between the user software and the operating system. The existing date and time, the number of active users, the operating system version number, the quantity of free memory or disk space, and so on are all examples of system information. The operating system stores information about all of its processes in the form of system calls like get process characteristics and update program characteristics.

Examples in Unix/Windows

```●getpid()/GetCurrentProcessID()```

```●sleep()/Sleep()```

```●alarm()/SetTimer()```
## *5.Communication:* 
The system's processes communicate with one another. Message queue and shared memory are the two models used for communication. Sender process connects to receiving process by specifying receiving process name or identity for message transfer. When the communication is complete, the system disconnects the communicating processes.

Examples in Unix/Windows

```●pipe()/CreatePipe()```

```●shmget()/CreateFileMapping()```

```●mmap()/MapViewOfFile()```

## Outline of the Assignment
In the description we will superficially explain all the main items (commands) that were used in the implementation of the shell.

```cp```

*Stands for copy. This command is used to copy files or group of files or directory.*

*Options:*

**1. -i(interactive): i** *stands for Interactive copying. With this option system first warns the user before overwriting the destination file*.

**2. -b(backup):** *With this option cp command creates the backup of the destination file in the same folder.*

**3. -f(force):** *If the system is unable to open destination file because the user doesn’t have writing permission, then by using -f option, destination file is deleted first and then copying of content is done from source to destination file.*

**4. -r or -R:** *Copying directory structure. With this option cp command copies the entire directory structure recursively.*

**5. -p(preserve):** *With -p option cp preserves the characteristics(permission bits, ownership...) of each source file in the corresponding destination file.*

```history```

*History command is used to view the previously executed command.*

*Options:*

**1. -c:**	*Clear the history list by deleting all of the entries.*

**2. -d offset:**	*Delete the history entry at offset OFFSET.*

**3. -a:**	*Append history lines from this session to the history file.*

**4. -n:**	*Read all history lines not already read from the history file.*

**5. -r:**	*Read the history file and append the contents to the history list.*

**6. -w:**	*Write the current history to the history file and append them to the history list.*

**7. -p:**	*Perform history expansion on each ARG and display the result without storing it in the history list.*

**8. -s:**	*Append the ARGs to the history list as a single entry.*

```free```

*Free command displays the total amount of free space available along with the amount of memory used and swap memory in the system, and also the buffers used by the kernel.*

*Options:*

**1. -b, -bytes:** *It displays the memory in bytes.*

**2. -k, -kilo:** *It displays the amount of memory in kilobytes(default).*

**3. -m, -mega:** It displays the amount of memory in megabytes.*

**4. -g, -giga:** It displays the amount of memory in gigabytes.*

**5. -tera:** *It displays the amount of memory in terabytes.*

**6. -h, -human:** *It shows all output columns automatically scaled to shortest three digit unit and display the units also of print out. The units used are B(bytes), K(kilos), M(megas), G(gigas), and T(teras).*

**7. -c, -count:** *It displays the output c number of times and this option actually works with -s option.*

**8. -l, -lohi:** *It shows the detailed low and high memory statistics.*

**9. -o, -old:** *This option disables the display of the buffer adjusted line.*

**10. -s, -seconds:** *This option allows you to display the output continuously after s seconds delay. In actual, the usleepsystem call is used for microsecond resolution delay times.*

**11. -t, -total:** *It adds an additional line in the output showing the column totals.*

**12. -help:** *It displays a help message and exit.*

**13. -V, -version:** *It displays version info and exit.*

```fortune/Random Quotes```

*Displays random disturbing, inspirational, silly or sarchastic phrases from a database of quotations.*

*Options:*

**1. -a:**	*Choose from all databases, regardless of whether they are considered "offensive" or not.*

**2. -e:**	*Make the probability of choosing a fortune file equal to that of all other files.*

**3. -f:**	*Print out a list of all fortune files that would have been searched, but do not print a fortune.*

**4. -i:**	*When used with -m, make regular expression searching case-insensitive.*

**5. -l:**	*Use only quotations longer than the length specified with -n, or 160 characters if -n is not used.*

**6. -m:** *[pattern]	Print all fortunes matching the regular expression specified in [pattern]*

**7. -n:** *[length]	Override the length used by -l and -s to determine "long" and "short" messages (default 160 characters).*

**8. -o:**	*Choose only from "offensive" databases.*

**9. -s:**	*Use only quotations shorter than the length specified with -n, or 160 characters if -n is not used.*

**10.-w:**	*Wait for a period of time before terminating; useful for situations in which a fortune needs to be read before the screen is cleared.*

```forkbomb```

*The fork bomb is a form of denial-of-service (DoS) attack against a Linux based system.It forks processes infinitely to fill memory.*
## Instructions for compiling 
```gcc shell.c -o shell```

```./shell```
## Challenges
Researching material that was needed to create a code for project

Lack of or incomprehensible resources

Difficulty to understand and implement some of the built-in C functions

## Sources/Tutorials
https://www.geeksforgeeks.org/making-linux-shell-c/

https://www.cs.cornell.edu/courses/cs414/2004su/homework/shell/shell.html

https://www.guru99.com/introduction-to-shell-scripting.html

https://www.linuxtechi.com/learn-use-fork-vfork-wait-exec-system-calls-linux/

https://g4greetz.wordpress.com/tag/fork-bomb-in-c/

https://www.cyberciti.biz/faq/copy-command/#:~:text=cp%20is%20the%20command%20entered,same%20or%20a%20different%20name.

https://stackoverflow.com/questions/5050479/history-implementation-in-a-simple-shell-program-in-c

https://www.tutorialspoint.com/c_standard_library/c_function_free.htm

https://securitronlinux.com/bejiitaswrath/very-useful-c-program-print-a-random-fortune/

https://www.systutorials.com/how-to-get-the-hostname-of-the-node-in-c/

https://www.programiz.com/c-programming/c-file-input-output

https://tuxthink.blogspot.com/2012/12/c-program-in-linux-to-find-username-of.html
