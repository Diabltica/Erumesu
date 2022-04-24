cmake_minimum_required(VERSION 3.22)
project(Erumesu C)

set(CMAKE_C_STANDARD 99)

add_executable(Erumesu src/main.c src/linux_serial_sender.c src/linux_serial_sender.h src/windows_serial_sender.c src/windows_serial_sender.h)
