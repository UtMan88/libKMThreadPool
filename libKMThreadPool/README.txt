Keith M.'s C++ Win32 Thread pool lib.

-Compile Library File----------------------------------------
Everything is already set up to compile the library file.
All you need to do is include the project into your solution,
and compile! The project is set up to output the library file
into the same directory as your solution.

-Including the project into your solution--------------------
A bit of a task, but nothing too hard.

1- Include the Threadpool project file into your solution.

2- Open up YOUR projects' properties.

3- Under C/C++>>General, in Additional Include Directories, 
   add in the path to the Threadpools' directory.

4- Under Linker>>Input, in Additional Dependencies, add 
   libKMThreadPool.lib

5- Exit Properties, right-click on your project in the 
   solution explorer, click Project Dependencies, and check 
   the libKMThreadPool checkbox.

6- That should be all you need!
-------------------------------------------------------------
-------------------------------------------------------------
-------------------------------------------------------------
-------------------------------------------------------------
-------------------------------------------------------------
-------------------------------------------------------------
-------------------------------------------------------------
-------------------------------------------------------------
-Change Log--------------------------------------------------
REVISION# - Description
000000001 - Threadpool turned into a library!