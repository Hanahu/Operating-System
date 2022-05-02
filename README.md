# Operating-System
Implementation of a Shell in C program
# Group Members
Edna Bogdanić

Hanah Sijerčić
# Files
shell.c
# Answers from Task 1.5
# Q1:Do the following actions require the OS to use kernel mode or user mode is sufficient?
● A program wants to read from disk.

● Reading the current time from the hardware clock.
# Q2:Explain the purpose of a system call. There are different sets of system calls: list them and give at least 2 examples of a system call for each category.
A system call is a communication link among a running program and the operating system. It enables the user to use the os system's services. Processes written in C, C++, and assembly language are used in these system calls. Each system call has its unique name in each operating system. Every system call is assigned a unique number to identify it.
# System Calls:
# 1.Process Control: 
The execution of a program is a process. A process must be loaded into main memory before it can be executed. It may be necessary to wait, terminate, or establish and end child processes while it is running.

Examples in Unix/Windows

●fork()/CreateProcess()

●exit()/ExitProcess()

●wait()/WaitForSingleObject()
# 2.File Management: 
We can make and delete files using the system. The name of the file and other properties of the file are required for the creation and delete operations. File properties contain things like file type, size of the file, security codes, and accounting data. These properties are used by systems to conduct operations on files and directories. We can open and use the file once it has been created. Reading, writing, and relocating operations on files are also possible with the system.
Examples in Unix/Windows
●open()/CreateFile()
●read()/ReadFile()
●write()/WriteFile()
●close()/CloseHandle()
# 3.Device Management: 
Whenever a process is operating, it requires a number of resources to do its task. Main memory, disk drives, files, and so forth are examples of these resources. The resource is allocated to the process if it is available. The process can read, write, and move the device once the resource has been allocated to it.
Examples in Unix/Windows
●read()/ReadConsole()
●write()/WriteConsole()
●ioctl()/SetConsoleMode()
# 4.Information Maintenance: 
System calls are used to transfer data between the user software and the operating system. The existing date and time, the number of active users, the operating system version number, the quantity of free memory or disk space, and so on are all examples of system information. The operating system stores information about all of its processes in the form of system calls like get process characteristics and update program characteristics.
Examples in Unix/Windows
●getpid()/GetCurrentProcessID()
●sleep()/Sleep()
●alarm()/SetTimer()
# 5.Communication: 
The system's processes communicate with one another. Message queue and shared memory are the two models used for communication. Sender process connects to receiving process by specifying receiving process name or identity for message transfer. When the communication is complete, the system disconnects the communicating processes.
Examples in Unix/Windows
●pipe()/CreatePipe()
●shmget()/CreateFileMapping()
●mmap()/MapViewOfFile()

# Outline of the Assignment
# Instructions for compiling 
gcc shell.c -o shell

./shell
# Challenges
Researching material that was needed to create a code for project

Lack of or incomprehensible resources

Difficulty to understand and implement some of the built-in C functions
# Sources/Tutorials
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
