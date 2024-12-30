#pragma once
#include <string>
#include <fstream>
#include <iostream> 

using namespace std::string_literals;

class Product {
private:
    struct Info {
        Info()
            : name(""s)
            , count(0)
            , priority(0)
        {}
        std::string name;
        size_t count;
        int priority;
    } command;

    Product* next;

public:
    Product()
        : next(nullptr)
    {}

    explicit Product(const std::string& name, size_t count, int priority) 
        : next(nullptr) 
    {
        command.name = name;
        command.count = count;
        command.priority = priority;
    }

    void setNext(Product* nextProduct) {
        next = nextProduct;
    }

    Product* GetNext() const {
        return next;
    }

    const std::string& GetName() const {
        return command.name;
    }

    size_t GetCount() const {
        return command.count;
    }

    int GetPriority() const {
        return command.priority;
    }
};
