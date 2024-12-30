#pragma once 
#include "Supplier.h"

template <typename Type>
class Firm {
private:
    std::string name;     // строка, содержащая название фирмы
    Supplier<Type>* head; // указатель на первый поставщик в списке поставщиков
    Supplier<Type>* tail; // указатель на последний поставщик в списке поставщиков

public:
    Firm()
        : name("")
        , head(nullptr)
        , tail(nullptr)
    {}

    explicit Firm(const std::string& firm_name)
        : name(firm_name)
        , head(nullptr)
        , tail(nullptr)
    {}

    ~Firm() { 
        Supplier<Type>* currentSupplier = head;
        while (currentSupplier) {
            Supplier<Type>* temp = currentSupplier;
            currentSupplier = currentSupplier->GetNextNode();
            delete temp;
        }
    }

    // устанавливает название фирмы
    void SetFirmName(const std::string& firm_name) {
        name = firm_name;
    }
    
    // добавляет нового поставщика в конец списка
    void PushSupplier(const Type& value) {
        Supplier<Type>* new_supplier = new Supplier<Type>(value);
        if (!head) {
            head = new_supplier;
            tail = new_supplier;
        }
        else {
            tail->SetNextNode(new_supplier);
            tail = new_supplier;
        }
    }

    //  getter функция для атрибута head
    Supplier<Type>* GetHead() const {
        return head;
    }

    // находит поставщика по значению
    Supplier<Type>* FindSupplier(const Type& value) {
        Supplier<Type>* current = head;
        while (current) {
            if (current->getValue() == value) {
                return current;
            }
            current = current->GetNextNode();
        }
        return nullptr;
    }

    // удаляет поставщика из списка
    void RemoveSupplier(const Type& value) {
        Supplier<Type>* current = head;
        Supplier<Type>* previous = nullptr;
        while (current) {
            if (current->getValue() == value) {
                if (previous) {
                    previous->SetNextNode(current->GetNextNode());
                }
                else {
                    head = current->GetNextNode();
                }
                if (current == tail) {
                    tail = previous;
                }
                delete current;
                return;
            }
            previous = current;
            current = current->GetNextNode();
        }
    }

    // выводит информацию о фирме и ее поставщиках
    void Print() const {
        Supplier<Type>* current = head;
        std::cout << name << std::endl;
        while (current) {
            std::cout << "\tПоставщик " << current->getValue() << std::endl;
            current->PrintProducts();
            current = current->GetNextNode();
        }
    }
};
