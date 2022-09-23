# -new-ls-command



./myls [options] [file list]
[options]: Optional options from the list below. May be specified in any order or grouping, such as “” (none), “-i”, “-i -l -R”, “-iRl” “-R -li”, “-lR”…
[file list]: Optional space separated list of paths to files or directories to display.

Options: Implement the following options (you need not support any other options, and you need not  support the long version of the option names):
-i: Print the index number of each file
-l: Use a long listing format
-R: List subdirectories recursively. (Make sure that recursion must not cause any infinite loop)

The format of the output  of myls [options] [file list] should  be EXACTLTY same as ls [options] [file lists]

Sort :  Sort the files and directories lexicographically. When printing directories recursively (-R option), do a depth-first traversal of the directories, entering sibling directories in lexicographical order.

Date Format : When using the -l option you must print out date information in the following format:
mmm dd yyyy hh:mm
For example:
Oct  2 2021 14:52
Sep 30 2021 00:01
Specifically:
mmm    Initial three characters of month name; first letter capitalized.
dd     Two digit day of month; pad with space (‘ ‘) for single digit day.
yyyy   Four digit year number; pad with spaces (‘ ‘) if less than 4 digits.
hh     Two digit hour (24 hour clock); pad with zero (‘0’) if less than 2 digits.
mm     Two digit minute; pad with zero (‘0’) if less than 2 digits.



Special Paths
You must support the following paths with special meaning (x and y are arbitrary names):
/    Root directory (when at the front of path of the path such as /usr)
/x/y Absolute path to a file or directory
/xy/ Absolute path to a directory
x/y  Relative path to a file or directory
x/y/ Relative path to a directory
~   User’s home folder (can be used such as ~  or  ~/test/this/out)
.   Current directory
..  Up one directory (can be used such as  ../  or  ../../oh/my/../really/.. )
*    Wildcard (such as *.c); most of this work will be done by the shell!

 Simplifications vs built-in ls command
Do not print the “Total 123456” line at the top of the output when using the -l option.
All options (if any) must be specified before any files/directories (if any). 
You do not need to support quoted strings as arguments:
$ myls "thank goodness we don’t/have to support this/"
$ myls 'it is like a "gift" not to do this!.txt'
$ myls 'seemed like a good idea.c'



