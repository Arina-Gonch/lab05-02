#include "Reader.h" 
#include <fstream> 
#include <sstream> 
#include <stdexcept> 
#include <cctype> 


Reader::Reader() : fileName("") 
{
    std::cout << "[Конструктор Reader] Создан обработчик текста.\n"; 
}


Reader::Reader(const std::string& fileName) : fileName(fileName) 
{
    if (fileName.empty()) throw std::invalid_argument("Имя файла не может быть пустым."); 
    std::cout << "[Конструктор Reader с параметрами] Создан обработчик файла: " << fileName << '\n';
}


Reader::Reader(const Reader& other) : fileName(other.fileName) 
{
    std::cout << "[Конструктор копирования Reader] Создана копия обработчика.\n"; 
}


Reader::~Reader() 
{
    std::cout << "[Деструктор Reader] Объект обработчика уничтожен.\n"; 
}


std::string Reader::getFileName() const 
{
    return fileName; 
}


void Reader::setFileName(const std::string& value) 
{
    if (value.empty()) throw std::invalid_argument("Имя файла не может быть пустым."); 
    fileName = value; 
}


Reader& Reader::operator=(const Reader& other) 
{
    if (this != &other) 
    {
        fileName = other.fileName; 
        std::cout << "[Оператор присваивания Reader] Имя файла скопировано.\n"; 
    }
    return *this; 
}


std::ostream& operator<<(std::ostream& out, const Reader& processor) 
{
    out << "Текущий файл: " << (processor.fileName.empty() ? "не выбран" : processor.fileName) << '\n';
    return out; 
}


static bool startsWithVowel(const std::string& word) 
{
    for (unsigned char ch : word) 
    {
        if (ch >= 'A' && ch <= 'Z') ch = static_cast<unsigned char>(ch - 'A' + 'a'); 
        if (ch >= 'a' && ch <= 'z') 
        {
            return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u'; 
        }
    }
    return false; 
}


void Reader::processFile() const
{
    if (fileName.empty()) throw std::runtime_error("Файл не выбран. Сначала укажите имя файла."); 

    std::ifstream file(fileName); 
    if (!file.is_open()) throw std::runtime_error("Не удалось открыть файл: " + fileName); 

    std::string line; 
    bool found = false; 
    std::cout << "\nСлова, начинающиеся с английских гласных (a, e, i, o, u):\n"; 

    while (std::getline(file, line)) 
    {
        std::stringstream lineStream(line); 
        std::string word; 

        while (lineStream >> word)
        {
            if (startsWithVowel(word)) 
            {
                std::cout << word << '\n';
                found = true; 
            }
        }
    }

    if (file.bad()) throw std::runtime_error("Ошибка при чтении содержимого файла."); 
    if (!found) std::cout << "В файле не найдено слов, начинающихся с английских гласных.\n"; 

    file.close(); 
}