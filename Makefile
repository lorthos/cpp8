#cd appz/emsdk
#source ./emsdk_env.sh
wasm1:
	cd build;emcmake cmake -DCMAKE_BUILD_TYPE=Debug ..

wasm2:
	cd build;cmake --build . --parallel --config Debug

wasm3:
	cd build;python3 -m http.server 8000

run:
	cmake-build-debug/cpp8 ./roms/$(game)