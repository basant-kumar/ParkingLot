# ParkingLot System
This project implements a fully automatic parking lot system which will keep track of the cars parked inside and give the parking ticket to the car driver. The system is opitmized in such way that car driver gets the empty slot which nearest to the entry point to park the car. 

---
## Requirements
- GCC compiler : version 8.1.0 
- To install in Ubuntu, run $sudo apt install g++ or $sudo apt install build-essential
- To isntall in Mac, follow this link, http://www-scf.usc.edu/~csci104/20142/installation/gccmac.html

## How to run the program

- ### Ubuntu/Mac
    step-1 : open terminal
    step-2 : clone or copy the program folder and navigate the terminal to that folder
    step-3 : copy your custom input file into program folder or edit the existing input.txt file
    step-4 : To run execute this command $g++ ParkingLot.cpp -o output 
    step-5 : $./output.exe input.txt  (here input.txt should your custom input file or already existing input file in the folder)
    step-6 : you will the output of the given input file in the ternimal



## Some assumption for this system

1) Parking lot has only one floor (though, can be changed to multi floor parking lot)
2) all cars of the same size and slots in the parking lot also of the same size
3) each car has unique registration number and has a unique driver
4) we will proceed to next command if the current given command is invalid