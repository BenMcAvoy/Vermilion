# Vermilion

Vermilion is a Windows C++ reverse-engineering research project focused on Unreal Engine data structures and rendering. It contains game-specific object abstractions, a Dear ImGui overlay that draws skeletal relationships, and separate driver and driver-testbench projects.

## Build

Open `Vermilion.sln` in Visual Studio. The driver project requires the Windows Driver Kit; the user-mode projects use vcpkg manifest dependencies.

## Status

This is an experimental, game-build-specific project. The structures and offsets are not a stable Unreal Engine SDK, and the repository is not a general-purpose overlay framework.
