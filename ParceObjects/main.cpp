#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

enum ObjectType {TableData = 0, Table = 1, Form = 2, Report = 3, Dataport = 4, CodeUnit = 5,
                 XmlPort = 6, MenuSuite = 7, Page = 8, Query = 9, System = 10, FieldNumber = 11,
                 LimitedUsageTableData = 12, TablePage = 13, PageExtension = 14,
                 TableExtension = 15, Enum = 16, EnumExtension = 17, Profile = 18,
                 ProfileExtension = 19, PermissionSet = 20, PermissionSetExtension = 21,
                 ReportExtension = 22};

struct Object {
    uint64_t id;
    uint8_t type;

    Object() : id(0), type(23) {};
    Object(uint64_t new_id, uint8_t new_type)
        : id(new_id), type(new_type) {}
};

uint8_t CharToInt (const char c) {
    switch(static_cast<int>(c)) {
        case static_cast<int>('0'): return 0;
        case static_cast<int>('1'): return 1;
        case static_cast<int>('2'): return 2;
        case static_cast<int>('3'): return 3;
        case static_cast<int>('4'): return 4;
        case static_cast<int>('5'): return 5;
        case static_cast<int>('6'): return 6;
        case static_cast<int>('7'): return 7;
        case static_cast<int>('8'): return 8;
        case static_cast<int>('9'): return 9;
    }
    std::string error_text = "Incorrect input symbol: <#>.";
    error_text[25] = c;
    throw std::out_of_range(error_text);
    return 99;
}

std::vector<std::string> SplitIntoWords (const std::string& text) {
    if (text.empty()) {
        return {};
    }
    size_t words_size = 1;
    for (const char c : text) {
        if (c == ' ') {
            ++ words_size;
        }
    }
    std::vector<std::string> words(words_size);
    std::string word = "";
    for (const char c : text) {
        if (c == ',') {
            if (!word.empty()) {
                words.push_back(word);
                word.clear();
            }
        } else if (c == ' ') {
            continue;
        } else {
            word += c;
        }
    }

    if (!word.empty()) {
        words.push_back(word);
    }
    return words;
}

uint64_t StringToNumber (const std::string &string_number) {
    std::string reversed_number = string_number;
    std::reverse(reversed_number.begin(), reversed_number.end());
    uint64_t result = 0;
    for (const char c : reversed_number) {
        result *= 10;
        result += CharToInt(c);
    }
    return result;

}

double StringToNumber (const std::string &string_number, bool is_ceil) {
    std::string reversed_number = string_number;
    double result = 0;
    if (is_ceil) {
        std::reverse(reversed_number.begin(), reversed_number.end());
        for (const char c : reversed_number) {
            result *= 10.0;
            result += static_cast<double>(CharToInt(c));
        }
        return result;
    }
    double divider = 10.0;
    for (const char c : reversed_number) {
        result += static_cast<double>(CharToInt(c)) / divider;
        divider /= 10.0;
    }
    return result;
}

uint8_t ConvertObjectType (const std::string &object_type) {
    if (object_type == "TableData") return ObjectType::TableData;
    if (object_type == "Table") return ObjectType::Table;
    if (object_type == "Form") return ObjectType::Form;
    if (object_type == "Report") return ObjectType::Report;
    if (object_type == "Dataport") return ObjectType::Dataport;
    if (object_type == "CodeUnit") return ObjectType::CodeUnit;
    if (object_type == "XmlPort") return ObjectType::XmlPort;
    if (object_type == "MenuSuite") return ObjectType::MenuSuite;
    if (object_type == "Page") return ObjectType::Page;
    if (object_type == "Query") return ObjectType::Query;
    if (object_type == "System") return ObjectType::System;
    if (object_type == "FieldNumber") return ObjectType::FieldNumber;
    if (object_type == "LimitedUsageTableData") return ObjectType::LimitedUsageTableData;
    if (object_type == "TablePage") return ObjectType::TablePage;
    if (object_type == "PageExtension") return ObjectType::PageExtension;
    if (object_type == "TableExtension") return ObjectType::TableExtension;
    if (object_type == "Enum") return ObjectType::Enum;
    if (object_type == "EnumExtension") return ObjectType::EnumExtension;
    if (object_type == "Profile") return ObjectType::Profile;
    if (object_type == "ProfileExtension") return ObjectType::ProfileExtension;
    if (object_type == "PermissionSet") return ObjectType::PermissionSet;
    if (object_type == "PermissionSetExtension") return ObjectType::PermissionSetExtension;
    if (object_type == "ReportExtension") return ObjectType::ReportExtension;
    throw std::logic_error("ObjectType was not declared yet: <" + object_type + ">.");
}

double ConwertWeightFromString (const std::string &weight) {
    std::string ceil = "", rational = "";
    size_t delimiter_id = 0;
    for (const char c : weight) {
        if ((c == ',') || (c == '.')) {
            break;
        }
        ceil += c;
        ++ delimiter_id;
    }
    ++ delimiter_id;
    for (/**/; delimiter_id < weight.size(); ++ delimiter_id) {
        rational += weight[delimiter_id];
    }
    double result = StringToNumber(ceil, true) + StringToNumber(rational, false);
    return result;
}

class Input {
private:
    std::string file_name = "";

public:
    Input (const std::string &new_file_name) {
        file_name = new_file_name;
    }

    std::vector<std::map<Object, int>> ReadData () {
        if (file_name.empty()) {
            throw std::logic_error("File name not set yet.");
        }
        std::map<Object, std::map<Object, double /*weight*/>> objects_with_links;
        std::unordered_map<Object, double /*weight*/> unique_objects;
        std::fstream my_file(file_name);
        while (!my_file.eof()) {
            std::string reader;
            getline(my_file, reader);
            if (reader.empty()) {
                continue;
            }
            std::vector<std::string> words = SplitIntoWords(reader);
            Object head_object(StringToNumber(words[0]), ConvertObjectType(words[1]));
            if (words.size() == 3) {
                unique_objects.insert({Object, StringToNumber(words[2])});
            }
        }
    }
};

int main () {
    return 0;

}
