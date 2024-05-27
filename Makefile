run-debug: shared-debug
	cd build/msys && ./QtApp.exe

run-release: shared-release
	cd build/msys && ./deploy/QtApp.exe

run-static-release: static-release
	cd build/mvsc/Release && ./QtApp.exe

shared-debug:
	cd build/msys && cmake --build . --config Debug

shared-release:
	cd build/msys && cmake --build . --config Release

static-release:
	cd build/mvsc && cmake --build . --config Release