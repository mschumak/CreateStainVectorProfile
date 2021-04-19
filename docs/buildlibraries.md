<h1 align="center">Build the Plugin</h1>

## Requirements

The following instructions were tested with version v5.5.0.20200610 of Sedeen and the Sedeen SDK. 
Visual Studio 2017 only. , CMake 3.13 or newer.
It's built with VS2017. Do not get a more recent one.


## Building Libraries and Dependencies

The CreateStainVectorProfile plugin depends on libraries that must be built 
before attempting to build the plugin. The installation order presented here 
is required to build the dependencies for the MLPACK library.


### Boost

It is important to build based on compatible dependencies. To ensure compatibility, use an older version of [Boost](https://www.boost.org/). Using 1.69.0.
[Boost 1.69.0](https://dl.bintray.com/boostorg/release/1.69.0/source/boost_1_69_0.zip)

Put zip in desired directory, for instance c:\libraries\Boost
Extract all into c:\libraries\Boost
Open Command Prompt as Administrator (git bash or other Unix-style emulators will not work)
Change to directory c:\libraries\Boost\boost_1_69_0
Enter commands:
bootstrap
Once that finishes, enter command
.\b2
Wait for Boost to compile


### LAPACK and BLAS

Install Git for Windows and git bash. Get CMake. Get Visual Studio 2017.

Instructions to build LAPACK on Windows can be found at
http://icl.cs.utk.edu/lapack-for-windows/lapack/
under the heading "Build Instructions to create LAPACK and LAPACKE 3.5.0 dlls for Windows with MinGW"

MinGW
-----
Install MinGW to get a Fortran compiler.
Go to https://sourceforge.net/projects/mingw-w64/
Click the Files tab, and find the line:
MinGW-W64 Online Installer
    MinGW-W64-install.exe
Save the online installer, and run the .exe file.

Choose your configuration:
Version 8.1.0
Acrhitecture x86_64
Threads win32
Exception seh
Build revision 0

Set installation directory. The default will be 
C:\Program Files\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0
Click Next to install.
Add the bin directory to the PATH environment variable.
Open Settings, click on System, click on About, on RHS, click on Advanced System Settings, click on Environment Variables..., click on Path, click the Edit... button, click the New button.
Add the MinGW bin directory to the new line in the list of directories in the Path variable:
C:\Program Files\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0\mingw64\bin
Click Ok, Ok, Ok.


LAPACK
------
Go to netlib.org/LAPACK to get LAPACK
Under the heading "Previous Release", click on LAPACK, version 3.8.0
Download lapack-3.8.0.tar.gz
Copy to C:\libraries\LAPACK
Open git bash
Change to /c/libraries/LAPACK directory
enter command: tar xvzf lapack-3.8.0.tar.gz

Make a new directory C:/libraries/LAPACK/lapack-3.8.0-build
Open CMake
Choose C:/libraries/LAPACK/lapack-3.8.0 as the source code directory
Choose C:/libraries/LAPACK/lapack-3.8.0-build as the build directory
Click Configure
In the dropdown list under "Specify the generator for this project", choose MinGW Makefiles
Click the "Specify native compilers" button, and click Next
Choose the following compilers:
C: C:\Program Files\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0\mingw64\bin\gcc.exe
C++: C:\Program Files\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0\mingw64\bin\g++.exe
Fortran: C:\Program Files\mingw-w64\x86_64-8.1.0-win32-seh-rt_v6-rev0\mingw64\bin\gfortran.exe
Click Finish

In the variable list, make sure that CMAKE_BUILD_TYPE is set to Release
Check BUILD_SHARED_LIBS
Check CMAKE_GNUtoMS
Click Configure again.
Check the Advanced box to see additional variables.
Set the CMAKE_SHARED_LINKER_FLAGS value to be the following text exactly as shown with no spaces:
-Wl,--allow-multiple-definition
(single dash before Wl, double dash before allow-multiple-definition)
Warnings about CMake version compatibility may appear. These are acceptable.
Click Generate.
When Generating is done, open git bash and change to the /c/libraries/LAPACK/lapack-3.8.0-build directory.
Type mingw32-make, hit enter
Let it build!


Armadillo
---------
Go to http://arma.sourceforge.net/
Click the Download tab
Click to download a stable version. This plugin was last tested and working with armadillo-10.4.0.tar.xz
Copy to C:\libraries\Armadillo
Open git bash
Change to /c/libraries/Armadillo directory
enter command: tar xvf armadillo-10.4.0.tar.xz
Make a new directory C:/libraries/Armadillo/armadillo-10.4.0-build
Make a new directory C:/libraries/Armadillo/armadillo-10.4.0-release
Open CMake
Choose C:/libraries/Armadillo/armadillo-10.4.0 as the source code directory
Choose C:/libraries/Armadillo/armadillo-10.4.0-build as the build directory
Click Configure
In the dropdown list under "Specify the generator for this project", choose Visual Studio 15 2017
Ensure the "Use default native compilers" option is selected, and click Finish
Change CMAKE_INSTALL_PREFIX to C:/libraries/Armadillo/armadillo-10.4.0-release
Click Configure
Click Generate
Open Visual Studio 2017, and open C:\libraries\Armadillo\armadillo-10.4.0-build\armadillo.sln
Change the configuration to Release
From the Build menu, select Build ALL_BUILD
In the Solution Explorer, click INSTALL
From the Build menu, select Build INSTALL
Close the solution and/or Visual Studio


ensmallen
---------
Go to https://ensmallen.org/
Click to download a stable version. This plugin was last tested and working with ensmallen-2.16.2.tar.gz
Copy to C:\libraries\ensmallen
Open git bash
Change to /c/libraries/ensmallen directory
enter command: tar xvzf ensmallen-2.16.2.tar.gz
Make a new directory C:\libraries\ensmallen\ensmallen-2.16.2-build
Make a new directory C:\libraries\ensmallen\ensmallen-2.16.2-release
Open CMake
Choose C:/libraries/ensmallen\ensmallen-2.16.2 as the source code directory
Choose C:/libraries/ensmallen\ensmallen-2.16.2-build as the build directory
Click Configure
In the dropdown list under "Specify the generator for this project", choose Visual Studio 15 2017
Ensure the "Use default native compilers" option is selected, and click Finish
Change CMAKE_INSTALL_PREFIX to C:/libraries/ensmallen\ensmallen-2.16.2-release
Set ARMADILLO_INCLUDE_DIR to the location of the Armadillo include directory. If the instructions above were followed, this location is C:/libraries/Armadillo/armadillo-10.4.0-release/include
Click Configure again
Set ARMADILLO_LIBRARY to the armadillo.lib file. If the instructions above were followed, the full path for this file is C:/libraries/Armadillo/armadillo-10.4.0-release/lib/armadillo.lib
Check the box for USE_OPENMP
Click Configure again
Click Generate
Open Visual Studio 2017, and open C:\libraries\ensmallen\ensmallen-2.16.2-build\ensmallen.sln
Change the configuration to Release
From the Build menu, select Build ALL_BUILD
In the Solution Explorer, click INSTALL
From the Build menu, select Build INSTALL
Close the solution and/or Visual Studio


MLPACK
------
Go to https://www.mlpack.org/
Click Download mlpack to get a stable version. This plugin was last tested and working with mlpack-3.4.2.tar.gz
Copy to C:\libraries\mlpack
Open git bash
Change to /c/libraries/mlpack directory
enter command: tar xvzf mlpack-3.4.2.tar.gz
Make a new directory C:\libraries\mlpack\mlpack-3.4.2-build
Make a new directory C:\libraries\mlpack\mlpack-3.4.2-release
Open CMake
Choose C:/libraries/mlpack\mlpack-3.4.2 as the source code directory
Choose C:/libraries/mlpack\mlpack-3.4.2-build as the build directory
Click Configure
In the dropdown list under "Specify the generator for this project", choose Visual Studio 15 2017
Ensure the "Use default native compilers" option is selected, and click Finish
Check the box for Advanced to show additional variables.

Set ARMADILLO_INCLUDE_DIR to the location of the Armadillo include directory. If the instructions above were followed, this location is C:/libraries/Armadillo/armadillo-10.4.0-release/include
Uncheck the box for BUILD_CLI_EXECUTABLES
Uncheck the box for BUILD_GO_BINDINGS
Uncheck the box for BUILD_JULIA_BINDINGS
Uncheck the box for BUILD_PYTHON_BINDINGS
Uncheck the box for BUILD_R_BINDINGS
Uncheck the box for BUILD_TESTS
Change CMAKE_INSTALL_PREFIX to C:/libraries/mlpack\mlpack-3.4.2-release
Uncheck the box for DOWNLOAD_ENSMALLEN 
Click Configure
Set ARMADILLO_LIBRARY to the armadillo.lib file. If the instructions above were followed, the full path for this file is C:/libraries/Armadillo/armadillo-10.4.0-release/lib/armadillo.lib
Set the ENSMALLEN_INCLUDE_DIR to the location of the ensmallen include directory. If the instructions above were followed, this location is C:/libraries/ensmallen/ensmallen-2.16.2-release/include
Click Configure

Set Boost_INCLUDE_DIR to the location of the Boost include directory. If the instructions above were followed, this location is c:\libraries\Boost\boost_1_69_0
Set Boost_SERIALIZATION_LIBRARY_DEBUG to C:/libraries/Boost/boost_1_69_0/stage/lib/libboost_serialization-vc141-mt-gd-x64-1_69.lib
Set Boost_SERIALIZATION_LIBRARY_RELEASE to C:/libraries/Boost/boost_1_69_0/stage/lib/libboost_serialization-vc141-mt-x64-1_69.lib
Set Boost_UNIT_TEST_FRAMEWORK_LIBRARY_DEBUG to C:/libraries/Boost/boost_1_69_0/stage/lib/libboost_unit_test_framework-vc141-mt-gd-x64-1_69.lib
Set Boost_UNIT_TEST_FRAMEWORK_LIBRARY_RELEASE to C:/libraries/Boost/boost_1_69_0/stage/lib/libboost_unit_test_framework-vc141-mt-x64-1_69.lib
Click Configure
The remaining CMake variables that are marked as NOTFOUND are optional. Bindings to Julia, Markdown, Python, Go, and R are also optional.
Click Generate
Open Visual Studio 2017, and open C:\libraries\mlpack\mlpack-3.4.2-build\mlpack.sln
Change the configuration to Release
From the Build menu, select Build ALL_BUILD
Let it build.
In the Solution Explorer, click INSTALL
From the Build menu, select Build INSTALL
Close the solution and/or Visual Studio







## Building the Plugin

After building the necessary libraries, get Sedeen, the Sedeen SDK.

### CMake

[TinyXML2](https://github.com/leethomason/tinyxml2.git)

[OpticalDensityThreshold](https://github.com/sedeen-piip-plugins/OpticalDensityThreshold.git)

[StainAnalysisplugin](https://github.com/sedeen-piip-plugins/StainAnalysis-plugin.git)


## Copyright & License

Copyright (c) 2021 Sunnybrook Research Institute

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.