# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.28

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "D:\jean-\Appli\CLion 2024.1\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "D:\jean-\Appli\CLion 2024.1\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/HiveGame.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HiveGame.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HiveGame.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HiveGame.dir/flags.make

CMakeFiles/HiveGame.dir/GameMaster.cpp.obj: CMakeFiles/HiveGame.dir/flags.make
CMakeFiles/HiveGame.dir/GameMaster.cpp.obj: CMakeFiles/HiveGame.dir/includes_CXX.rsp
CMakeFiles/HiveGame.dir/GameMaster.cpp.obj: C:/Users/jean-/Desktop/HiveGame_LO21/HiveGame/GameMaster.cpp
CMakeFiles/HiveGame.dir/GameMaster.cpp.obj: CMakeFiles/HiveGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HiveGame.dir/GameMaster.cpp.obj"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HiveGame.dir/GameMaster.cpp.obj -MF CMakeFiles\HiveGame.dir\GameMaster.cpp.obj.d -o CMakeFiles\HiveGame.dir\GameMaster.cpp.obj -c C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\GameMaster.cpp

CMakeFiles/HiveGame.dir/GameMaster.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HiveGame.dir/GameMaster.cpp.i"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\GameMaster.cpp > CMakeFiles\HiveGame.dir\GameMaster.cpp.i

CMakeFiles/HiveGame.dir/GameMaster.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HiveGame.dir/GameMaster.cpp.s"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\GameMaster.cpp -o CMakeFiles\HiveGame.dir\GameMaster.cpp.s

CMakeFiles/HiveGame.dir/Hexagon.cpp.obj: CMakeFiles/HiveGame.dir/flags.make
CMakeFiles/HiveGame.dir/Hexagon.cpp.obj: CMakeFiles/HiveGame.dir/includes_CXX.rsp
CMakeFiles/HiveGame.dir/Hexagon.cpp.obj: C:/Users/jean-/Desktop/HiveGame_LO21/HiveGame/Hexagon.cpp
CMakeFiles/HiveGame.dir/Hexagon.cpp.obj: CMakeFiles/HiveGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HiveGame.dir/Hexagon.cpp.obj"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HiveGame.dir/Hexagon.cpp.obj -MF CMakeFiles\HiveGame.dir\Hexagon.cpp.obj.d -o CMakeFiles\HiveGame.dir\Hexagon.cpp.obj -c C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\Hexagon.cpp

CMakeFiles/HiveGame.dir/Hexagon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HiveGame.dir/Hexagon.cpp.i"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\Hexagon.cpp > CMakeFiles\HiveGame.dir\Hexagon.cpp.i

CMakeFiles/HiveGame.dir/Hexagon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HiveGame.dir/Hexagon.cpp.s"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\Hexagon.cpp -o CMakeFiles\HiveGame.dir\Hexagon.cpp.s

CMakeFiles/HiveGame.dir/Insecte.cpp.obj: CMakeFiles/HiveGame.dir/flags.make
CMakeFiles/HiveGame.dir/Insecte.cpp.obj: CMakeFiles/HiveGame.dir/includes_CXX.rsp
CMakeFiles/HiveGame.dir/Insecte.cpp.obj: C:/Users/jean-/Desktop/HiveGame_LO21/HiveGame/Insecte.cpp
CMakeFiles/HiveGame.dir/Insecte.cpp.obj: CMakeFiles/HiveGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/HiveGame.dir/Insecte.cpp.obj"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HiveGame.dir/Insecte.cpp.obj -MF CMakeFiles\HiveGame.dir\Insecte.cpp.obj.d -o CMakeFiles\HiveGame.dir\Insecte.cpp.obj -c C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\Insecte.cpp

CMakeFiles/HiveGame.dir/Insecte.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HiveGame.dir/Insecte.cpp.i"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\Insecte.cpp > CMakeFiles\HiveGame.dir\Insecte.cpp.i

CMakeFiles/HiveGame.dir/Insecte.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HiveGame.dir/Insecte.cpp.s"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\Insecte.cpp -o CMakeFiles\HiveGame.dir\Insecte.cpp.s

CMakeFiles/HiveGame.dir/Joueur.cpp.obj: CMakeFiles/HiveGame.dir/flags.make
CMakeFiles/HiveGame.dir/Joueur.cpp.obj: CMakeFiles/HiveGame.dir/includes_CXX.rsp
CMakeFiles/HiveGame.dir/Joueur.cpp.obj: C:/Users/jean-/Desktop/HiveGame_LO21/HiveGame/Joueur.cpp
CMakeFiles/HiveGame.dir/Joueur.cpp.obj: CMakeFiles/HiveGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/HiveGame.dir/Joueur.cpp.obj"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HiveGame.dir/Joueur.cpp.obj -MF CMakeFiles\HiveGame.dir\Joueur.cpp.obj.d -o CMakeFiles\HiveGame.dir\Joueur.cpp.obj -c C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\Joueur.cpp

CMakeFiles/HiveGame.dir/Joueur.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HiveGame.dir/Joueur.cpp.i"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\Joueur.cpp > CMakeFiles\HiveGame.dir\Joueur.cpp.i

CMakeFiles/HiveGame.dir/Joueur.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HiveGame.dir/Joueur.cpp.s"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\Joueur.cpp -o CMakeFiles\HiveGame.dir\Joueur.cpp.s

CMakeFiles/HiveGame.dir/main.cpp.obj: CMakeFiles/HiveGame.dir/flags.make
CMakeFiles/HiveGame.dir/main.cpp.obj: CMakeFiles/HiveGame.dir/includes_CXX.rsp
CMakeFiles/HiveGame.dir/main.cpp.obj: C:/Users/jean-/Desktop/HiveGame_LO21/HiveGame/main.cpp
CMakeFiles/HiveGame.dir/main.cpp.obj: CMakeFiles/HiveGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/HiveGame.dir/main.cpp.obj"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HiveGame.dir/main.cpp.obj -MF CMakeFiles\HiveGame.dir\main.cpp.obj.d -o CMakeFiles\HiveGame.dir\main.cpp.obj -c C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\main.cpp

CMakeFiles/HiveGame.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HiveGame.dir/main.cpp.i"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\main.cpp > CMakeFiles\HiveGame.dir\main.cpp.i

CMakeFiles/HiveGame.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HiveGame.dir/main.cpp.s"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\main.cpp -o CMakeFiles\HiveGame.dir\main.cpp.s

CMakeFiles/HiveGame.dir/Plateau.cpp.obj: CMakeFiles/HiveGame.dir/flags.make
CMakeFiles/HiveGame.dir/Plateau.cpp.obj: CMakeFiles/HiveGame.dir/includes_CXX.rsp
CMakeFiles/HiveGame.dir/Plateau.cpp.obj: C:/Users/jean-/Desktop/HiveGame_LO21/HiveGame/Plateau.cpp
CMakeFiles/HiveGame.dir/Plateau.cpp.obj: CMakeFiles/HiveGame.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/HiveGame.dir/Plateau.cpp.obj"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HiveGame.dir/Plateau.cpp.obj -MF CMakeFiles\HiveGame.dir\Plateau.cpp.obj.d -o CMakeFiles\HiveGame.dir\Plateau.cpp.obj -c C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\Plateau.cpp

CMakeFiles/HiveGame.dir/Plateau.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HiveGame.dir/Plateau.cpp.i"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\Plateau.cpp > CMakeFiles\HiveGame.dir\Plateau.cpp.i

CMakeFiles/HiveGame.dir/Plateau.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HiveGame.dir/Plateau.cpp.s"
	"D:\jean-\Appli\CLion 2024.1\bin\mingw\bin\g++.exe" $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\Plateau.cpp -o CMakeFiles\HiveGame.dir\Plateau.cpp.s

# Object files for target HiveGame
HiveGame_OBJECTS = \
"CMakeFiles/HiveGame.dir/GameMaster.cpp.obj" \
"CMakeFiles/HiveGame.dir/Hexagon.cpp.obj" \
"CMakeFiles/HiveGame.dir/Insecte.cpp.obj" \
"CMakeFiles/HiveGame.dir/Joueur.cpp.obj" \
"CMakeFiles/HiveGame.dir/main.cpp.obj" \
"CMakeFiles/HiveGame.dir/Plateau.cpp.obj"

# External object files for target HiveGame
HiveGame_EXTERNAL_OBJECTS =

HiveGame.exe: CMakeFiles/HiveGame.dir/GameMaster.cpp.obj
HiveGame.exe: CMakeFiles/HiveGame.dir/Hexagon.cpp.obj
HiveGame.exe: CMakeFiles/HiveGame.dir/Insecte.cpp.obj
HiveGame.exe: CMakeFiles/HiveGame.dir/Joueur.cpp.obj
HiveGame.exe: CMakeFiles/HiveGame.dir/main.cpp.obj
HiveGame.exe: CMakeFiles/HiveGame.dir/Plateau.cpp.obj
HiveGame.exe: CMakeFiles/HiveGame.dir/build.make
HiveGame.exe: CMakeFiles/HiveGame.dir/linkLibs.rsp
HiveGame.exe: CMakeFiles/HiveGame.dir/objects1.rsp
HiveGame.exe: CMakeFiles/HiveGame.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable HiveGame.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\HiveGame.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HiveGame.dir/build: HiveGame.exe
.PHONY : CMakeFiles/HiveGame.dir/build

CMakeFiles/HiveGame.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\HiveGame.dir\cmake_clean.cmake
.PHONY : CMakeFiles/HiveGame.dir/clean

CMakeFiles/HiveGame.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\cmake-build-debug C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\cmake-build-debug C:\Users\jean-\Desktop\HiveGame_LO21\HiveGame\cmake-build-debug\CMakeFiles\HiveGame.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/HiveGame.dir/depend
