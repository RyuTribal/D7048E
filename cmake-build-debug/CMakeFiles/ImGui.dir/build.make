# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2023.3.3\bin\cmake\win\x64\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2023.3.3\bin\cmake\win\x64\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Programming\D7048E

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Programming\D7048E\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/ImGui.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ImGui.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ImGui.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ImGui.dir/flags.make

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui.cpp.obj: CMakeFiles/ImGui.dir/flags.make
CMakeFiles/ImGui.dir/App/vendor/imgui/imgui.cpp.obj: C:/Programming/D7048E/App/vendor/imgui/imgui.cpp
CMakeFiles/ImGui.dir/App/vendor/imgui/imgui.cpp.obj: CMakeFiles/ImGui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Programming\D7048E\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ImGui.dir/App/vendor/imgui/imgui.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ImGui.dir/App/vendor/imgui/imgui.cpp.obj -MF CMakeFiles\ImGui.dir\App\vendor\imgui\imgui.cpp.obj.d -o CMakeFiles\ImGui.dir\App\vendor\imgui\imgui.cpp.obj -c C:\Programming\D7048E\App\vendor\imgui\imgui.cpp

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ImGui.dir/App/vendor/imgui/imgui.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Programming\D7048E\App\vendor\imgui\imgui.cpp > CMakeFiles\ImGui.dir\App\vendor\imgui\imgui.cpp.i

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ImGui.dir/App/vendor/imgui/imgui.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Programming\D7048E\App\vendor\imgui\imgui.cpp -o CMakeFiles\ImGui.dir\App\vendor\imgui\imgui.cpp.s

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_demo.cpp.obj: CMakeFiles/ImGui.dir/flags.make
CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_demo.cpp.obj: C:/Programming/D7048E/App/vendor/imgui/imgui_demo.cpp
CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_demo.cpp.obj: CMakeFiles/ImGui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Programming\D7048E\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_demo.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_demo.cpp.obj -MF CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_demo.cpp.obj.d -o CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_demo.cpp.obj -c C:\Programming\D7048E\App\vendor\imgui\imgui_demo.cpp

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_demo.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Programming\D7048E\App\vendor\imgui\imgui_demo.cpp > CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_demo.cpp.i

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_demo.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Programming\D7048E\App\vendor\imgui\imgui_demo.cpp -o CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_demo.cpp.s

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_draw.cpp.obj: CMakeFiles/ImGui.dir/flags.make
CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_draw.cpp.obj: C:/Programming/D7048E/App/vendor/imgui/imgui_draw.cpp
CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_draw.cpp.obj: CMakeFiles/ImGui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Programming\D7048E\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_draw.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_draw.cpp.obj -MF CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_draw.cpp.obj.d -o CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_draw.cpp.obj -c C:\Programming\D7048E\App\vendor\imgui\imgui_draw.cpp

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_draw.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Programming\D7048E\App\vendor\imgui\imgui_draw.cpp > CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_draw.cpp.i

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_draw.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Programming\D7048E\App\vendor\imgui\imgui_draw.cpp -o CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_draw.cpp.s

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_tables.cpp.obj: CMakeFiles/ImGui.dir/flags.make
CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_tables.cpp.obj: C:/Programming/D7048E/App/vendor/imgui/imgui_tables.cpp
CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_tables.cpp.obj: CMakeFiles/ImGui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Programming\D7048E\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_tables.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_tables.cpp.obj -MF CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_tables.cpp.obj.d -o CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_tables.cpp.obj -c C:\Programming\D7048E\App\vendor\imgui\imgui_tables.cpp

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_tables.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Programming\D7048E\App\vendor\imgui\imgui_tables.cpp > CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_tables.cpp.i

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_tables.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Programming\D7048E\App\vendor\imgui\imgui_tables.cpp -o CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_tables.cpp.s

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_widgets.cpp.obj: CMakeFiles/ImGui.dir/flags.make
CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_widgets.cpp.obj: C:/Programming/D7048E/App/vendor/imgui/imgui_widgets.cpp
CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_widgets.cpp.obj: CMakeFiles/ImGui.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Programming\D7048E\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_widgets.cpp.obj"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_widgets.cpp.obj -MF CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_widgets.cpp.obj.d -o CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_widgets.cpp.obj -c C:\Programming\D7048E\App\vendor\imgui\imgui_widgets.cpp

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_widgets.cpp.i"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Programming\D7048E\App\vendor\imgui\imgui_widgets.cpp > CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_widgets.cpp.i

CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_widgets.cpp.s"
	C:\PROGRA~1\JETBRA~1\CLION2~1.3\bin\mingw\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Programming\D7048E\App\vendor\imgui\imgui_widgets.cpp -o CMakeFiles\ImGui.dir\App\vendor\imgui\imgui_widgets.cpp.s

# Object files for target ImGui
ImGui_OBJECTS = \
"CMakeFiles/ImGui.dir/App/vendor/imgui/imgui.cpp.obj" \
"CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_demo.cpp.obj" \
"CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_draw.cpp.obj" \
"CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_tables.cpp.obj" \
"CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_widgets.cpp.obj"

# External object files for target ImGui
ImGui_EXTERNAL_OBJECTS =

C:/Programming/D7048E/App/vendor/imgui/bin/Debug-windows-x86_64/ImGui/libImGui.a: CMakeFiles/ImGui.dir/App/vendor/imgui/imgui.cpp.obj
C:/Programming/D7048E/App/vendor/imgui/bin/Debug-windows-x86_64/ImGui/libImGui.a: CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_demo.cpp.obj
C:/Programming/D7048E/App/vendor/imgui/bin/Debug-windows-x86_64/ImGui/libImGui.a: CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_draw.cpp.obj
C:/Programming/D7048E/App/vendor/imgui/bin/Debug-windows-x86_64/ImGui/libImGui.a: CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_tables.cpp.obj
C:/Programming/D7048E/App/vendor/imgui/bin/Debug-windows-x86_64/ImGui/libImGui.a: CMakeFiles/ImGui.dir/App/vendor/imgui/imgui_widgets.cpp.obj
C:/Programming/D7048E/App/vendor/imgui/bin/Debug-windows-x86_64/ImGui/libImGui.a: CMakeFiles/ImGui.dir/build.make
C:/Programming/D7048E/App/vendor/imgui/bin/Debug-windows-x86_64/ImGui/libImGui.a: CMakeFiles/ImGui.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Programming\D7048E\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library C:\Programming\D7048E\App\vendor\imgui\bin\Debug-windows-x86_64\ImGui\libImGui.a"
	$(CMAKE_COMMAND) -P CMakeFiles\ImGui.dir\cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\ImGui.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ImGui.dir/build: C:/Programming/D7048E/App/vendor/imgui/bin/Debug-windows-x86_64/ImGui/libImGui.a
.PHONY : CMakeFiles/ImGui.dir/build

CMakeFiles/ImGui.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\ImGui.dir\cmake_clean.cmake
.PHONY : CMakeFiles/ImGui.dir/clean

CMakeFiles/ImGui.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Programming\D7048E C:\Programming\D7048E C:\Programming\D7048E\cmake-build-debug C:\Programming\D7048E\cmake-build-debug C:\Programming\D7048E\cmake-build-debug\CMakeFiles\ImGui.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/ImGui.dir/depend
