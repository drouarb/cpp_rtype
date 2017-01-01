[![rtype](http://web-vassets.ea.com/Assets/Richmedia/Image/FullImageLogo/fr_r-type-logo.png)](https://git.minewolf.tf/root/rtype)
=============================================

## Description

This is an multiplayer implementation of the game r-type.

## Installation
You can download an installer at this address http://minewolf.tf/down/rtype_setup.exe

## Build [![build status](http://git.minewolf.tf/root/rtype/badges/master/build.svg)](http://git.minewolf.tf/root/rtype/commits/master)

To build this project you need cmake and SFML and a compilation toolchain (gcc+make,mingw,visual studio...). To enable tests compilation you need to set `RTYPE_TESTS=ON`. All unit tests are written with ctest, to execute it run the command `ctest`.

## Protocol

This game is a multiplayer game, it use a client/server architecture. The protocol is defined in the [RFC here](https://epitechfr-my.sharepoint.com/personal/gregoire_guemas_epitech_eu/_layouts/15/guestaccess.aspx?guestaccesstoken=wfPbJSy621wO06dXqBQdVWWKdJl637QE%2fRHgbU71f2w%3d&docid=01fb57e007a8048f3a7750dc258d85670&rev=1).

## License

This program is distributed under [MIT License](https://git.minewolf.tf/root/rtype/blob/master/LICENSE).