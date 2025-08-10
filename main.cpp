#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

class Person {
private:
    std::string name_;
    int age_;
    int sex_;
    std::string phone_;
    std::string address_;

public:
    Person(std::string &name, int age, int sex, std::string phone, std::string &address)
        : name_(name), age_(age), sex_(sex), phone_(phone), address_(address) {}
    
    Person(Person&& person) noexcept {
        name_ = std::move(person.name_);
        age_ = person.age_;
        sex_ = person.sex_;
        phone_ = std::move(person.phone_);
        address_ = std::move(person.address_);
    }

    Person(const Person& other)
        : name_(other.name_), age_(other.age_), sex_(other.sex_),
          phone_(other.phone_), address_(other.address_) {}

    Person& operator=(const Person& other) {
        if (this != &other) {
            name_ = other.name_;
            age_ = other.age_;
            sex_ = other.sex_;
            phone_ = other.phone_;
            address_ = other.address_;
        }
        return *this;
    }

    Person& operator=(Person&& other) noexcept {
        if (this != &other) {
            name_ = std::move(other.name_);
            age_ = other.age_;
            sex_ = other.sex_;
            phone_ = std::move(other.phone_);
            address_ = std::move(other.address_);
        }
        return *this;
    }

    ~Person() = default;

    std::string FormatSex() const {
        if (sex_ == 1) {
            return "男";
        } else {
            return "女";
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "姓名: " << person.name_
            << "，年龄: " << person.age_
            << "，性别: " << person.FormatSex()
            << "，电话: " << person.phone_
            << "，地址: " << person.address_;

        return os;
    }

    const std::string& get_name() const {
        return name_;
    }
};

class ContactList {
private:
    std::vector<Person> list_;
public:
    void AddPerson(const Person& person) {
        list_.push_back(person);
    }

    void AddPerson(Person&& person) {
        list_.push_back(std::move(person));
    }

    bool RemovePerson(const std::string& name) {
        auto it = std::remove_if(list_.begin(), list_.end(),
            [&name](const Person& person) { 
                return person.get_name() == name; 
            });
        
        if (it != list_.end()) {
            list_.erase(it, list_.end());
            return true;
        }

        return false;
    }

    std::vector<Person*> SearchPerson(const std::string& name) {
        std::vector<Person*> res;

        for (auto& person : list_) {
            if (person.get_name() == name) {
                res.push_back(&person);
            }
        }

        return res;
    }

    int Size() const {
        return list_.size();
    }

    void Clear() {
        list_.clear();
    }

    const std::vector<Person>& get_list() const {
        return list_;
    }
};

constexpr int kMaxSize = 1000;

class ConsoleApp {
private:
    ContactList list_;
public:
    void ShowMenu() {
        std::cout << "***************************" << std::endl;
        std::cout << "*****   1、添加联系人  *****" << std::endl;
        std::cout << "*****   2、显示联系人  *****" << std::endl;
        std::cout << "*****   3、删除联系人  *****" << std::endl;
        std::cout << "*****   4、查找联系人  *****" << std::endl;
        std::cout << "*****   5、修改联系人  *****" << std::endl;
        std::cout << "*****   6、清空联系人  *****" << std::endl;
        std::cout << "*****   0、退出通讯录  *****" << std::endl;
        std::cout << "***************************" << std::endl;
    }

    Person GetPersonFromConsole() {
        std::string name, phone, address;
        int age, sex;

        std::cout << "请输入姓名: ";
        std::cin >> name;

        std::cout << "请输入年龄: ";
        std::cin >> age;

        std::cout << "请输入性别(1: 男, 2: 女): ";

        while (true) {
            std::cin >> sex;

            if (sex == 1 || sex == 2) {
                break;
            } else {
                std::cout << "输入错误，请重新输入性别(1: 男, 2: 女): ";
            }
        }

        std::cout << "请输入电话: ";
        std::cin >> phone;
        
        std::cout << "请输入地址: ";
        std::cin >> address;

        return {name, age, sex, phone, address};
    }

    void DisplayContacts(const std::vector<Person>& contacts) {
        for (const auto& person : contacts) {
            std::cout << person << std::endl;
        }
    }

    void DisplayContacts(const std::vector<Person*>& contacts) {
        for (const auto& person : contacts) {
            std::cout << *person << std::endl;
        }
    }

    void ShowContactsList() {
        if (list_.Size() == 0) {
            std::cout << "通讯录为空" << std::endl;
            return;
        }

        std::cout << "当前通讯录联系人数量: " << list_.Size() << std::endl;
        DisplayContacts(list_.get_list());
    }

    void Add() {
        if (list_.Size() >= kMaxSize) {
            std::cout << "通讯录已满，无法添加更多联系人" << std::endl;
            return;
        }

        Person person = GetPersonFromConsole();
        list_.AddPerson(std::move(person));
        std::cout << "添加联系人成功" << std::endl;
    }

    void Remove() {
        if (list_.Size() == 0) {
            std::cout << "通讯录为空，无法删除联系人" << std::endl;
            return;
        }

        std::string name;
        std::cout << "请输入要删除的联系人姓名: ";
        std::cin >> name;

        if (list_.RemovePerson(name)) {
            std::cout << "删除联系人成功" << std::endl;
        } else {
            std::cout << "删除失败，未找到联系人" << std::endl;
        }
    }

    void Modify() {
        if (list_.Size() == 0) {
            std::cout << "通讯录为空，无法修改联系人" << std::endl;
            return;
        }

        std::string name;
        std::cout << "请输入要修改的联系人姓名: ";
        std::cin >> name;

        auto res = list_.SearchPerson(name);
        if (res.empty()) {
            std::cout << "未找到联系人" << std::endl;
            return;
        }

        std::cout << "找到以下联系人: " << std::endl;
        DisplayContacts(res);

        if (res.size() == 1) {
            auto person = GetPersonFromConsole();
            *res[0] = person;
            return;
        }

        
        int select;
        bool exit_flag = false;

        while (true) {
            std::cout << "请输入要修改的联系人序号(从1开始)，-1表示退出修改: " << std::endl;
            std::cin >> select;

            if (select == -1) {
                break;
            } else if (select <= 0 || select > res.size()) {
                std::cout << "输入序号错误，请重新输入: " << std::endl;
            } else {
                *res[select - 1] = GetPersonFromConsole();
                std::cout << "修改联系人成功" << std::endl;
            }
        }
    }

    void Search() {
        if (list_.Size() == 0) {
            std::cout << "通讯录为空，无法查找联系人" << std::endl;
            return;
        }

        std::string name;
        std::cout << "请输入要查找的联系人姓名: " << std::endl;
        std::cin >> name;

        auto res = list_.SearchPerson(name);
        if (res.empty()) {
            std::cout << "未找到联系人" << std::endl;
        } else {
            DisplayContacts(res);
        }
    }

    void Clear() {
        list_.Clear();
        std::cout << "通讯录已清空" << std::endl;
    }

    void Run() {
        int choice;
        using mem_fun_ptr = void (ConsoleApp::*)();
        mem_fun_ptr funcs[] = {
            &ConsoleApp::Add,
            &ConsoleApp::ShowContactsList,
            &ConsoleApp::Remove,
            &ConsoleApp::Search,
            &ConsoleApp::Modify,
            &ConsoleApp::Clear
        };
        
        ShowMenu();
        while (true) {
            std::cout << "请输入您的选择: ";
            std::cin >> choice;

            if (choice == 0) {
                std::cout << "退出通讯录" << std::endl;
                break;
            } else if (choice < 1 || choice > 6) {
                std::cout << "输入错误，请重新输入" << std::endl;
            } else {
                (this->*funcs[choice - 1])();
            }
        }
    }
};

int main() {
    ConsoleApp app;
    app.Run();
    return 0;
}
