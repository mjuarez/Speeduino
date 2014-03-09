# Speeduino

Speeduino is an Arduino controlled speedometer project. It's originally written to work with Speedhut speedometers but could probably be adapted to work with others.

## Getting Started
Please refer to [Speedhut's page](http://www.speedhut.com/instructions.i) for instructions on hooking up your speedometer. Instructions for connection your Arduino are available in the comment header of the sketch.

To use the Python example scripts, you'll need the following modules:
* [pyserial](http://pyserial.sourceforge.net/)
* [requests](http://docs.python-requests.org/en/latest/)

## Examples
#### btcguild.py
```btcguild.py
usage: btcguild.py [-h] --apikey APIKEY -f F

Program to send current hashrate to Arduino speedometer gauge.

optional arguments:
  -h, --help       show this help message and exit
  --apikey APIKEY  BTC Guild API Key
  -f F             Arduino serial port```

## Gotchas
Most of the Python scripts will attempt to disable DTR on serial communication in order to prevent the Arduino from resetting itself. Not all systems will support this. It is suggested to follow these instructions on disabling power reset on serial connectivity for your Arduino. (http://playground.arduino.cc/Main/DisablingAutoResetOnSerialConnection#.Uxv9hD5gaGI)
