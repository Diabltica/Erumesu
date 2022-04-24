cmake_minimum_required(VERSION 3.22)
project(Erumesu C)

set(CMAKE_C_STANDARD 99)

add_executable(Erumesu src/main.c src/Linux/linux_serial_sender.c src/Linux/linux_serial_sender.h src/windows/windows_serial_sender.c src/windows/windows_serial_sender.h)
