# Builtin

a Builtin or an Internal Command is a command whose code is compiled as part of the shell executable itself, i.e.
the shell doesn’t need to execute an external program,
nor does it need to `fork` a new process in order to execute the command.
Many of the commands we use on daily basis, such as `cd`, `echo`, `export`, and `readonly` are in fact builtin utilities.
You can read more about shell builtin utilities in this `POSIX` standard [link](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html).