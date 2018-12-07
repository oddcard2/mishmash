Gtest build
Windows
1. Download https://github.com/abseil/googletest/archive/release-1.8.1.zip
2. Unpack it into the directory where the README.txt file is located, so you will have new googletest-release-1.8.1 directory
3. Download cmake if you don't have it (need at least CMake 3.7 for Visual Studio 2017)
	Go to https://cmake.org/download/
	Download Windows win64-x64 ZIP of latest version
	Unpack somewhere
4. Add cmake bin directory to PATH, for example G:\Progs\cmake-3.13.1-win64-x64\bin
5. Open console
6. cd googletest-release-1.8.1\googletest
7. mkdir build
8. cmake -G "Visual Studio 15 2017 Win64" ..
9. Open solution googletest-release-1.8.1\googletest\build\gtest.sln
10. Build soluition

