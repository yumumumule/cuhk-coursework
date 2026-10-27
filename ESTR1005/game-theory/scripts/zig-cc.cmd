@echo off
rem Set ZIG_EXE to the full path of zig.exe before configuring CMake.
if not defined ZIG_EXE (
  echo Set ZIG_EXE to the full path of zig.exe. 1>&2
  exit /b 1
)
"%ZIG_EXE%" cc %*
