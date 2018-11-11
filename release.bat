copy /Y /B Debug\ddraw.dll ddraw.dll
7z u -y Output/DDrawDebug.7z ddraw.dll
copy /Y /B Release\ddraw.dll ddraw.dll
7z u -y Output/DDrawRelease.7z ddraw.dll
del ddraw.dll

7z u -y Output/DDrawSource.7z add_on *.cpp *.h ddwrapper.def ddwrapper.sln ddwrapper.vcxproj ddwrapper.vcxproj.filters detours.lib release.bat
