Betim Sejdiu

I started this process by making env. This was pretty simple, I simply used the example C file given to us and
implemented that code in bsh.c and instead of printing it I stored the strings into an array.

Then I went and implemented setenv. I started by implementing the logic of setting a new env. This was as simple
as adding the string at the end and incrementing the size of the string array. Implementing the logic of finding
the env variable and seeing if it existed made me need to use string sep. So I just seperated the string with
the delimiter of "=" and compared the string with the env trying to get passed. If I see the env I overwrite the
entire string.

Unsetenv was much easier considering I had the searching logic done in setenv. So I copied that code and when I
found the varaiable I freed it and set that pointer equal to the string in the next iteration of the array until
I went through the array.

Cd was a little more complicated to implement. I had an if else where the if was when the argument after cd was either
null or tilde. In those cases we update the PWD to home. In that case I searched for home and got the address after the
equal sign and set PWD to a copy of that string. In the other cases where there is some sort of address passed I called
chdir(). There is a function associated with chdir(), getcwd() that takes the current working directory and stores it
into a string. After chdir I simply found PWD again and set the path equal to the return string getcwd().

History was very simple to implement. I did this by making an array of strings and after every call of a command
I simply stored the cmdline into an array and kept track of the size and made sure enough size was allocated when
everytime a cmd line was added. Printing it was as easy a forloop that iterated through the size and printed
every string in the array.

The linux commands was the most complex portion of the project. This was because we firstly must find the PATH and get
the value of that variable. After this I needed to go through all the string and constantly seperating with every ":"
and seeing if that path results in an executable using the command access(). If this is true we give the task of
executing the linux command to a child process so the result doesn't stop our bsh program.
