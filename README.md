# F12021 UDP Telemetry to CSV File.

Command line tool for creating a CSV file of the drivers telemetry per lap using the F1 2021 UDP API.

The CSV files can be used in a plotter, for example [PlotJuggler](https://github.com/facontidavide/PlotJuggler)

For Example using [PlotJuggler](https://github.com/facontidavide/PlotJuggler)

## Table of Contents  
[Installation](#installation)   
[Usage](#usage)                      
[License](#license)                    

## <a name="installation"/>Installation

### For Linux and Mac users

```shell
mkdir build
cd build
cmake ..
make
sudo make install
```

### For windows

This is what I did to build on windows (I'm no expert on windows)

- Installed free version of visual studio
- Installed vscode
- Open the repo in vscode
- Installed the C++ intelliSense from microsoft
- Installed the CMake Tools plugin from microsoft
- VSCode had a pop-up to configure to use CMake, I clicked yes
- Then clicked the build button at the bottom of VSCode
- This then built the executables in ./build/Debug

## <a name="usage"/>Usage

I have included [F1 2021 UDP Guide](doc/Data_Output_from_F1_2021%2351.docx) in the docs dir, there is a section "How do I enable the UDP Telemetry Output?".

**NOTE** The CSV files are written to the same directory (folder) the executable is run from.

Open a terminal and run (Windows users may need to set the PATH environment variable to the executable (risf1))

```
risf1 [port number (Default 20777)]
```

For Example

```
risf1 20777
```

Then loadup the CSV file in you favorite Plotting software.

![Plotjuggler example](/images/tyresurfacetemp.png)

## <a name="license"/>License

ris-f12021 is licensed under the Apache License 2.0, which means that you are free to get and use it for commercial and non-commercial purposes as long as you fulfill its conditions.

See the [LICENSE](LICENSE) file for more details.
