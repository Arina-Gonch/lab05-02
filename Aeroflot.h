#pragma once
#include <iostream> 
#include <string> 

class Aeroflot 
{
private: 
    std::string destination; 
    int flightNumber; 
    std::string aircraftType; 

public: 
    Aeroflot(); 
    Aeroflot(const std::string& destination, int flightNumber, const std::string& aircraftType); 
    Aeroflot(const Aeroflot& other); 
    ~Aeroflot(); 

    std::string getDestination() const; 
    int getFlightNumber() const; 
    std::string getAircraftType() const; 

    void setDestination(const std::string& value); 
    void setFlightNumber(int value); 
    void setAircraftType(const std::string& value); 

    Aeroflot& operator=(const Aeroflot& other); 

    friend std::ostream& operator<<(std::ostream& out, const Aeroflot& flight); 
    friend std::istream& operator>>(std::istream& in, Aeroflot& flight); 
}; 

class AeroflotManager 
{
private: 
    Aeroflot* flights;
    int count; 

    void sortFlights();

public: 
    AeroflotManager(); 
    AeroflotManager(const AeroflotManager& other); 
    ~AeroflotManager(); 

    AeroflotManager& operator=(const AeroflotManager& other); 
    Aeroflot& operator[](int index); 
    const Aeroflot& operator[](int index) const; 

    int getCount() const; 
    bool isEmpty() const; 

    void add(const Aeroflot& flight, int position); 
    void remove(int position); 
    void edit(int position, const Aeroflot& flight); 
    void findByDestination(const std::string& destination) const; 

    friend std::ostream& operator<<(std::ostream& out, const AeroflotManager& manager); 
}; 