# Baja-Datalogging

Created by Kaelan Strones 

This project is created to collect three axis of acceleration along with two axis of angles on the ASU Polytechnic Baja car. 

The current workings and most stable release only print out the raw acceleromet values onto an SD card. Raw gyro values can be printed but is not useful until we have fixed the problem with gyro drift. 

We are currently working on getting angles of the car also printed to the spreadsheet. My first setup was utilizing the gyro's angular rate to calculate the current angle but the gyro drifts a lot and would get worse on a vibrating car. My next option is to utilize the accelerometer alone or with the gyro to get an angle. 

This project also contains a project for strain gauge datalogging. This portion of code is untested and parts are still needed before tests can be run. 

The components utilized in the project 
  IMU
   1. Arduino Uno
   2. Adafruit 10DOF 
   3. Adafruit Wifi Shield
   
  Strain Gauge System
   1. Arduino Mega
   2. Adafruit Wifi Shield
   3. Adafruit ADS1115 4 channel ADC converter
   4. Custom built gauge bridge PCB
 

Future projects
 1. strain gauge datalogging 
 2. thermal datalogging
