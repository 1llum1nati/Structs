#include <iostream>
#include <ctime>
#include <cassert>

class Node {
public:
    int value;
    Node *next;
    Node *prev;
};

class Deque {
protected:
    Node *head = NULL;
    Node *tail = NULL;
    int sizeOfDeque = 0;

    void push_front(int value) {
        if (head == NULL) {
            Node *Temp = new Node;
            Temp->value = value;
            Temp->next = NULL;
            Temp->prev = NULL;
            head = Temp;
            tail = Temp;
        }
        else {
            Node *Temp = new Node;
            head->prev = Temp;
            Temp->value = value;
            Temp->next = head;
            Temp->prev = NULL;
            head = Temp;
        }
        ++sizeOfDeque;
    }

    void push_back(int value) {
        if (head == NULL) {
            Node *Temp = new Node;
            Temp->value = value;
            Temp->next = NULL;
            Temp->prev = NULL;
            head = Temp;
            tail = Temp;
        }
        else {
            Node *Temp = new Node;
            tail->next = Temp;
            Temp->value = value;
            Temp->prev = tail;
            Temp->next = NULL;
            tail = Temp;
        }
        ++sizeOfDeque;
    }

    void pop_front() {
        if (sizeOfDeque > 0) {
            Node *Temp = head;
            head = head->next;
            delete Temp;
            --sizeOfDeque;
        }
        else
            std::cout << "Deque is empty!" << std::endl;
    }
    void pop_back() {
        if (sizeOfDeque > 0) {
            Node *Temp = tail;
            tail = tail->prev;
            delete Temp;
            --sizeOfDeque;
        }
        else
            std::cout << "Deque is empty!" << std::endl;
    }

    void init(int initSize) {
        for (int i = 0; i != initSize; ++i) {
             push_back(rand() % 100);
        }
    }

    void isEmpty() {
        if (!sizeOfDeque)
            std::cout << "Deque is empty!" << std::endl;
        else
            std::cout << "Deque is not empty!" << std::endl;
    }

    void checkValues() {
        if (!sizeOfDeque)
            std::cout << "Deque is empty!" << std::endl;
        else {
            for (int i = 0; i < sizeOfDeque; ++i) {
	        int temp = head->value;
	        std::cout << temp << std::endl;
	        pop_front();
	        push_back(temp);
	    }
        }
    }

    void front() {
    	if (!sizeOfDeque)
    	    std::cout << "Deque is empty!" << std::endl;
    	else
            std::cout << head->value << std::endl;
    }
    void back() {
    	if (!sizeOfDeque)
    	    std::cout << "Deque is empty!" << std::endl;
    	else
            std::cout << tail->value << std::endl;
    }

};

class DequeD : Deque {
public:
    void push_frontD(int number) { push_front(number); }
    void push_backD(int number) { push_back(number); }
    void pop_frontD() { pop_front(); }
    void pop_backD() { pop_back(); }
    void isEmptyD() { isEmpty(); }
    void initD(int sizeOfDeque) { init(sizeOfDeque); }
    void checkValuesD() { checkValues(); }
    void frontD() { front(); }
    void backD() { back(); }
    int size() { return sizeOfDeque; }
    int &operator[] (int index);
    
    void ShellSort(DequeD deque)
    {
        int step = sizeOfDeque / 2;
        while (step >= 1) {
            for (int i = 0; i != (sizeOfDeque - step); ++i) {
                for(int j = i; j >= 0 && deque[j] > deque[j + step]; --j) {
                    deque[j] += deque[j + step];
                    deque[j + step] = deque[j] - deque[j + step];
                    deque[j] -= deque[j + step];
                }
            }
            step /= 2;
        }
    }
};

int &DequeD::operator[] (int index) {
    Node *Temp = head;
    for (int i = 0; i < index; ++i) {
        push_back(Temp->value);
        Temp = head->next;
        pop_front();
    }
    for (int i = 0; i < index; ++i) {
        push_front(tail->value);
        pop_back();
    }
    return Temp->value;
}

int main()
{
    srand(time(NULL));
    DequeD Example;
    int choice = 0, choiceInit = 0;
    std::cout << "Type any number to init the deque, 0 to continue\n";
    std::cin >> choiceInit;
    if (choiceInit) {
        std::cout << "Size?\n";
        int sizeOfDeque;
        std::cin >> sizeOfDeque;
        Example.initD(sizeOfDeque);
        std::cout << "Stack has been initialized!\n";
    }
    while(choice != 12) {
        std::cout << "Enter number:\n" <<
            "1 - push_front\n" <<
            "2 - push_back\n" <<
            "3 - pop_front\n" <<
            "4 - pop_back\n" <<
            "5 - check all\n" <<
            "6 - check front\n" <<
            "7 - check back\n" <<
            "8 - get value\n" <<
            "9 - set value\n" <<
            "10 - check empty\n" <<
            "11 - ShellSort\n" <<
            "12 - stop\n" <<
            "> ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Type any integer number: ";
            int number;
            std::cin >> number;
            Example.push_frontD(number);
        }
        if (choice == 2) {
            std::cout << "Type any integer number: ";
            int number;
            std::cin >> number;
            Example.push_backD(number);
        }
        if (choice == 3) {
            std::cout << "Done!\n"; 
            Example.pop_frontD();
        }
        if (choice == 4) {
            std::cout << "Done!\n";
            Example.pop_backD();
        }
        if (choice == 5) {
            Example.checkValuesD();
        }
        if (choice == 6) {
            Example.frontD();
        }
        if (choice == 7) {
            Example.backD();
        }
        if (choice == 8) {
            int tempIndex;
            std::cout << "Type index" << std::endl;
            std::cin >> tempIndex;
            if (tempIndex >= 0 && tempIndex < Example.size()) {
                std::cout << Example[tempIndex] << std::endl;
            }
            else
                std::cout << "error" << std::endl;
        }
        if (choice == 9) {
            int tempIndex;
            std::cout << "Type index" << std::endl;
            std::cin >> tempIndex;
            if (tempIndex >= 0 && tempIndex < Example.size()) {
                std::cout << "Type value" << std::endl;
                std::cin >> Example[tempIndex];
            }
            else
                std::cout << "error" << std::endl;
        }
        if (choice == 10) {
            Example.isEmptyD();
        }
        if (choice == 11) {
            Example.ShellSort(Example);
        }
    }

    return 0;
}
