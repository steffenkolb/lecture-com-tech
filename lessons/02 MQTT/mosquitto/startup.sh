#!/bin/bash
docker run -it --name mqtt-broker -p 1883:1883 -p 9001:9001 eclipse-mosquitto