# Less-Infection-Room-System
- it's simulated version:  
tinkercad: https://www.tinkercad.com/things/ajbmeDHdkZA

## Slave
the slave board(s) is to cense(read) the temperatuer of the room and the distance 
tasks:  
-- read when reacive event  
-- send(write) the the data when request event
## Master Board
- it's continues loop of sending and reciving commands to request data of the temperature and distance  
-- then drive a motor depend on the temp plus leds to indicate the temp level  
-- also fire an alarm "peizo0o0o" if the distance is more than 2 meter 
