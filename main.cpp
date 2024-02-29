#include <iostream>
#include <Windows.h>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;


struct Node {
    int data;
    Node* prev, *next;
    Node(int data):data(data), prev(nullptr), next(nullptr){}
};

struct LinkedList{
    Node* head, * tail;

    LinkedList(){
        head = tail = nullptr;
    }

    ~LinkedList(){
        while(head != nullptr) popFront();
    }

    Node* pushFront(int data){
        Node* ptr = new Node(data);
        ptr->next = head;
        if (head != nullptr){
            head->prev = ptr;
        }
        if (tail == nullptr){ //Если объект единственный tail == nullptr
            tail = ptr;
        }
        head = ptr;
        return ptr;
    }

    Node* pushBack(int data){
        Node* ptr = new Node(data);
        ptr->prev = tail;
        if (tail != nullptr){
            tail->next = ptr;
        }
        if (head == nullptr){ //Если объект единственный head == nullptr
            head = ptr;
        }
        tail = ptr;
        return ptr;
    }

    void popFront(){
        if(head == nullptr) return; //Если нет элементов, то удалять нечего => return
        Node* ptr = head->next;
        if(ptr != nullptr){
            ptr->prev = nullptr;
        }
        else //если единственный объект
            tail = nullptr;
        delete head;
        head = ptr;
    }

    void popBack(){
        if(tail == nullptr) return; //Если нет элементов, то удалять нечего => return
        Node* ptr = tail->prev;
        if(ptr != nullptr){
            ptr->next = nullptr;
        }
        else //если единственный объект
            head = nullptr;
        delete tail;
        tail = ptr;
    }

    Node* getAt(int index){
        Node* ptr = head;
        int n = 0;
        while(n != index){
            if (ptr == nullptr) return nullptr;//если нет объектов или дошли до конца списка
            ptr = ptr->next;
            n++;
        }
        return ptr;
    }

    Node* insert (int index, int data){
        Node* right = getAt(index);
        if (right == nullptr) return pushBack(data);
        Node* left = right->prev;
        if (left == nullptr) pushFront(data);
        Node* ptr = new Node(data);
        ptr->prev = left;
        ptr->next = right;
        left->next = ptr;
        right->prev = ptr;
        return ptr;
    }

    void erase(int index){
        Node* ptr = getAt(index);
        if (ptr == nullptr) return; //нет такого элемента для удаления
        if (ptr->prev == nullptr){ //если удаляемый элемент первый
            popFront();
            return;
        }
        if (ptr->next == nullptr){ //если удаляемый элемент последний
            popBack();
            return;
        }
        Node* left = ptr->prev;
        Node* right = ptr->next;
        left->next = right;
        right->prev = left;
        delete ptr;
    }

    void swapElements(int index1, int index2){
        Node* ptr1 = getAt(index1);
        Node* ptr2 = getAt(index2);
        Node* left1 = getAt(index1-1);
        Node* left2 = getAt(index2-1);
        Node* right1 = getAt(index1+1);
        Node* right2 = getAt(index2+1);

        if (ptr1 == nullptr) return;
        else if (ptr2 == nullptr) return;
        else if (index1 == index2) return;

        if (left1 != nullptr) {
            left1->next = ptr2;
        } else {
            head = ptr2;
        }

        if (left2 != nullptr) {
            left2->next = ptr1;
        } else {
            head = ptr1;
        }

        if (right1 != nullptr) {
            right1->prev = ptr2;
        }

        if (right2 != nullptr) {
            right2->prev = ptr1;
        }

        // Обновление указателей next и prev у самих элементов
        Node* temp = ptr1->next;
        ptr1->next = ptr2->next;
        ptr2->next = temp;
        temp = ptr1->prev;
        ptr1->prev = ptr2->prev;
        ptr2->prev = temp;
    }
};


//Обычные функции
void menu(){
    cout << "1) Заполнить список\n" <<
         "2) Редактировать список\n" <<
         "3) Вывести список\n" <<
         "4) Заполнить массив\n" <<
         "5) Редактировать массив\n" <<
         "6) Выход\n-->> ";
}


void editMenu(){
    cout << "\n1) Вставить элемент\n" <<
         "2) Удалить элемент по индексу\n" <<
         "3) Удалить элемент по значению\n" <<
         "4) Обмен элементов\n" <<
         "5) Получить элемент по индексу\n" <<
         "6) Получить элемент по значению\n-->> ";
}


int randint(){
    return rand() % 99;
}

//Функции list
void printList(LinkedList &list){
    for (Node *ptr = list.head; ptr != nullptr; ptr = ptr->next)
        cout << ptr->data << " ";
    cout << "\n";
}


void randList(LinkedList &list){
    int lenght = 0;
    cout << "Введите количество элементов -->> ";
    cin >> lenght;
    for (int i = 0; i < lenght; i++){
        list.pushBack(randint());
    }
}


void fillList(LinkedList &list){
    int number;
    while (cin >> number) {
        list.pushBack(number);
        if (cin.peek() == '\n') {
            break;
        }
    }
}


void clearList(LinkedList &list){
    while(list.head != nullptr) list.popBack();
}


int findId(LinkedList &list, int number){
    int id = 0;
    for (Node *ptr = list.head; ptr != nullptr; ptr = ptr->next){
        if (ptr->data == number){
            return id;
        }
        id++;
    }
    return -1;
}


//Функции динамического массива


//.........................................................
int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
    nanoseconds result;

    int choise;
    LinkedList list;

    while(true){
        menu();
        cin >> choise;
        switch (choise){
            case 1:
                system("cls");
                cout << "1) Зарандомить\n" <<
                "2) Ввести ручками\n-->> ";
                cin >> choise;
                if (choise == 1){
                    clearList(list);
                    start = steady_clock::now();
                    randList(list);
                    end = steady_clock::now();
                    result = duration_cast<nanoseconds>(end - start);
                    cout << "\nВремя создания: " << result.count() << "\n";
                }
                else if (choise == 2){
                    clearList(list);
                    start = steady_clock::now();
                    fillList(list);
                    end = steady_clock::now();
                    result = duration_cast<nanoseconds>(end - start);
                    cout << "\nВремя создания: " << result.count() << "\n";
                }
                break;
            case 2:
                int number, id;
                Node* pointer;
                editMenu();
                cin >> choise;
                if (choise == 1){
                    cout << "Индекс: ";
                    cin >> id;
                    cout << "Значение: ";
                    cin >> number;
                    list.insert(id, number);
                    printList(list);
                }
                else if (choise == 2){
                    cout << "Индекс: ";
                    cin >> id;
                    list.erase(id);
                    printList(list);
                }
                else if (choise == 3){
                    cout << "Значение: ";
                    cin >> number;
                    id = findId(list, number);
                    if (id == -1){
                        cout << "\nТакого элемента нет!\n";
                        break;
                    }
                    list.erase(id);
                    printList(list);
                }
                else if (choise == 4){
                    cout << "Индекс1: ";
                    cin >> id;
                    cout << "Индекс2: ";
                    cin >> number;
                    list.swapElements(id, number);
                    printList(list);
                }
                else if (choise == 5){
                    cout << "Индекс: ";
                    cin >> id;
                    pointer = list.getAt(id);
                    cout << "Индекс: " << id << "\tЗначение: " << pointer->data << "\n";
                }
                else if (choise == 6){
                    cout << "Значение: ";
                    cin >> number;
                    id = findId(list, number);
                    pointer = list.getAt(id);
                    cout << "Индекс: " << id << "\tЗначение: " << pointer->data << "\n";
                }
                else cout << "\nНеправильно введен номер!!!\n";
                break;
            case 3:
                printList(list);
                break;
            case 4:
                
                break;
            case 5:

                break;
            case 6:
                exit(0);
            default:
                cout << "Неправильно введен номер!!!\n";
                break;
        }
    }
}

