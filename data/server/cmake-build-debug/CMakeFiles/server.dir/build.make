# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2019.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2019.2.3\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\dmazza\olinleap\data\server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\dmazza\olinleap\data\server\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles\server.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\server.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\server.dir\flags.make

CMakeFiles\server.dir\main.cpp.obj: CMakeFiles\server.dir\flags.make
CMakeFiles\server.dir\main.cpp.obj: ..\main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\dmazza\olinleap\data\server\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/main.cpp.obj"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1420~1.275\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\server.dir\main.cpp.obj /FdCMakeFiles\server.dir\ /FS -c C:\Users\dmazza\olinleap\data\server\main.cpp
<<

CMakeFiles\server.dir\main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/main.cpp.i"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1420~1.275\bin\Hostx86\x86\cl.exe > CMakeFiles\server.dir\main.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\dmazza\olinleap\data\server\main.cpp
<<

CMakeFiles\server.dir\main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/main.cpp.s"
	C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1420~1.275\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\server.dir\main.cpp.s /c C:\Users\dmazza\olinleap\data\server\main.cpp
<<

# Object files for target server
server_OBJECTS = \
"CMakeFiles\server.dir\main.cpp.obj"

# External object files for target server
server_EXTERNAL_OBJECTS =

server.exe: CMakeFiles\server.dir\main.cpp.obj
server.exe: CMakeFiles\server.dir\build.make
server.exe: CMakeFiles\server.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\dmazza\olinleap\data\server\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable server.exe"
	"C:\Program Files\JetBrains\CLion 2019.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\server.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100177~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100177~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MIB055~1\2019\COMMUN~1\VC\Tools\MSVC\1420~1.275\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\server.dir\objects1.rsp @<<
 /out:server.exe /implib:server.lib /pdb:C:\Users\dmazza\olinleap\data\server\cmake-build-debug\server.pdb /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\server.dir\build: server.exe

.PHONY : CMakeFiles\server.dir\build

CMakeFiles\server.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\server.dir\cmake_clean.cmake
.PHONY : CMakeFiles\server.dir\clean

CMakeFiles\server.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\Users\dmazza\olinleap\data\server C:\Users\dmazza\olinleap\data\server C:\Users\dmazza\olinleap\data\server\cmake-build-debug C:\Users\dmazza\olinleap\data\server\cmake-build-debug C:\Users\dmazza\olinleap\data\server\cmake-build-debug\CMakeFiles\server.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles\server.dir\depend

