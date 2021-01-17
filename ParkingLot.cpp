#include<iostream>
#include<unordered_map>
#include<vector>
#include<set>
#include<fstream>
#include<sstream>

using namespace std;

class Driver{
    //string firstName;
    //string lastName;
    int age;
    //string licenseNumber;

    public:
    Driver(){

    }
    Driver(int age){
        this->age = age;
    }
    //getter for age
    int getAge(){
        return this->age;
    }
    //setter for age
    void setAge(int age){
        this->age = age;
    }
};

class Vehicle{
    string registrationPlateNumber;  //to store registration number of a vehicle

    public:

    string getRegistrationPlateNumber(){
        return this->registrationPlateNumber;
    }

    void setRegistrationPlateNumber(string regNumber){
        this->registrationPlateNumber = regNumber;
    }
};

class Car : public Vehicle{
    public:
    Car(){

    }
    Car(string registrationPlateNumber){
        setRegistrationPlateNumber(registrationPlateNumber);
    }

};

class ParkingLot{
    int numberOfSlots;
    unordered_map<int, Car> carMap;  //to store details of car for a slot number
    unordered_map<int, Driver> driverMap; //to store details of driver for a slot number
    
    //assuming there is only one entry and exit point
    //slots are numbered in accending order for parking lot, smaller numbers being near entry point
    /*
        10  9 <- slot numbers
        8   7
        6   5
        4   3
        2   1
           ^ 
          ||
    entry/exit point
    
    */
    set<int> availableSlots;  //to store the available slots and first element of SET is always the slot which is nearest to the entry point

    public:
    
    ParkingLot(){

    }
    ParkingLot(int slots){
        this->numberOfSlots = slots;
        cout<<"Created parking of "<<slots<<" slots."<<endl;
        
        for(int i=numberOfSlots; i>0; --i){
            this->availableSlots.insert(i);
        }
    }
    //getter for number of slots
    int getNumberOfSlots(){
        return this->numberOfSlots;
    }

    //setter for number of slots
    void setNumberOfSlots(int slots){
        this->numberOfSlots = slots;
    }  

    // check for slot's availability
    bool isSlotAvailable(){
        return this->availableSlots.size()==0 ? false : true;
    }

    //return an empty slot which is near to entry point
    int getEmptySlot(){
        if(!isSlotAvailable()){
            cout<<"Parking lot is full"<<endl;
            return -1;
        }
        int slot = *(this->availableSlots.begin());
        this->availableSlots.erase(slot);
        return slot;
    }

    //clear a slot after a car leaves
    void setEmptySlot(int slot){
        this->availableSlots.insert(slot);
    }

    //returns driver for the given slot
    Driver getDriverForSlot(int slot){
        return this->driverMap[slot];
    }
    
    void setDriverForSlot(int slot, Driver driver){
        this->driverMap[slot] = driver;        
    }

    void removeDriverFromSlot(int slot){
        this->driverMap.erase(slot);
    }

    Car getCarForSlot(int slot){
        return this->carMap[slot];
    }

    void setCarForSlot(int slot, Car car){
        this->carMap[slot] = car;        
    }

    void removeCarFromSlot(int slot){
        this->carMap.erase(slot);
        removeDriverFromSlot(slot);
    }

    unordered_map<int, Car> getCarMap(){
        return this->carMap;
    }

    unordered_map<int, Driver> getDriverMap(){
        return this->driverMap;
    }
};

class TicketService{

    public:
    TicketService(){

    }
    //park a car in the parking lot and give ticket to the driver
    void park(ParkingLot &pLot, Car car, Driver driver){
        if(!pLot.isSlotAvailable()){
            cout<<"Parking lot is full. Please comeback later! :)"<<endl;
            return;
        }
        int slot = pLot.getEmptySlot();
        pLot.setCarForSlot(slot, car);
        pLot.setDriverForSlot(slot, driver);
        cout<<"Car with vehicle registration number "<<car.getRegistrationPlateNumber()<<" has been parked at slot number "<<slot<<endl;
    }

    //remove car from the parking lot 
    void leave(ParkingLot &pLot, int slot){
        if(slot <= 0 || slot > pLot.getNumberOfSlots()){
            cout<<"Invalid slot number, please provide valid slot number"<<endl;
            return;
        }
        cout<<"Slot number "<<slot<<" vacated,"<<" the car with registration number "<< pLot.getCarForSlot(slot).getRegistrationPlateNumber()<<
                    " left the space, "<< "the driver of the car was of age "<< pLot.getDriverForSlot(slot).getAge()<<endl;

        pLot.setEmptySlot(slot);
        pLot.removeCarFromSlot(slot);
    }

    //print all the slot number of cars with given driver age
    void slotNumbersForDriverOfAge(ParkingLot &pLot, int age){
        bool flag=true;
        for(auto it : pLot.getDriverMap()){
            if(it.second.getAge() == age){
                cout<<it.first<<",";
                flag=false;
            }
        }
        if(flag){
            cout<<"null, No driver with age "<<age<<" found.";
        }
        cout<<endl;
    }

    //print the slot number of car with given registration number
    void slotNumberOfCarWithNumber(ParkingLot &pLot, string regNumber){

        for(auto it : pLot.getCarMap()){
            if(it.second.getRegistrationPlateNumber() == regNumber){
                cout<<it.first<<endl;
                return;
            }
        }
        //if there is no car with given registration number, print null
        cout<<"null, No Car with registration number "<<regNumber<<" found."<<endl;
    }

    //print all the vehicle registration number whose driver age is given age
    void vehicleRegistrationNumberForDriverOfAge(ParkingLot &pLot, int age){
        bool flag = true;

        for(auto it : pLot.getDriverMap()){
            if(it.second.getAge() == age){
                cout<<pLot.getCarForSlot(it.first).getRegistrationPlateNumber()<<", ";
                flag = false;
            }
        }
        if(flag){
            cout<<"null, No driver with age "<<age<<" found.";
        }cout<<endl;
    }

};

class CommandService{

    string inputFilename;

    public:
    ParkingLot pLot;
    TicketService ticket;

    CommandService(string inputFilename){
        this->inputFilename = inputFilename;
    }

    string getInputFilename(){
        return this->inputFilename;
    }

    void setInputFilename(string input){
        this->inputFilename = input;
    }

    void run(){
        string line;
        ifstream myFile(getInputFilename());

        if(myFile.is_open()){
            while(getline(myFile, line)){
                //cout<<"line: "<<line<<endl;
                if(!decodeCommand(line)){
                    cout<<"Received invalid command for the execuation, omiting command "<<line<<endl;
                }
            }
        }
        else{
            cout<<"Not able to open given file, \nNote: file should be in the same folder of the program. \n( or maybe check the filename once :D)"<<endl;
        }
    }

    bool decodeCommand(string line){
        istringstream ss(line);
        string word;
        ss >> word;

        if(word == "Create_parking_lot"){
            int slot;
            ss>>slot;
            //cout<<"slot: "<<slot<<endl;
            pLot = ParkingLot(slot);
        }
        else if(word == "Park"){
            string regNumber;
            string age1;
            int age;
            ss>>regNumber;
            ss>>age1;
            ss>>age;

            //cout<<"regnum: "<<regNumber<<" age: "<<age<<endl;
            Car car(regNumber);
            Driver driver(age);
            ticket.park(pLot, car, driver);
        }
        else if(word == "Leave"){
            int slot;
            ss>>slot;
            ticket.leave(pLot, slot);
        }
        else if(word == "Slot_numbers_for_driver_of_age"){
            int age;
            ss>>age;
            ticket.slotNumbersForDriverOfAge(pLot, age);
        }
        else if(word == "Slot_number_for_car_with_number"){
            string regNumber;
            ss>> regNumber;
            ticket.slotNumberOfCarWithNumber(pLot, regNumber);
        }
        else if(word == "Vehicle_registration_number_for_driver_of_age"){
            int age;
            ss>>age;
            ticket.vehicleRegistrationNumberForDriverOfAge(pLot, age);
        }
        else{
            //can't decode because given command is invalid
            return false;
        }
        return true;
    }

};





int main(int argc, char** argv){
    if(argc > 2){
        cout<<"Only one filename is required, received many input arguments, (e.g. ./output.exe input.txt) "<<endl;
        return 0;
    }

    if(argc != 2 ){
        cout<<"Please provide filename as well, (e.g. ./output.exe input.txt) "<<endl;
        return 0;
    }
    
    string inputFilename = argv[1];
    CommandService cmd(inputFilename);
    cmd.run();
    return 0;
}