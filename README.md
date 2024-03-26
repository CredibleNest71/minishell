# minishell
our minishell 

echo hi2 >hola1.txt | cat <hola1.txt
-> if hola1.txt doesnt exist, pipe is empty, both cmds are executed at the same time so cat will throw an error: "bash: hola.txt: No such file or directory" but hola1.txt will still be created

Things to test (Artem version)
1) exit pipe exit
2) echo abc > abc pipe cat << eof
   and then press ctrl c, nothing should be created
4) create variables with export that contain special chars like pipes and rtedirections. Compare output with bash.
5) create folder and try to type folder name, it should say command not found. If it says smt else, try to execute folder.

Things to test (Paul version)
1) put an invalid command and then afterwards exit without args. The exit code must be 127.
2) do "echo << eof | ls | ls > output.txt" but when being in the herdoc input just press control-C. The other commands must not be executed and the file is not allowed to be existing.
3) start the minishell with the command "env -i ./minishell". It should not crash.
4) when being in the minishell do "unset PATH" and then execute ls.
5) check for leaks with valgrind (also in child processes and for open fds).
