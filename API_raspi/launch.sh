#!/bin/bash
make clean;
make;
sudo ip link set can0 up type can bitrate 360000 ;
./init


