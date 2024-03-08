#include <iostream>
#include <Windows.h>
#include <ctime>
#include <chrono>
#undef max
using namespace std;
using namespace chrono;


struct Node {
    int data;
    Node* prev, *next;
    Node(int input_data) {
        data = input_data;
        prev = nullptr;
        next = nullptr;
    }
};

struct LinkedList{
    Node* head, * tail;

    void LinkedList_create() {
        head = tail = nullptr;
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

    void eraseByIndex(int index){
        Node* ptr = getAt(index);
        if (ptr == nullptr){
            cout << "\nНет элемента для удаления\n";
            return; //нет такого элемента для удаления
        }
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

    void eraseByValue(int number){
        Node* ptr = head;
        while(ptr != nullptr && ptr->data != number){
            ptr = ptr->next;
        }
        if (ptr == nullptr){
            cout << "\nНет элемента для удаления!\n";
            return; //нет такого элемента для удаления
        }
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
         "2) Действия со списоком\n" <<
         "3) Вывести список\n" <<
         "4) Заполнить массив\n" <<
         "5) Действия с массивом\n" <<
         "6) Вывести массив\n" <<
         "7) Очистить экран\n" <<
         "8) Выход\n-->> ";
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
    return rand() % 100;
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


int findInList(LinkedList &list, int number){
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
void randArray(int &sizeArr, int* &arr){
    int  *rez = new int[sizeArr];
    for (int i = 0; i < sizeArr; i++){
        *(rez + i) = randint();
    }
    delete[] arr;
    arr = rez;
}





void printArray(int &sizeArr, int* &arr){
    for (int i = 0; i < sizeArr; i++){
        cout << arr[i] << " ";
    }
    cout << "\n";
}


void addToArray(int &sizeArr, int* &arr, int &id, int& number){
    sizeArr++;
    int  *rez = new int[sizeArr];
    for (int i = 0; i < id; i++) {
        rez[i] = arr[i];
    }
    rez[id] = number;
    for (int i = id; i < sizeArr - 1; i++) {
        rez[i+1] = arr[i];
    }
    delete[] arr;
    arr = rez;
}


void fillArray(int &sizeArr, int* &arr, int &number){
    while (true){
        cin >> number;
        int  *rez = new int[sizeArr+1];
        for (int i = 0; i < sizeArr; i++) {
            rez[i] = arr[i];
        }
        rez[sizeArr] = number;
        sizeArr++;
        delete[] arr;
        arr = rez;
        if (cin.peek() == '\n') {
            break;
        }
    }
}


void deleteByIndex(int &sizeArr, int* &arr, int& id){
    sizeArr--;
    int  *rez = new int[sizeArr];
    int j = 0;
    for (int i = 0; i < sizeArr+1; i++) {
        if (i != id) {
            *(rez + j) = *(arr + i);
            j++;
        }
    }
    delete[] arr;
    arr = rez;
}


void deleteByValue(int &sizeArr, int* &arr, int& number){
    sizeArr--;
    int  *rez = new int[sizeArr];
    int j = 0;
    for (int i = 0; i < sizeArr+1; i++) {
        if (*(arr + i) != number) {
            *(rez + j) = *(arr + i);
            j++;
        }
    }
    delete[] arr;
    arr = rez;
}


void swapInArray(int &sizeArr, int* &arr, int index1, int index2){
    if (index1 < 0 || index2 < 0) return;
    if (index1 >= sizeArr || index2 >= sizeArr) return;
    swap(*(arr + index1), *(arr + index2));
}


void getByValue(int &sizeArr, int* &arr,int &number){
    for (int i = 0; i < sizeArr; i++){
        if (*(arr + i) == number){
            cout << "Индекс: " << i << "\n";
            return;
        }
    }
    cout << "\nЗначение не найдено!\n";
}

//.........................................................
int main() {
    SetConsoleOutputCP(CP_UTF8);
    srand(time(NULL));
    time_point<steady_clock, duration<__int64, ratio<1, 1000000000>>> start, end;
    nanoseconds result;

    int choise, sizeArr = 0, id, number;
    int* arr = new int [sizeArr];
    LinkedList list;
    list.LinkedList_create();
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
                    printList(list);
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
                Node* pointer;
                editMenu();
                cin >> choise;
                switch(choise){
                    case 1:
                        cout << "Индекс: ";
                        cin >> id;
                        cout << "Значение: ";
                        cin >> number;
                        start = steady_clock::now();
                        list.insert(id, number);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        printList(list);
                        cout << "\nВремя вставки: " << result.count() << "\n";
                        break;
                    case 2:
                        cout << "Индекс: ";
                        cin >> id;
                        start = steady_clock::now();
                        list.eraseByIndex(id);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        printList(list);
                        cout << "\nВремя удаления: " << result.count() << "\n";
                        break;
                    case 3:
                        cout << "Значение: ";
                        cin >> number;
                        start = steady_clock::now();
                        list.eraseByValue(number);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        printList(list);
                        cout << "\nВремя удаления: " << result.count() << "\n";
                        break;
                    case 4:
                        cout << "Индекс1: ";
                        cin >> id;
                        cout << "Индекс2: ";
                        cin >> number;
                        list.swapElements(id, number);
                        printList(list);
                        break;
                    case 5:
                        cout << "Индекс: ";
                        cin >> id;
                        start = steady_clock::now();
                        pointer = list.getAt(id);
                        cout << "Значение: " << pointer->data << "\n";
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        cout << "Время получения: " << result.count() << "\n";
                        break;
                    case 6:
                        cout << "Значение: ";
                        cin >> number;
                        start = steady_clock::now();
                        id = findInList(list, number);
                        if (id == -1){
                            cout << "\nНеправильно введено значение!\n";
                        }
                        else{
                            cout << "Индекс: " << id << "\n";
                        }
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        cout << "Время получения: " << result.count() << "\n";
                        break;
                    default:
                        cout << "Неправильно введен номер!!!\n";
                        break;
                }
                break;
            case 3:
                printList(list);
                break;
            case 4:
                cout << "1) Зарандомить\n" <<
                     "2) Ввести ручками\n-->> ";
                cin >> choise;
                if (choise == 1){
                    cout << "Введите размер массива\n-->> ";
                    cin >> sizeArr;
                    start = steady_clock::now();
                    randArray(sizeArr, arr);
                    printArray(sizeArr, arr);
                    end = steady_clock::now();
                    result = duration_cast<nanoseconds>(end - start);
                    cout << "\nВремя создания: " << result.count() << "\n";
                }
                else if (choise == 2){
                    start = steady_clock::now();
                    fillArray(sizeArr, arr, number);
                    printArray(sizeArr, arr);
                    end = steady_clock::now();
                    result = duration_cast<nanoseconds>(end - start);
                    cout << "\nВремя создания: " << result.count() << "\n";
                }
                break;
            case 5:
                editMenu();
                cin >> choise;
                switch(choise){
                    case 1:
                        cout << "Индекс: ";
                        cin >> id;
                        cout << "Значение: ";
                        cin >> number;
                        start = steady_clock::now();
                        addToArray(sizeArr, arr, id, number);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        printArray(sizeArr, arr);
                        cout << "\nВремя вставки: " << result.count() << "\n";
                        break;
                    case 2:
                        cout << "Индекс: ";
                        cin >> id;
                        start = steady_clock::now();
                        deleteByIndex(sizeArr, arr, id);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        printArray(sizeArr, arr);
                        cout << "\nВремя удаления: " << result.count() << "\n";
                        break;
                    case 3:
                        cout << "Значение: ";
                        cin >> number;
                        start = steady_clock::now();
                        deleteByValue(sizeArr, arr, number);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        printArray(sizeArr, arr);
                        cout << "\nВремя удаления: " << result.count() << "\n";
                        break;
                    case 4:
                        cout << "Индекс1: ";
                        cin >> id;
                        cout << "Индекс2: ";
                        cin >> number;
                        swapInArray(sizeArr, arr, id, number);
                        break;
                    case 5:
                        cout << "Индекс: ";
                        cin >> id;
                        if (id < 0 || id >= sizeArr){
                            cout << "\nНеправильно введён индекс!\n";
                        }
                        else{
                            start = steady_clock::now();
                            cout << "Значение: " << *(arr + id) << "\n";
                            end = steady_clock::now();
                            result = duration_cast<nanoseconds>(end - start);
                            cout << "Время получения: " << result.count() << "\n";
                        }
                        break;
                    case 6:
                        cout << "Значение: ";
                        cin >> number;
                        start = steady_clock::now();
                        getByValue(sizeArr, arr, number);
                        end = steady_clock::now();
                        result = duration_cast<nanoseconds>(end - start);
                        cout << "Время получения: " << result.count() << "\n";
                        break;
                    default:
                        cout << "Неправильно введён номер!!!\n";
                        break;
                }
                break;
            case 6:
                printArray(sizeArr, arr);
                break;
            case 7:
                system("cls");
                break;
            case 8:
                clearList(list);
                delete [] arr;
                exit(0);
            default:
                cout << "\nНеправильно ввёден номер!!!\n";
                break;
        }
    }
}

