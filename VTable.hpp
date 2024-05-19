#include <iostream>
#include <map>
#include <functional>
#include <fstream>
#include <vector>
#include <utility>
#include <string>
#include <regex>
#include "TypeInfo.hpp"


std::vector<std::pair<int, std::string>> find_virtual_functions(const std::string& filename)
{
    std::ifstream file(filename);
    std::vector<std::pair<int, std::string>> functions;
    std::string line;
    int VirtualIndex = 0;
    while (std::getline(file, line))
    {
        if (line.find("/*virtual*/") != std::string::npos)
        {
            VirtualIndex++;
            size_t function_start = line.rfind(' ', line.find('('));
            std::string function_name = line.substr(function_start + 1, line.find('(') - function_start - 1);
            functions.push_back(std::make_pair(VirtualIndex, function_name));
        }
    }
    return functions;
}



bool findFunction(const std::string& filename, const std::string& functionName) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string pattern = "\\b" + functionName + "\\s*\\(";
    std::regex functionRegex(pattern);
    
    std::string line;
    while (std::getline(file, line)) {
        if (std::regex_search(line, functionRegex)) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}


class VTable
{
public:
    VTable()
    {
        
    }

    void AddFunction(int index, std::function<void()> func)
    {
        m_functions[index] = func;

    }

    std::unordered_map<int, std::function<void()>> GetFunctions() const {
        return m_functions;
    }

    void CallFunction(int index)
    {
        if (index > 0 && index <= m_functions.size()) {
            m_functions[index]();
        }
    }

    void SetTypeInfo(const TypeInfo& typeinfo)
    {
        m_typeinfo = typeinfo;
    }

    TypeInfo GetTypeInfo() const
    {
        return m_typeinfo;
    }
    
private:
    std::unordered_map<int, std::function<void()>> m_functions;
    TypeInfo m_typeinfo; //my 0 slot;
};