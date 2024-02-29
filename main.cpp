#include <iostream>
#include <Windows.h>
using namespace std;

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
};

void menu(){
    cout << "1) Заполнить список\n" <<
    "2) Редактировать список\n" <<
    "3) Заполнить массив\n" <<
    "4) Редактировать массив\n" <<
    "5) Выход\n-->> ";
}


int randint(){
    return rand() % 200 - 99;
}


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

int main() {
    SetConsoleOutputCP(CP_UTF8);
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
                    randList(list);
                    printList(list);
                }
                else if (choise == 2){
                    clearList(list);
                    fillList(list);
                    printList(list);
                }
                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:
                exit(0);
                break;
            default:
                cout << "Неправильно введен номер!!!\n";
                break;
        }
    }
    return 0;
}

