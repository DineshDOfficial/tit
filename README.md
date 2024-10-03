# Storium

A modular, reconfigurable data platform.

## Features

- Multi-Paradigm Data Storage
- Dynamic Storage Model Reconfiguration
...

gcc -I/mingw64/include -L/mingw64/lib -o storium src/main.c src/core/kvstore.c src/api/rest_api.c src/ui/web_interface.c -lmicrohttpd

gcc -IC:/msys64/mingw64/include -LC:/msys64/mingw64/lib -o storium src/main.c src/core/kvstore.c src/api/rest_api.c src/ui/web_interface.c -lmicrohttpd

gcc -IC:/msys64/mingw64/include -I./src/core -LC:/msys64/mingw64/lib -o storium src/main.c src/core/kvstore.c src/api/rest_api.c src/ui/web_interface.c -lmicrohttpd

gcc -IC:/msys64/mingw64/include -I./src/core -LC:/msys64/mingw64/lib -o storium src/main.c src/core/kvstore.c src/api/rest_api.c src/ui/web_interface.c -lmicrohttpd

gcc -I/mingw64/include -I./src/core -L/mingw64/lib -o storium src/main.c src/core/kvstore.c src/api/rest_api.c src/ui/web_interface.c -lmicrohttpd
