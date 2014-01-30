Greetings,

This Xcode-based Arduino project has a few quirks worth mentioning:

* I use a FTDI-USB card to program Arduinos and clones. You’ll want to edit the makefile in the project and update the BOARD_PORT path for your preferred device.

* In Xcode, <command>-r to run does not work. Instead, use <command>-b (i.e. build) to compile and upload your code to the device. There are many build targets to choose from but I set the scheme to build the “Fast” target. For the rest YMMV.

* If you get a “Serial port not available” error the makefile may not be configured properly, or no USB device is connected.

Otherwise let the error messages guide you! If you run into insurmountable issues feel free to ping me: mooshx (at) gmail (dot) com
