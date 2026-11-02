#pragma once
#include <iostream> 
#include <string> 

class Reader 
{
private: 
    std::string fileName; 

public: 
    Reader(); 
    explicit Reader(const std::string& fileName); 
    Reader(const Reader& other); 
    ~Reader(); 

    std::string getFileName() const; 
    void setFileName(const std::string& value); 
    void processFile() const; 

    Reader& operator=(const Reader& other); 

    friend std::ostream& operator<<(std::ostream& out, const Reader& processor); 
}; 
