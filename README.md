## To-Do List

To-Do Lists can help you get and stay on top of important projects and piles of tasks or decisions.

To-Do List is an interactive console program that allows users to organize the tasks on their to-do list in one easy to use application. Users are able to do simple actions like add, remove, and complete tasks. They can also undo and redo their actions, and save their tasks to a file in order to load them during subsequent application launches.

To compile and execute the code, you must first reside in the directory that source code files are in. Once you are in the correct directory, run the code by typing the following command at the terminal prompt:

```
$ make
$ ./ToDoList
```

## Functionality

**To_Do List application accepts the following set of commands:**

1.	`ADD` - This command creates a new task. All newly created tasks are considered incomplete to start. The user specifies the task’s type, deadline, and description. If a specialized task requires additional information, the user provides that as well. In this application, it is assumed that a task’s deadline is an integer representing the number of days into the future when the task is due and  that an event’s time is a string.

2.  `PRINT` - This command displays all of the incomplete tasks in order of deadline. If multiple tasks are due the same number of days into the future, they are displayed in alphabetical order of description. Each task is printed on its own line, beginning with its position in the overall list, followed by its deadline, type, and description. If there are no incomplete tasks, it is indicated to the user.

3. `COMPLETE` - This command marks a specific incomplete task as complete. The user specifies the task number to mark as complete, as that task appears in the lists of the PRINT/DETAILED commands. If there are no incomplete tasks, it is indicated to the user.

4.  `COMPLETED` - This command displays all of the completed tasks. It follows the same format as the PRINT command. If there are no completed tasks, it is indicated to the user.

5.  `UNDO` - This command undoes the last ADD, REMOVE, or COMPLETE action. The user can undo actions multiple times, so long as there are actions left to undo. If there is nothing left to undo, it is indicated to the user.

6.  `REDO` -  This command redoes an action that was previously undone. If an action is undone, but then the user subsequently performs an ADD/COMPLETE/REMOVE action, the user will no longer be able to redo the undone action. If there is nothing to redo, it is indicated to the user.

7.  `SAVE` -  This command saves all of the incomplete tasks to a file. The user specifies the name of the file to create. If a file with that name already exists, application overwrite it.
example:
            ```
            > ./my_tasks.data
            ```
8.  `LOAD` - This command loads all of the tasks from a file as incomplete tasks.

9.  `EXIT` - This command will exit the program.

10. `HELP` - This command displays all of the available commands and their descriptions.
