# f12021 UDP telemetry to CSV file.

I will be adding some more instructions shortly

# Basics

## Setup UDP

I have included F1 2021 UDP Guide in the docs dir, there are instructions in there.
Search for "How do I enable the UDP Telemetry Output?".

## build

```
mkdir build
cd build
cmake ..
make
sudo make install
```

## run

```
risf1 [port number]
```

if there is no port number defaults to 20777.

After every lap a CSV file of the lap telemetry is produced (lap1.csv lap2.csv etc). 

I use plotjuggler (https://github.com/facontidavide/PlotJuggler) to plot the telemetry using distance as the x axis.

