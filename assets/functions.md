# External Functions
- [Print Related](#print-related)
- [Memory Related](#memory-related)
- [File Descriptor Related](#file-descriptor-related)
- [Directory Related](#directory-related)
- [Terminal Related](#terminal-related)
- [Readline Related](#readline-related)
- [Signal Related](#signal-related)
- [Execution Related](#execution-related)
- [Fork Related](#fork-related)
- [Stat Related](#stat-related)
- [Unused](#unused-functions)
## Print Related
### printf
SYNOPSIS:

    #include <stdio.h>

    int printf(const char *format, ...);

DESCRIPTION:

    The functions in the printf() family produce output according to a format.

RETURN VALUE:

    Upon successful return, these functions return the number of characters printed (excluding the null byte
    used to end output to strings).

    If an output error is encountered, a negative value is returned.

### write
SYNOPSIS:

    #include <unistd.h>

    ssize_t write(int fd, const void *buf, size_t count);

DESCRIPTION:

    write() writes up to count bytes from the buffer starting at buf to the file referred to by the file
    descriptor fd.

RETURN VALUE:

    On success, the number of bytes written is returned. On error, -1 is returned, and errno is set to indicate
    the cause of the error.

## Memory Related
### malloc
SYNOPSIS:

    #include <stdlib.h>

    void *malloc(size_t size);

DESCRIPTION:

    The malloc() function allocates size bytes and returns a pointer to the allocated memory. The memory is not
    initialized. If size is 0, then malloc() returns either NULL, or a unique pointer value that can later be
    successfully passed to free().

RETURN VALUE:

    The malloc() function returns a pointer to the allocated memory, which is suitably aligned for
    any built-in type. On error, this function returns NULL. NULL may also be returned by a successful call
    to malloc() with a size of zero.

### free
SYNOPSIS:

    #include <stdlib.h>

    void free(void *ptr);

DESCRIPTION:

    The  free() function frees the memory space pointed to by ptr, which must have been returned by a previous
    call to malloc(), calloc(), or realloc(). Otherwise, or if free(ptr) has already been called before,
    undefined behavior occurs. If ptr is NULL, no operation is performed.

RETURN VALUE:

    The free() function returns no value.

##  File Descriptor Related
### open
SYNOPSIS:

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    int open(const char *pathname, int flags);
    int open(const char *pathname, int flags, mode_t mode);

DESCRIPTION:

    The open() system call opens the file specified by pathname. If the specified file does not exist, it may
    optionally (if O_CREAT is specified in flags) be created by open().

    A call to open() creates a new open file description, an entry in the system-wide table of open files.

    The argument flags must include one of the following access modes: O_RDONLY, O_WRONLY, or O_RDWR. These
    request opening the file read-only, write-only, or read/write, respectively.

    In  addition, zero or more file creation flags and file status flags can be bitwise-or'd in flags.

RETURN VALUE:

    open() returns the new file descriptor (a nonnegative integer), or -1 if an error occurred
    (in which case, errno is set appropriately).

### read
SYNOPSIS:

    #include <unistd.h>

    ssize_t read(int fd, void *buf, size_t count);

DESCRIPTION:

    read() attempts to read up to count bytes from file descriptor fd into the buffer starting at buf.

    On files that support seeking, the read operation commences at the file offset, and the file offset is
    incremented by the number of bytes read. If the file offset is at or past the end of file, no bytes are
    read, and read() returns zero.

    If count is zero, read() may detect the errors described below. In the absence of any errors, or if read()
    does not check for errors, a read() with a count of 0 returns zero and has no other effects.

RETURN VALUE:

    On success, the number of bytes read is returned (zero indicates end of file), and the file position is
    advanced by this number. 

    It is not an error if this number is smaller than the number of bytes requested; this may happen for example
    because fewer bytes are actually available right now (maybe because we were close to end-of-file,
    or because we are reading from a pipe, or from a terminal), or because read() was interrupted by a signal.

    On error, -1 is returned, and errno is set appropriately. In this case, it is left unspecified whether the
    file position (if any) changes.

### dup
SYNOPSIS:

    #include <unistd.h>

    int dup(int oldfd);    

DESCRIPTION:

    The dup() system call creates a copy of the file descriptor oldfd, using the lowest-numbered unused file
    descriptor for the new descriptor.

    After a successful return, the old and new file descriptors may be used interchangeably. They refer to the
    same open file description (see open(2)) and thus share file offset and file status flags;

RETURN VALUE:

    On success, this system calls returns the new file descriptor. On error, -1 is returned, and errno is set
    appropriately.

### dup2
SYNOPSIS:

    #include <unistd.h>

    int dup2(int oldfd, int newfd);    

DESCRIPTION:

    The dup2() system call performs the same task as dup(), but instead of using the lowest-numbered unused file
    descriptor, it uses the file descriptor number specified in newfd. If the file descriptor newfd was
    previously open, it is silently closed before being reused.

    Note the following points:

    *  If oldfd is not a valid file descriptor, then the call fails, and newfd is not closed.

    *  If oldfd is a valid file descriptor, and newfd has the same value as oldfd, then dup2() does nothing, and
        returns newfd.

RETURN VALUE:

    On success, this system calls returns the new file descriptor. On error, -1 is returned, and errno is set
    appropriately.

### close
SYNOPSIS:

    #include <unistd.h>

    int close(int fd);

DESCRIPTION:

    close() closes a file descriptor, so that it no longer refers to any file and may be reused. Any record
    locks.

    If fd is the last file descriptor referring to the underlying open file description, the resources
    associated with the open file description are freed; if the file descriptor was the last reference
    to a file which has been removed using unlink(2), the file is deleted.

RETURN VALUE:

    close() returns zero on success.  On error, -1 is returned, and errno is set appropriately.

## Directory Related
### getcwd
SYNOPSIS:

    #include <unistd.h>

    char *getcwd(char *buf, size_t size);

DESCRIPTION:

    The getcwd() function copies an absolute pathname of the current working directory to the array pointed to
    by buf, which is of length size.

    If the length of the absolute pathname of the current working  directory, including the terminating null
    byte, exceeds size bytes, NULL is returned, and errno is set to ERANGE; an application should check for this
    error, and allocate a larger buffer if necessary.

RETURN:

    On success, this function returns a pointer to a string containing the pathname of the current working
    directory. In the case of getcwd() this is the same value as buf.

    On failure, these functions return NULL, and errno is set to indicate the error. The contents of the array
    pointed to by buf are undefined on error.

### chdir
SYNOPSIS:

    #include <unistd.h>

    int chdir(const char *path);

DESCRIPTION:

    chdir() changes the current working directory of the calling process to the directory specified in path.

RETURN:

    On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

### opendir
SYNOPSIS:

    #include <sys/types.h>
    #include <dirent.h>

    DIR *opendir(const char *name);

DESCRIPTION:

    The opendir() function opens a directory stream corresponding to the directory name, and returns a pointer
    to the directory stream. The stream is positioned at the first entry in the directory.

RETURN:

    The opendir() function returns a pointer to the directory stream. On error, NULL is
    returned, and errno is set appropriately.

### readdir
SYNOPSIS:

    #include <dirent.h>

    struct dirent *readdir(DIR *dirp);

DESCRIPTION:

    The readdir() function returns a pointer to a dirent structure representing the next directory entry in the
    directory stream pointed to by dirp. It returns NULL on reaching the end of the directory stream or if an
    error occurred.

    The fields of the dirent structure are listed in the man readdir.

RETURN:

    On success, readdir() returns a pointer to a dirent structure. (This structure may be statically allocated;
    do not attempt to free it.)

    If the end of the directory stream is reached, NULL is returned and errno is not changed. If an error
    occurs, NULL is returned and errno is set appropriately. To distinguish end of stream from an error, set
    errno to zero before calling readdir() and then check the value of errno if NULL is returned.

### closedir
SYNOPSIS:

    #include <sys/types.h>
    #include <dirent.h>

    int closedir(DIR *dirp);

DESCRIPTION:

    The closedir() function closes the directory stream associated with dirp. A successful call to closedir()
    also closes the underlying file descriptor associated with dirp. The directory stream descriptor dirp is
    not available after this call.

RETURN:

    The closedir() function returns 0 on success.  On error, -1 is returned, and errno is set appropriately.

### unlink
SYNOPSIS:

    #include <unistd.h>

    int unlink(const char *pathname);

DESCRIPTION:

    unlink() deletes a name from the filesystem. If that name was the last link to a file and no processes have
    the file open, the file is deleted and the space it was using is made available for reuse.

    If the name was the last link to a file but any processes still have the file open, the file will remain in
    existence until the last file descriptor referring to it is closed.

    If the name referred to a symbolic link, the link is removed.

    If the name referred to a socket, FIFO, or device, the name for it is removed but processes which have the
    object open may continue to use it.

RETURN:

    On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

## Terminal Related
### getenv
SYNOPSIS:

    #include <stdlib.h>

    char *getenv(const char *name);

DESCRIPTION:

    The getenv() function searches the environment list to find the environment variable name, and returns a
    pointer to the corresponding value string.

RETURN:

    The getenv() function returns a pointer to the value in the environment, or NULL if there is no match.

### isatty
SYNOPSIS:

    #include <unistd.h>

    int isatty(int fd);

DESCRIPTION:

    The isatty() function tests whether fd is an open file descriptor referring to a terminal.

RETURN:

    isatty() returns 1 if fd is an open file descriptor referring to a terminal; otherwise 0 is returned, and
    errno is set to indicate the error.

### ttyname
SYNOPSIS:

    #include <unistd.h>

    char *ttyname(int fd);

DESCRIPTION:

    The function ttyname() returns a pointer to the null-terminated pathname of the terminal device that is open
    on the file descriptor fd, or NULL on error (for example, if fd is not connected to a terminal). The return
    value may point to static data, possibly overwritten by the next call. The function ttyname_r() stores this
    pathname in the buffer buf of length buflen.

RETURN:

    The function ttyname() returns a pointer to a pathname on success. On error, NULL is returned, and errno is
    set appropriately. The function ttyname_r() returns 0 on success, and an error number upon error.

### ttyslot
SYNOPSIS:

    #include <unistd.h>

    int ttyslot(void);

DESCRIPTION:

    The legacy function ttyslot() returns the index of the current user's entry in some file.

    In detail, the function ttyslot() returns the index of the controlling terminal of the calling process
    in  the file /etc/ttys, and that is (usually) the same as the index of the entry for the current user in 
    the file /etc/utmp. BSD still has the /etc/ttys file, but System V-like systems do not, and hence cannot
    refer to it.

    Thus, on such systems the documentation says that ttyslot() returns the current user's index in the
    user accounting data base.

    For more information about this legacy function, check man ttyslot.

RETURN:

    If successful, this function returns the slot number. On error (e.g., if none of the file descriptors 0, 1
    or 2 is associated with a terminal that occurs in this data base) it returns 0 on UNIX V6 and V7 and
    BSD-like systems, but -1 on System V-like systems.

### ioctl
SYNOPSIS:

    #include <sys/ioctl.h>

    int ioctl(int fd, unsigned long request, ...);

DESCRIPTION:

    The ioctl() system call manipulates the underlying device parameters of special files. In particular, many
    operating characteristics of character special files (e.g., terminals) may be controlled with ioctl()
    requests. The argument fd must be an open file descriptor.

    The second argument is a device-dependent request code. The third argument is an untyped pointer to memory.
    It's traditionally char *argp (from the days before void * was valid C), and will be so named for this
    discussion.

RETURN:

    Usually, on  success  zero is returned. A few ioctl() requests use the return value as an output parameter
    and return a nonnegative value on success. On error, -1 is returned, and errno is set appropriately.


## Readline Related
### readline
SYNOPSIS:

    #include <stdio.h>
    #include <readline/readline.h>
    #include <readline/history.h>

    char *readline (const char *prompt);

DESCRIPTION:

    readline will read a line from the terminal and return it, using prompt as a prompt. If prompt is NULL or
    the empty string, no prompt is issued.  The line returned is allocated with malloc(3); the caller must
    free it when finished. The line returned has the final newline removed, so only the text of the line
    remains.

    readline offers editing capabilities while the user is entering the line. By default, the line editing
    commands are similar to those of emacs. A vi-style line editing interface is also available.

RETURN VALUE:

    readline returns the text of the line read. A blank line returns the empty string. If EOF is encountered
    while reading a line, and the line is empty, NULL is returned. If an EOF is read with a non-empty line,
    it is treated as a newline.

### rl_clear_history
SYNOPSIS:

    #include <readline/readline.h>
    #include <readline/history.h>

    void rl_clear_history(void);

DESCRIPTION:

    The rl_clear_history() function clears the history list by deleting all of the entries.
    It frees data that the readline library saves in the histroy list.

RETURN VALUE:

    The rl_clear_history() function returns no value.

### rl_on_new_line
SYNOPSIS:

    #include <readline/readline.h>
    #include <readline/history.h>

    int rl_on_new_line(void);

DESCRIPTION:

    The rl_on_new_line() function tells the update routine that we have moved onto a new empty line,
    usually used after outputting a line.

RETURN VALUE:

    No information available.

### rl_redisplay
SYNOPSIS:

    #include <readline/readline.h>
    #include <readline/history.h>

    int rl_redisplay(void);

DESCRIPTION:

    The rl_redisplay() change what's displayed on the screen to reflect the current contents of rl_line_buffer.

RETURN:

    No information available.

### add_history
SYNOPSIS:

    #include <readline/readline.h>
    #include <readline/history.h>

    void add_history(char *s);

DESCRIPTION:

    The add_history() function saves the line passed as parameter in the history so it can be retrieved later
    in the terminal (like pressing the up arrow in bash).

RETURN VALUE:

    The add_history() function returns no value.

## Signal Related
### signal
SYNOPSIS:

     #include <signal.h>

    sighandler_t signal(int signum, sighandler_t handler);

DESCRIPTION:

    signal() sets the disposition of the signal signum to handler, which is either SIG_IGN, SIG_DFL, or the
    address of a programmer-defined function (a "signal handler").

    If the signal signum is delivered to the process, then one of the following happens:

    *  If the disposition is set to SIG_IGN, then the signal is ignored.

    *  If the disposition is set to SIG_DFL, then the default action associated with the signal occurs.

    *  If the disposition is set to a function, then first either the disposition is reset to SIG_DFL, or the
        signal  is  blocked (see Portability below), and then handler is called with argument signum.
        If invocation of the handler caused the signal to be blocked, then the signal is unblocked upon
        return from the handler.

    The signals SIGKILL and SIGSTOP cannot be caught or ignored.

RETURN VALUE:

    signal() returns the previous value of the signal handler, or SIG_ERR on error. In the event of an error,
    errno is set to indicate the cause.

### sigaction
SYNOPSIS:

     #include <signal.h>

    int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);

DESCRIPTION:

    The sigaction() system call is used to change the action taken by a process on receipt of a specific signal.
    (See signal(7) for an overview of signals.)

    signum specifies the signal and can be any valid signal except SIGKILL and SIGSTOP.

    If act is non-NULL, the new action for signal signum is installed from act. If oldact is non-NULL, the
    previous action is saved in oldact.

RETURN VALUE:

    sigaction() returns 0 on success; on error, -1 is returned, and errno is set to indicate the error.

### sigemptyset
SYNOPSIS:

     #include <signal.h>

    int sigemptyset(sigset_t *set);

DESCRIPTION:

    sigemptyset() initializes the signal set given by set to empty, with all signals excluded from the set.

    Objects of type sigset_t must be initialized by a call to sigemptyset() before being
    passed to the function sigaddset().

RETURN VALUE:

    sigemptyset() returns 0 on success and -1 on error.
    On error, it sets errno to indicate the cause of the error.

### sigaddset
SYNOPSIS:

     #include <signal.h>

    int sigaddset(sigset_t *set, int signum);

DESCRIPTION:

    sigaddset() adds and deletes respectively signal signum from set.

    Objects  of type sigset_t must be initialized by a call to sigemptyset() before being
    passed to the function sigaddset().

RETURN VALUE:

    sigaddset() returns 0 on success and -1 on error.
    On error, it sets errno to indicate the cause of the error.

## Execution Related
### access
SYNOPSIS:

    #include <unistd.h>

    int access(const char *pathname, int mode);

DESCRIPTION:

    access() checks whether the calling process can access the file pathname. If pathname is a symbolic link,
    it is dereferenced.

    The mode specifies the accessibility check(s) to be performed, and is either the value F_OK, or a mask
    consisting of the bitwise OR of one or more of R_OK, W_OK, and X_OK. F_OK tests for the existence of the
    file. R_OK, W_OK, and X_OK test whether the file exists and grants read, write, and execute permissions,
    respectively.

RETURN VALUE:

    On success (all requested permissions granted, or mode is F_OK and the file exists), zero is  returned.
    On error (at least one bit in mode asked for a permission that is denied, or mode is F_OK and the file
    does not exist, or some other error occurred), -1 is returned, and errno is set appropriately.

### execve
SYNOPSIS:

    #include <unistd.h>

    int execve(const char *pathname, char *const argv[], char *const envp[]);

DESCRIPTION:

    execve()  executes the program referred to by pathname. This causes the program that is currently being run
    by the calling process to be replaced with a new program, with newly initialized stack, heap,
    and (initialized and uninitialized) data segments.

RETURN VALUE:

    On success, execve() does not return, on error -1 is returned, and errno is set appropriately.

### perror
SYNOPSIS:

    #include <stdio.h>

    void perror(const char *s);

DESCRIPTION:

    The perror() function produces a message on standard error describing the last error encountered during a
    call to a system or library function.

    First (if s is not NULL and *s is not a null byte ('\0')), the argument string s is printed, followed by a
    colon and a blank. Then an error message corresponding to the current value of errno and a new-line.

    To be of most use, the argument string should include the name of the function that incurred the error.

RETURN:

    The perror() function returns no value.

### exit
SYNOPSIS:

    #include <stdlib.h>

    void exit(int status); 

DESCRIPTION:

    The exit() function causes normal process termination and the least significant byte of status
    (i.e., status & 0xFF) is returned to the parent.

RETURN VALUE:

    The exit() function does not return.

## Fork Related
### fork
SYNOPSIS:

    #include <sys/types.h>
    #include <unistd.h>

    pid_t fork(void);

DESCRIPTION:

    fork() creates a new process by duplicating the calling process. The new process is referred to as the
    child process. The calling process is referred to as the parent process.

    The child process and the parent process run in separate memory spaces. At the time of fork() both memory
    spaces have the same content. Memory writes, file mappings and unmappings performed by one of the processes
    do not affect the other.

RETURN VALUE:

    On success, the PID of the child process is returned in the parent, and 0 is returned in the child. On
    failure, -1 is returned in the parent, no child process is created, and errno is set appropriately.

### pipe
SYNOPSIS:

    #include <unistd.h>

    int pipe(int pipefd[2]);

DESCRIPTION:

    pipe() creates  a pipe, a unidirectional data channel that can be used for interprocess communication. The
    array pipefd is used to return two file descriptors referring to the ends of the pipe. pipefd[0] refers to
    the  read end of the pipe. pipefd[1] refers to the write end of the pipe. Data written to the write end of
    the pipe is buffered by the kernel until it is read from the read end of the pipe.

RETURN VALUE:

    On success, zero is returned. On error, -1 is returned, errno is set appropriately, and pipefd is left
    unchanged.

### wait
SYNOPSIS:

    #include <sys/types.h>
    #include <sys/wait.h>

    pid_t wait(int *wstatus);

DESCRIPTION:

    The wait()  system call suspends execution of the calling thread until one of its children terminates. The
    call wait(&wstatus) is equivalent to:

    waitpid(-1, &wstatus, 0);

RETURN VALUE:

    wait(): on success, returns the process ID of the terminated child; on error, -1 is returned.

### waitpid
SYNOPSIS:

    #include <sys/types.h>
    #include <sys/wait.h>

    pid_t waitpid(pid_t pid, int *wstatus, int options);
 
DESCRIPTION:

    The waitpid() system call suspends execution of the calling thread until a child specified by  pid  argument
    has  changed  state.  By default, waitpid() waits only for terminated children, but this behavior is
    modifiable via the options argument, as described below.

    The value of pid can be:

    < -1   meaning wait for any child process whose process group ID is equal to the absolute value of pid.

    -1     meaning wait for any child process.

    0      meaning wait for any child process whose process group ID is equal to that of the calling process at the time of the call to waitpid().

    > 0    meaning wait for the child whose process ID is equal to the value of pid.

    The value of options is an OR of zero or more of the constants as seen in man 2 waitpid.

RETURN VALUE:

    waitpid(): on success, returns the process ID of the child whose state has changed; if WNOHANG was specified
    and  one  or more child(ren) specified by pid exist, but have not yet changed state, then 0 is returned.  On
    error, -1 is returned.

### kill
SYNOPSIS:

    #include <sys/types.h>
    #include <signal.h>

    int kill(pid_t pid, int sig);

DESCRIPTION:

    The kill() system call can be used to send any signal to any process group or process.

    If pid is positive, then signal sig is sent to the process with the ID specified by pid.

    If pid equals 0, then sig is sent to every process in the process group of the calling process.

    If  pid  equals  -1,  then sig is sent to every process for which the calling process has permission to send
    signals, except for process 1 (init), but see below.

    If pid is less than -1, then sig is sent to every process in the process group whose ID is -pid.

    If sig is 0, then no signal is sent, but existence and permission checks are still performed;  this  can  be
    used to check for the existence of a process ID or process group ID that the caller is permitted to signal.

RETURN VALUE:

    On success (at least one signal was sent), zero is returned.  On error, -1 is returned, and errno is set
    appropriately.

## Stat Related
### stat 
SYNOPSIS:

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    int stat(const char *pathname, struct stat *statbuf);

DESCRIPTION:

    This function returns  information about a file, in the buffer pointed to by statbuf. No permissions are
    required on the file itself, but—in the case of stat()—execute (search) permission
    is required on all of the directories in pathname that lead to the file.

    stat() retrieves information about the file pointed to by pathname.

RETURN:

    On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

### lstat

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    int lstat(const char *pathname, struct stat *statbuf);

DESCRIPTION:

    This function returns  information about a file, in the buffer pointed to by statbuf. No permissions are
    required on the file itself, but—in the case of lstat()—execute (search) permission
    is required on all of the directories in pathname that lead to the file.

    lstat() is identical to stat(), except that if pathname is a symbolic link, then it returns information
    about the link itself, not the file that the link refers to.

RETURN:

    On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

### fstat

    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    int fstat(int fd, struct stat *statbuf);

DESCRIPTION:

    This function returns  information about a file, in the buffer pointed to by statbuf. No permissions are
    required on the file itself, but—in the case of fstat()—execute (search) permission
    is required on all of the directories in pathname that lead to the file.

    fstat() is identical to stat(), except that the file about which information is to be retrieved is specified
    by the file descriptor fd.

RETURN:

    On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.

## Unused Functions
- rl_replace_line
- strerror
- tcgetattr
- tcsetattr
- tgetent
- tgetflag
- tgetnum
- tgetstr
- tgoto
- tputs
- wait3 && wait4
