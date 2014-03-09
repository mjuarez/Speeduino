#!/usr/bin/env python
"""
    BTC Guild Hashrate Example Script

    Gathers the total hashrate among workers, adds it up and sets
    the speedometer accordingly.

    Author:     Mike Juarez
    License:    Creative Commons Attribution-ShareAlike 3.0 United States License
    Date:       March 8, 2014
    Contact:    http://github.com/mjuarez

"""

import serial
import struct
import argparse
import requests
import time
import json

parser = argparse.ArgumentParser(
    description='Program to send current hashrate '
                'to Arduino speedometer gauge.')
parser.add_argument('--apikey', help="BTC Guild API Key", required=True)
parser.add_argument('-f', help="Arduino serial port", required=True)
args = parser.parse_args()
apikey = args.apikey
serialport = args.f

ser = serial.Serial(serialport, 9600, dsrdtr=False)
print "Initializing connection to %s" % ser.port
time.sleep(2)


def writeToGauge(val):
    """Write a value to the gauge"""
    ser.write(chr(val))


def getCurrentHashRate():
    """Return the current hash rate total of all your workers"""
    hash_rate = 0.0
    fetchurl = "https://www.btcguild.com/api.php?api_key=%s" % apikey
    print "Grabbing data from: %s" % fetchurl
    r = requests.get(fetchurl)
    if r.status_code == 200:
        try:
            jsondata = r.json()
        except ValueError:
            if r.text == "You have made too many API requests recently." \
                    "  API calls are limited to once every 15 seconds.":
                print "Polled API too fast."
                time.sleep(30)
                return hash_rate
            else:
                print r.text
                return hash_rate
        keys = jsondata['workers'].keys()
        for k in keys:
            hash_rate = hash_rate + float(jsondata['workers'][k]['hash_rate'])

    return hash_rate

while True:
    hashrate = getCurrentHashRate()
    writeToGauge(int(hashrate * 0.001))
    print "Current reported hashrate: " + str(hashrate)
    time.sleep(20)
