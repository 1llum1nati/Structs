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
    int &operator[] (int index);
    

    void CountingSort(QueueD queue) {
        int len = size();
        int *temp = new int[len];
        int min = queue[0], max = queue[0], newSize;
        for (int i = 1; i < len; ++i) { //max/min
            if(queue[i] > max)
                max = queue[i];
            if(queue[i] < min)
                min = queue[i];
        }
        newSize = max - min + 1;

        int *unique = new int[newSize]; 
        for (int i = min; i < len + min; ++i) { //подсчёт встречаемости каждого числа
            unique[queue[i-min]-min]++;  
        }

        for (int i = 0; i < newSize - 1; ++i) { //кумулятивное сложение
            unique[i+1] += unique[i];
        }

        for (int i = newSize; i > 0; --i) { //смещение вправо
            unique[i] = unique[i-1];
        }
        unique[0] = 0;

        for(int i = 0; i < len; ++i) { //новый отсортированный массив
            temp[unique[queue[i]-min]] = queue[i];
            unique[queue[i]-min]++;
        }

        for (int i = 0; i < len; ++i)
            queue[i] = temp[i];

        delete[] unique;
        delete[] temp;
    }

};

int &QueueD::operator[] (int index) {
    Node *Temp = head;
    for (int i = 0; i < sizeOfQueue; ++i) {
		if(i == index) {
			Temp = head;
		}
		int temp = head->value;
        pop();
        push(temp);
    }
    return Temp->value;
}

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
            "9 - CountingSort\n" <<
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
                std::cout << Example[tempIndex] << std::endl;
            }
            else
                std::cout << "error" << std::endl;
        }
        if (choice == 7) {
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
        if (choice == 8) {
            Example.isEmptyD();
        }
        if (choice == 9) {
            Example.CountingSort(Example);
        }
    }

    return 0;
}
