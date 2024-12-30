#include "Firm.h" 

Firm<std::string>* firm_ = nullptr;

static bool isRangeNum(const std::string& string, const char limit_begin, const char limit_end) {
    if (string.empty()) {
        return false;
    }
    else {
        for (const char& c : string) {
            if (c < limit_begin || c > limit_end) {
                return false;
            }
        }
        return true;
    }
}

enum class InputStatus {
    _EXIT_,
    _PUSH_NEW_FIRM_,
    _PUSH_SUPPLIER_,
    _DELETE_SUPPLIER_,
    _PUSH_PRODUCT_,
    _DELETE_PRODUCT_,
    _PEEK_SUPPLIER_,
    _PEEK_PRODUCT_FROM_SUPPLIER_,
    _PEEK_PRODUCT_FROM_FIRM_,
    _PRINT_,
    _LOAD_STRUCTURE_FROM_FILE_,
    _SAVE_STRUCTURE_TO_FILE_,
    _WAIT_CHOISE_
} input_status_;


static void Dialog() {
    std::cout << "Укажите номер команды:"s << std::endl;
    do {
        std::cout <<
            "1 >> Создать новую фирму"s << std::endl <<
            "2 >> Добавить поставщика"s << std::endl <<
            "3 >> Удалить поставщика" << std::endl <<
            "4 >> Добавить товар" << std::endl <<
            "5 >> Удалить товар" << std::endl <<
            "6 >> Найти поставщика" << std::endl <<
            "7 >> Найти товар у выбранного поставщика" << std::endl <<
            "8 >> Найти товар во всей фирме" << std::endl <<
            "9 >> Вывести состояние структуры в консоль" << std::endl <<
            "10 >> Загрузить структуру из файла" << std::endl <<
            "11 >> Сохранить структуру в файл" << std::endl <<
            "0 >> Завершить работу" << std::endl;

        std::string user_input;
        std::getline(std::cin, user_input);
        if (isRangeNum(user_input, '0', '9')) {
            input_status_ = static_cast<InputStatus>(std::stoi(user_input));
            switch (input_status_) {
            case InputStatus::_EXIT_:
                delete firm_;
                firm_ = nullptr;
                break;
            case InputStatus::_PUSH_NEW_FIRM_: {
                if (firm_) { // Фирма уже существует. Требуется удалить текущую, затем создать новую
                    Supplier<std::string>* currentSupplier = firm_->GetHead();
                    while (currentSupplier) {
                        Supplier<std::string>* temp = currentSupplier;
                        currentSupplier = currentSupplier->GetNextNode();
                        delete temp;
                    }
                }
                std::cout << "Укажите название фирмы: "s;
                std::string firm_name;
                std::getline(std::cin, firm_name);
                firm_ = new Firm<std::string>(firm_name);
                std::cout << "Фирма создана."s << std::endl;
               
                break;
            }
            case InputStatus::_PUSH_SUPPLIER_: {
                if (!firm_) {
                    std::cout << "Сначала создайте фирму."s << std::endl;
                    break;
                }
                std::cout << "Укажите название поставщика: "s;
                std::string supplier_name;
                std::getline(std::cin, supplier_name);
                firm_->PushSupplier(supplier_name);
                std::cout << "Поставщик добавлен."s << std::endl;
                break;
            }

            case InputStatus::_DELETE_SUPPLIER_: {
                if (!firm_) {
                    std::cout << "Сначала создайте фирму."s << std::endl;
                    break;
                }
                std::cout << "Укажите название поставщика для удаления: "s;
                std::string found_supplier;
                std::getline(std::cin, found_supplier);
                firm_->RemoveSupplier(found_supplier);
                std::cout << "Поставщик удален."s << std::endl;
                break;
            }
            case InputStatus::_PUSH_PRODUCT_: {
                if (!firm_) {
                    std::cout << "Сначала создайте фирму."s << std::endl;
                    break;
                }
                std::cout << "Укажите название поставщика: "s;
                std::string supplier_name;
                std::getline(std::cin, supplier_name);
                Supplier<std::string>* supplier = firm_->FindSupplier(supplier_name);
                if (!supplier) {
                    std::cout << "Поставщик не найден."s << std::endl;
                    break;
                }
                std::cout << "Укажите название товара: "s;
                std::string product_name;
                std::getline(std::cin, product_name);
                std::cout << "Укажите количество товара: "s;
                size_t count;
                std::cin >> count;
                std::cout << "Укажите приоритет товара: "s;
                int priority;
                std::cin >> priority;
                std::cin.ignore();  // Игнорируем оставшийся символ новой строки
                supplier->AddProduct(product_name, count, priority);
                std::cout << "Товар добавлен."s << std::endl;
                break;
            }
            case InputStatus::_DELETE_PRODUCT_: {
                if (!firm_) {
                    std::cout << "Фирма не создана."s << std::endl;
                    break;
                }
                else {
                    std::cout << "Укажите название поставщика: "s;
                    std::string supplier_name;
                    std::getline(std::cin, supplier_name);

                    // Найдем поставщика
                    Supplier<std::string>* supplier = firm_->FindSupplier(supplier_name);
                    if (supplier) {
                        std::cout << "Укажите название товара: "s;
                        std::string product_name;
                        std::getline(std::cin, product_name);

                        // Удалим товар у поставщика
                        supplier->DeleteProduct(product_name);
                        std::cout << "Товар удален."s << std::endl;
                    }
                    else {
                        std::cout << "Поставщик не найден."s << std::endl;
                    }
                }
                break; // case InputStatus::_DELETE_PRODUCT_
            }

            case InputStatus::_PEEK_SUPPLIER_: {
                if (!firm_) {
                    std::cout << "Фирма не создана."s << std::endl;
                    break;
                }

                std::cout << "Введите название поставщика: "s;
                std::string supplier_name;
                std::getline(std::cin, supplier_name);

                Supplier<std::string>* supplier = firm_->FindSupplier(supplier_name);
                if (supplier) {
                    std::cout << "Поставщик найден: "s << supplier_name << std::endl;
                }
                else {
                    std::cout << "Поставщик с названием "s << supplier_name << " не найден."s << std::endl;
                }
                break; // case InputStatus::_PEEK_SUPPLIER_
            }

            case InputStatus::_PEEK_PRODUCT_FROM_SUPPLIER_: {
                if (!firm_) {
                    std::cout << "Фирма не создана."s << std::endl;
                    break;
                }

                std::cout << "Введите название поставщика: "s;
                std::string supplier_name;
                std::getline(std::cin, supplier_name);

                Supplier<std::string>* supplier = firm_->FindSupplier(supplier_name);
                if (supplier) {
                    std::cout << "Товары поставщика "s << supplier_name << ":"s << std::endl;
                    supplier->PrintProducts();
                }
                else {
                    std::cout << "Поставщик с названием "s << supplier_name << " не найден."s << std::endl;
                }
                break; // case InputStatus::_PEEK_PRODUCT_FROM_SUPPLIER_
            }

            case InputStatus::_PEEK_PRODUCT_FROM_FIRM_: {
                if (!firm_) {
                    std::cout << "Фирма не создана."s << std::endl;
                    break;
                }

                std::cout << "Введите название товара: "s;
                std::string product_name; // Объявление переменной product_name
                std::getline(std::cin, product_name);

                bool found = false;
                Supplier<std::string>* current_supplier = firm_->GetHead();
                while (current_supplier) {
                    Product* current_product = current_supplier->GetProducts();
                    while (current_product) {
                        if (current_product->GetName() == product_name) {
                            std::cout << "Товар \""s << product_name << "\" найден у поставщика \""s << current_supplier->getValue() << "\""s << std::endl;
                            found = true;
                            break;
                        }
                        current_product = current_product->GetNext();
                    }
                    if (found) {
                        break;
                    }
                    current_supplier = current_supplier->GetNextNode();
                }

                if (!found) {
                    std::cout << "Товар \""s << product_name << "\" не найден во всей фирме."s << std::endl;
                }
                break; // case InputStatus::_PEEK_PRODUCT_FROM_FIRM_
            }

            case InputStatus::_PRINT_: {
                if (!firm_) {
                    std::cout << "Фирма не создана."s << std::endl;
                }
                else {
                    firm_->Print();
                }
                break; // case InputStatus::_PRINT_:
            }
            case InputStatus::_SAVE_STRUCTURE_TO_FILE_: {
                if (!firm_) {
                    std::cout << "Фирма не создана."s << std::endl;
                    break;
                }

                std::cout << "Укажите адрес файла выходного потока: "s;
                std::string path;
                std::getline(std::cin, path);
                std::ofstream file(path);
                if (!file.is_open()) {
                    std::cerr << "Произошла ошибка при открытии файла."s << std::endl;
                    break;
                }
                Supplier<std::string>* tmp = firm_->GetHead();
                while (tmp->GetNextNode() != nullptr) {
                    file << "Firm: "s << tmp->getValue() << std::endl;
                    file << "Supplier: " << tmp->getValue() << std::endl; 
                    Product* current = tmp->GetProducts();
                    while (current) {
                        file << "Product: " << current->GetName() << ", " << current->GetCount() << ", " << current->GetPriority() << std::endl;
                        current = current->GetNext();
                    }
                    tmp = tmp->GetNextNode();
                }

                break; // case InputStatus::_SAVE_STRUCTURE_TO_FILE_
            }
            case InputStatus::_LOAD_STRUCTURE_FROM_FILE_: {
                if (firm_) {
                    delete firm_; // Удаляем старую фирму, если она существует
                    firm_ = nullptr;
                }
                firm_ = new Firm<std::string>(); // Создаем новый объект фирмы

                std::cout << "Укажите адрес файла входного потока: "s;
                std::string path;
                std::getline(std::cin, path);

                std::ifstream file(path); // Открываем файл для чтения
                if (!file.is_open()) {
                    std::cerr << "Произошла ошибка при открытии файла."s << std::endl;
                }

                std::string line;
                std::string currentSupplier;
                while (std::getline(file, line)) {
                    if (line.substr(0, 6) == "Firm: ") {
                        // Устанавливаем имя фирмы
                        firm_->SetFirmName(line.substr(6));
                    }
                    else if (line.substr(0, 10) == "Supplier: ") {
                        // Устанавливаем имя текущего поставщика
                        currentSupplier = line.substr(10); 

                        // Добавляем поставщика в фирму
                        firm_->PushSupplier(currentSupplier);
                    }
                    else if (line.substr(0, 9) == "Product: ") {
                        size_t pos = line.find(", ");
                        std::string productName = line.substr(9, pos - 9);
                        line = line.substr(pos + 2);
                        pos = line.find(", ");
                        size_t productCount = std::stoi(line.substr(0, pos));
                        int productPriority = std::stoi(line.substr(pos + 2));
                        // Добавляем продукт к текущему поставщику
                        firm_->FindSupplier(currentSupplier)->AddProduct(productName, productCount, productPriority);
                    }
                } 
                break; // case InputStatus::_LOAD_STRUCTURE_FROM_FILE_
            }

            case InputStatus::_WAIT_CHOISE_:
                break;
            default:
                std::cout << "Команды не существует."s << std::endl;
                break;
            }
        }
        else {
            std::cout << "Некорректный ввод. Повторите попытку."s << std::endl;
        }
    } while (input_status_ != InputStatus::_EXIT_);
}

int main() {
    setlocale(LC_ALL, "RUS");
    Dialog();
    return 0;
}