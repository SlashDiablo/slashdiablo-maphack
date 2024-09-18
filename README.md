# slashdiablo-maphack

A customized maphack for reddit's slashdiablo D2 server

This maphack is based on BH maphack, written by McGod from the blizzhackers
forum. It was extensively customized for the slashdiablo realm by Deadlock39,
who created versions 0.1.1 and 0.1.2.

- [CHANGELOG](./CHANGELOG.md)
- [FEATURES](./FEATURES.md)

This is an attempt to merge everything again and fix the current mess:

## Current

- [x] https://github.com/BeLikeLeBron/slashdiablo-maphack (Lebron - called `beta` branch in the launcher) - **base source**
  - [x] reference branch (`main` is based on it, a copy is available in `launcher-beta`)
  - [ ] 3 pull requests are open here
  - forks of this that should be easy to merge:
    - [ ] https://github.com/dschu012/slashdiablo-maphack (Danny)
    - [ ] https://github.com/DoctorWoot420/slashdiablo-maphack (DrWoot)
- [ ] https://github.com/kr4d/slashdiablo-maphack (Hellords) - source 1
  - has features like kill counters, stormlib requirement removed, optimizations, etc
  - [ ] to be merged from (12 commits ahead currently)
- [x] https://github.com/SlashDiablo-II/SlashDiablo-Maphack (mir) - source 2
  - killed off
- [ ] https://github.com/planqi/slashdiablo-maphack (Planqi) - source 3
  - [ ] 3 PRs
  - [ ] 37 Issues
  - many unmerged things

## Unmaintained sources

Ancient lore at this point - ~~still need to collect issues~~ - nothing to collect or tracked in one of the repos from the previous section.

- [x] https://github.com/arolds/slashdiablo-maphack (arolds) - 2021
- [x] https://github.com/planqi/slashdiablo-maphack (planqi) - 2020
- [x] https://github.com/youbetterdont/slashdiablo-maphack (m81) - 2020
- [x] https://github.com/slayergod13/slashdiablo-maphack (slayergod13) - 2018
- [x] https://github.com/underbent/slashdiablo-maphack (Underbent) - 2015


# Building

To build with CMake, first install "Visual Studio Build Tools 2017" and a version of CMake>=3.7. Visual Studio Build Tools comes with a "Developer Command Prompt" that sets up the path with the right compilers and build tools. Next, create a build directory within the project root directory and make it the current working directory. Then, run the command `cmake -G"Visual Studio 15 2017" -DBUILD_SHARED_LIBS=TRUE -DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE ..` (save this command as a bat script if you like). This will create all necessary build files. Next, run `cmake --build . --config Release` to build the project.

To enable multi-processor support when buildling, set the CXXFLAGS environment variable with `set CXXFLAGS=/MP` prior to running the cmake command above.
