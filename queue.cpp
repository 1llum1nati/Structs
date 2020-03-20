#include <iostream>
#include <ctime>
#include <cassert>

class Node {
public:
    int value;
    Node *next;
    Node *prev;
};

class Queue {
protected:
    Node *head = NULL;
    Node *tail = NULL;
    int sizeOfQueue = 0;

    void push(int value) {
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
        ++sizeOfQueue;
    }

    void pop() {
        if (sizeOfQueue > 0) {
            Node *Temp = head;
            head = head->next;
            delete Temp;
            --sizeOfQueue;
        }
        else
            std::cout << "Queue is empty!" << std::endl;
    }

    void init(int initSize) {
        for (int i = 0; i != initSize; ++i) {
             push(rand() % 100);
        }
    }

    void isEmpty() {
        if (!sizeOfQueue)
            std::cout << "Queue is empty!" << std::endl;
        else
            std::cout << "Queue is not empty!" << std::endl;
    }

    void checkValues() {
        if (!sizeOfQueue)
            std::cout << "Queue is empty!" << std::endl;
        else {
            for (int i = 0; i < sizeOfQueue; ++i) {
				int temp = head->value;
				std::cout << temp << std::endl;
				pop();
				push(temp);
			}
        }
    }

    void front() {
    	if (!sizeOfQueue)
    	    std::cout << "Queue is empty!" << std::endl;
    	else
            std::cout << head->value << std::endl;
    }
    void back() {
    	if (!sizeOfQueue)
    	    std::cout << "Queue is empty!" << std::endl;
    	else
            std::cout << tail->value << std::endl;
    }

};

class QueueD : Queue {
public:
    void pushD(int number) { push(number); }
    void popD() { pop(); }
    void isEmptyD() { isEmpty(); }
    void initD(int sizeOfQueue) { init(sizeOfQueue); }
    void checkValuesD() { checkValues(); }
    void frontD() { front(); }
    void backD() { back(); }
    int size() { return sizeOfQueue; }

    int Get(int index) {
        int val;
        for (int i = 0; i < sizeOfQueue; ++i) {
            if(i == index) {
                val = head->value;
            }
            int temp = head->value;
            pop();
            push(temp);
        }

        return val;
    }

    void Set(int index, int val) {
        for (int i = 0; i < sizeOfQueue; ++i) {
            if(i == index) {
                head->value = val;
            }
            int temp = head->value;
            pop();
            push(temp);
        }
    }

    void InsertionSort(QueueD queue) {
    for(int i = 1; i < size(); i++)
        for(int j = i; j > 0 && queue.Get(j-1) > queue.Get(j); j--) {
            int temp = queue.Get(j-1);
            queue.Set(j-1, queue.Get(j));
            queue.Set(j, temp);
        }   
    }

};

int main()
{
    srand(time(NULL));
    QueueD Example;
    int choice = 0, choiceInit = 0;
    std::cout << "Type any number to init the queue, 0 to continue\n";
    std::cin >> choiceInit;
    if (choiceInit) {
        std::cout << "Size?\n";
        int sizeOfQueue;
        std::cin >> sizeOfQueue;
        Example.initD(sizeOfQueue);
        std::cout << "Queue has been initialized!\n";
    }
    while(choice != 10) {
        std::cout << "Enter number:\n" <<
            "1 - push\n" <<
            "2 - pop\n" <<
            "3 - check all\n" <<
            "4 - check front\n" <<
            "5 - check back\n" <<
            "6 - get value\n" <<
            "7 - set value\n" <<
            "8 - check empty\n" <<
            "9 - InsertionSort\n" <<
            "10 - stop\n" <<
            "> ";
        std::cin >> choice;
        if (choice == 1) {
            std::cout << "Type any integer number: ";
            int number;
            std::cin >> number;
            Example.pushD(number);
        }

        if (choice == 2) {
            std::cout << "Done!\n";
            Example.popD();
        }

        if (choice == 3) {
            Example.checkValuesD();
        }
        if (choice == 4) {
            Example.frontD();
        }
        if (choice == 5) {
            Example.backD();
        }
        if (choice == 6) {
            int tempIndex;
            std::cout << "Type index" << std::endl;
            std::cin >> tempIndex;
            if (tempIndex >= 0 && tempIndex < Example.size()) {
                std::cout << Example.Get(tempIndex) << std::endl;
            }
            else
                std::cout << "error" << std::endl;
        }
        if (choice == 7) {
            int tempIndex, tempValue;
            std::cout << "Type index" << std::endl;
            std::cin >> tempIndex;
            if (tempIndex >= 0 && tempIndex < Example.size()) {
                std::cout << "Type value" << std::endl;
                std::cin >> tempValue;
                Example.Set(tempIndex, tempValue);
                std::cout << "Done!\n";
            }
            else
                std::cout << "error" << std::endl;
        }
        if (choice == 8) {
            Example.isEmptyD();
        }
        if (choice == 9) {
            Example.InsertionSort(Example);
        }
    }

    return 0;
}
