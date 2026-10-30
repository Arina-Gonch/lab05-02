#include "Aeroflot.h" 
#include <stdexcept> 
#include <limits> 


Aeroflot::Aeroflot() : destination("Не указан"), flightNumber(0), aircraftType("Не указан") 
{
    std::cout << "[Конструктор Aeroflot] Создан пустой объект рейса.\n"; 
}


Aeroflot::Aeroflot(const std::string& destination, int flightNumber, const std::string& aircraftType) : destination(destination), flightNumber(flightNumber), aircraftType(aircraftType) 
{
    if (destination.empty()) throw std::invalid_argument("Пункт назначения не может быть пустым."); 
    if (flightNumber <= 0) throw std::invalid_argument("Номер рейса должен быть положительным числом."); 
    if (aircraftType.empty()) throw std::invalid_argument("Тип самолёта не может быть пустым."); 
    std::cout << "[Конструктор Aeroflot с параметрами] Создан рейс №" << flightNumber << ".\n"; 
}


Aeroflot::Aeroflot(const Aeroflot& other) : destination(other.destination), flightNumber(other.flightNumber), aircraftType(other.aircraftType) 
{
    std::cout << "[Конструктор копирования Aeroflot] Скопирован рейс №" << flightNumber << ".\n"; 
}


Aeroflot::~Aeroflot() 
{
    std::cout << "[Деструктор Aeroflot] Уничтожен объект рейса №" << flightNumber << ".\n"; 
}


std::string Aeroflot::getDestination() const 
{
    return destination; 
}


int Aeroflot::getFlightNumber() const 
{
    return flightNumber; 
}


std::string Aeroflot::getAircraftType() const 
{
    return aircraftType; 
}


void Aeroflot::setDestination(const std::string& value) 
{
    if (value.empty()) throw std::invalid_argument("Пункт назначения не может быть пустым."); 
    destination = value; 
}


void Aeroflot::setFlightNumber(int value) 
{
    if (value <= 0) throw std::invalid_argument("Номер рейса должен быть положительным числом."); 
    flightNumber = value; 
}


void Aeroflot::setAircraftType(const std::string& value) 
{
    if (value.empty()) throw std::invalid_argument("Тип самолёта не может быть пустым."); 
    aircraftType = value; 
}


Aeroflot& Aeroflot::operator=(const Aeroflot& other) 
{
    if (this != &other) 
    {
        destination = other.destination; 
        flightNumber = other.flightNumber; 
        aircraftType = other.aircraftType; 
        std::cout << "[Оператор присваивания Aeroflot] Скопированы данные рейса №" << flightNumber << ".\n"; 
    }
    return *this; 
}

std::ostream& operator<<(std::ostream& out, const Aeroflot& flight) 
{
    out << "Пункт назначения: " << flight.destination << '\n'; 
    out << "Номер рейса: " << flight.flightNumber << '\n'; 
    out << "Тип самолёта: " << flight.aircraftType << '\n'; 
    return out; 
}


std::istream& operator>>(std::istream& in, Aeroflot& flight) 
{
    std::string destination; 
    std::string aircraftType; 
    int flightNumber = 0; 

    if (!std::getline(in >> std::ws, destination)) return in; 
    if (!(in >> flightNumber)) return in; 
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    if (!std::getline(in >> std::ws, aircraftType)) return in; 

    try 
    {
        flight.setDestination(destination); 
        flight.setFlightNumber(flightNumber); 
        flight.setAircraftType(aircraftType); 
    }
    catch (const std::exception&) 
    {
        in.setstate(std::ios::failbit); 
    }

    return in; 
}


AeroflotManager::AeroflotManager() : flights(nullptr), count(0) 
{
    std::cout << "[Конструктор AeroflotManager] Создано пустое хранилище рейсов.\n"; 
}


AeroflotManager::AeroflotManager(const AeroflotManager& other) : flights(nullptr), count(other.count) 
{
    if (count > 0) 
    {
        flights = new Aeroflot[count];
        for (int i = 0; i < count; ++i) flights[i] = other.flights[i]; 
    }
    std::cout << "[Конструктор копирования AeroflotManager] Создана копия хранилища.\n"; 
}


AeroflotManager::~AeroflotManager() 
{
    delete[] flights; 
    flights = nullptr; 
    count = 0; 
    std::cout << "[Деструктор AeroflotManager] Хранилище рейсов уничтожено.\n"; 
}


AeroflotManager& AeroflotManager::operator=(const AeroflotManager& other) 
{
    if (this != &other) 
    {
        Aeroflot* newFlights = nullptr; 
        if (other.count > 0) 
        {
            newFlights = new Aeroflot[other.count]; 
            for (int i = 0; i < other.count; ++i) newFlights[i] = other.flights[i]; 
        }
        delete[] flights; 
        flights = newFlights; 
        count = other.count; 
        std::cout << "[Оператор присваивания AeroflotManager] Содержимое хранилища скопировано.\n";
    }
    return *this; 
}

Aeroflot& AeroflotManager::operator[](int index) 
{
    if (index < 0 || index >= count) throw std::out_of_range("Указан несуществующий номер рейса в списке.");
    return flights[index]; 
}


const Aeroflot& AeroflotManager::operator[](int index) const 
{
    if (index < 0 || index >= count) throw std::out_of_range("Указан несуществующий номер рейса в списке."); 
    return flights[index]; 
}


int AeroflotManager::getCount() const 
{
    return count; 
}


bool AeroflotManager::isEmpty() const 
{
    return count == 0; 
}


void AeroflotManager::sortFlights() 
{
    for (int i = 1; i < count; ++i) 
    {
        Aeroflot current(flights[i]); 
        int j = i - 1; 
        while (j >= 0 && flights[j].getFlightNumber() > current.getFlightNumber()) 
        {
            flights[j + 1] = flights[j]; 
            --j; 
        }
        flights[j + 1] = current; 
    }
}


void AeroflotManager::add(const Aeroflot& flight, int position) 
{
    if (position < 0 || position > count) throw std::out_of_range("Позиция добавления должна быть от 1 до количества рейсов плюс один."); 

    Aeroflot* newFlights = new Aeroflot[count + 1]; 
    for (int i = 0; i < position; ++i) newFlights[i] = flights[i]; 
    newFlights[position] = flight; 
    for (int i = position; i < count; ++i) newFlights[i + 1] = flights[i]; 

    delete[] flights; 
    flights = newFlights; 
    ++count; 
    sortFlights(); 
}


void AeroflotManager::remove(int position) 
{
    if (position < 0 || position >= count) throw std::out_of_range("Нельзя удалить рейс: указан неверный номер записи."); 

    Aeroflot* newFlights = nullptr; 
    if (count > 1) 
    {
        newFlights = new Aeroflot[count - 1]; 
        int newIndex = 0; 
        for (int i = 0; i < count; ++i) 
        {
            if (i != position) newFlights[newIndex++] = flights[i]; 
        }
    }

    delete[] flights; 
    flights = newFlights; 
    --count; 
}


void AeroflotManager::edit(int position, const Aeroflot& flight) 
{
    if (position < 0 || position >= count) throw std::out_of_range("Нельзя изменить рейс: указан неверный номер записи."); 
    flights[position] = flight; 
    sortFlights(); 
}

void AeroflotManager::findByDestination(const std::string& destination) const 
{
    bool found = false; 
    for (int i = 0; i < count; ++i) 
    {
        if (flights[i].getDestination() == destination) 
        {
            std::cout << "Номер рейса: " << flights[i].getFlightNumber() << '\n'; 
            std::cout << "Тип самолёта: " << flights[i].getAircraftType() << "\n\n"; 
            found = true; 
        }
    }
    if (!found) std::cout << "Рейсов в пункт назначения \"" << destination << "\" не найдено.\n"; 
}


std::ostream& operator<<(std::ostream& out, const AeroflotManager& manager) 
{
    if (manager.count == 0) 
    {
        out << "Список авиарейсов пуст.\n"; 
        return out; 
    }

    for (int i = 0; i < manager.count; ++i)
    {
        out << "\nРейс №" << i + 1 << '\n'; 
        out << manager.flights[i]; 
    }
    return out; 
}