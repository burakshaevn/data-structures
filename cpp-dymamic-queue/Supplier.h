#pragma once 
#include "Product.h"

template <typename Type>
class Supplier {
private:
    Type value;
    Supplier<Type>* next_node;
    Product* product_head;
    Product* product_tail;

public:
    Supplier()
        : value(Type())
        , next_node(nullptr)
        , product_head(nullptr)
        , product_tail(nullptr)
    {}

    explicit Supplier(const Type& val, Supplier<Type>* next = nullptr)
        : value(val)
        , next_node(next)
        , product_head(nullptr)
        , product_tail(nullptr)
    {}

    ~Supplier() {
        Product* currentProduct = product_head;
        while (currentProduct) {
            Product* temp = currentProduct;
            currentProduct = currentProduct->GetNext();
            delete temp;
        }
    }

    const Type& getValue() const {
        return value;
    }

    Supplier<Type>* GetNextNode() const {
        return next_node;
    }

    void SetNextNode(Supplier<Type>* next) {
        next_node = next;
    }

    void AddProduct(const std::string& product_name, size_t count, int priority) {
        Product* new_product = new Product(product_name, count, priority);
        if (!product_head || product_head->GetPriority() > priority) {
            new_product->setNext(product_head);
            product_head = new_product;
            if (!product_tail) {
                product_tail = new_product;
            }
        }
        else {
            Product* current = product_head;
            while (current->GetNext() && current->GetNext()->GetPriority() <= priority) {
                current = current->GetNext();
            }
            new_product->setNext(current->GetNext());
            current->setNext(new_product);
            if (!new_product->GetNext()) {
                product_tail = new_product;
            }
        }
    }

    void DeleteProduct(const std::string& product_name) {
        if (!product_head) return;
        Product* current = product_head;
        Product* prev = nullptr;
        while (current && current->GetName() != product_name) {
            prev = current;
            current = current->GetNext();
        }
        if (current) {
            if (prev) {
                prev->setNext(current->GetNext());
            }
            else {
                product_head = current->GetNext();
            }
            if (!current->GetNext()) {
                product_tail = prev;
            }
            delete current;
        }
    }

    void PrintProducts() const {
        Product* current = product_head;
        while (current) {
            std::cout
                << "\t\tТовар " << current->GetName()
                << ", Количество " << current->GetCount()
                << ", Приоритет " << current->GetPriority() << std::endl;
            current = current->GetNext();
        }
    }

    Product* GetProducts() const {
        return product_head;
    }

    int GetProductCount() const {
        int count = 0;
        Product* current = product_head;
        while (current) {
            ++count;
            current = current->GetNext();
        }
        return count;
    }
};
