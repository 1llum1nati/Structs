#include <iostream>
#include <string>
#include <malloc.h>

using namespace std;

struct Node {
    string mark;
    Node *next = nullptr, *prev = nullptr;
    int *weightOfArcs;
    Node **relatedVertex;

    class Iterator {
    public:
        Node** current;

        Iterator() {
            current = nullptr;
        }

        explicit Iterator(Node **temp) {
            current = temp;
        }

        Iterator operator ++() {
            Iterator i = *this;
            current++;
            return i;
        }

        Iterator operator ++(int) {
            Iterator i = *this;
            current++;
            return i;
        }

        bool operator !=(Iterator other) {
            return current != other.current;
        }

        Node* operator *() {
            return *current;
        }
    };

    Iterator begin() {
        return Iterator(relatedVertex);
    }

    Iterator end() {
        return Iterator(relatedVertex + _msize(relatedVertex)/sizeof(Node*)); //костыль для винды
    }
};

class Graph {
public:
    Node *firstNode, *lastNode;
    int sizeOfGraph = 0;

    void addNode(const string& mark);
    void addArc(const int& weight, const string& mark1,const string& mark2);
    void deleteNode(const string& mark);
    void deleteArc(const string& mark1, const string& mark2);
    void changeMark(const string& oldMark, const string& newMark);
    void changeArc(const int& weight, const string& mark1, const string& mark2);

    class Iterator {
    public:
        Node* current;

        Iterator() {
            current = nullptr;
        }

        explicit Iterator(Node *temp) {
            current = temp;
        }

        Iterator operator ++() {
            Iterator i = *this;
            current = current->next;
            return i;
        }

        Iterator operator ++(int) {
            Iterator i = *this;
            current = current->next;
            return i;
        }

        bool operator !=(Iterator other) {
            return current != other.current;
        }

        Node* operator *() {
            return current;
        }
    };

    Iterator begin() {
        return Iterator(firstNode);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
};


void Graph::addNode(const string& mark) {
    short flag = 0;
    Node* check = firstNode;
    for(int i = 0; i < sizeOfGraph; ++i) {
        if(check->mark == mark)
            ++flag;
        check = check->next;
    }

    if (!flag) {
        Node* temp = new Node;
        temp->mark = mark;
        temp->weightOfArcs = new int[sizeOfGraph + 1];
        temp->relatedVertex = new Node*[sizeOfGraph + 1];
        for(int i = 0; i < sizeOfGraph + 1; ++i) {
            temp->weightOfArcs[i] = 0;
            temp->relatedVertex[i] = nullptr;
        }

        if(!sizeOfGraph) {
            firstNode = temp;
            lastNode = temp;
        } else {
            temp->prev = lastNode;
            lastNode->next = temp;
            lastNode = temp;
            Node *temp2 = firstNode;
            for(int i = 0; i < sizeOfGraph; ++i) {
                int* weightOfArcs_temp = new int[sizeOfGraph + 1];
                Node** relatedVertex_temp = new Node*[sizeOfGraph + 1];
                for (int j = 0; j < sizeOfGraph; ++j) {
                    weightOfArcs_temp[j] = temp2->weightOfArcs[j];
                    relatedVertex_temp[j] = temp2->relatedVertex[j];
                }
                weightOfArcs_temp[sizeOfGraph] = 0;
                relatedVertex_temp[sizeOfGraph] = nullptr;
                delete[] temp2->weightOfArcs;
                delete[] temp2->relatedVertex;
                temp2->weightOfArcs = weightOfArcs_temp;
                temp2->relatedVertex = relatedVertex_temp;
                temp2 = temp2->next;
            }
        }
        ++sizeOfGraph;
    } else {
        cout << "Mark is duplicated!\n";
    }
}

void Graph::addArc(const int& weight, const string& mark1, const string& mark2) {
    if(weight > 0) {
        short flag = 0, index;
        Node* check = firstNode, *find, *find2;
        for(int i = 0; i < sizeOfGraph; ++i) {
            if(check->mark == mark1) {
                flag++;
                find = check;
            }
            if(check->mark == mark2) {
                flag++;
                index = i;
                find2 = check;
            }
            check = check->next;
        }

        if(flag == 2) {
            if(!find->weightOfArcs[index]) {
                find->weightOfArcs[index] = weight;
                find->relatedVertex[index] = find2;
            }
            else
                cout << "Arc already exists!\n";
        } else {
            cout << "Didn't find nodes!\n";
        }
    } else {
        cout << "Arc must be >= 0!\n";
    }
}

void Graph::deleteNode(const string& mark) {
    short flag = 0;
    Node* check = firstNode;
    for(int i = 0; i < sizeOfGraph; ++i) {
        if(check->mark == mark) {
            if(check == firstNode) {
                firstNode = check->next;
            } else if (check == lastNode) {
                lastNode = check->prev;
            } else {
                check->prev->next = check->next;
                check->next->prev = check->prev;
            }
            delete check;
            flag++;
            Node *temp2 = firstNode;
            for(int j = 0; j < sizeOfGraph - 1; ++j) {
                int* weightOfArcs_temp = new int[sizeOfGraph];
                for (int k = 0; k < i; ++k) {
                    weightOfArcs_temp[k] = temp2->weightOfArcs[k];
                }

                for (int k = i; k < sizeOfGraph - 1; ++k) {
                    weightOfArcs_temp[k] = temp2->weightOfArcs[k + 1];
                }
                delete[] temp2->weightOfArcs;
                temp2->weightOfArcs = weightOfArcs_temp;
                temp2 = temp2->next;
            }

            --sizeOfGraph;
            break;
        }
        check = check->next;
    }
    if(flag) {
        cout << "done!\n";
    }
}

void Graph::deleteArc(const string& mark1, const string& mark2) {
    short flag = 0, index;
    Node* check = firstNode, *find;
    for(int i = 0; i < sizeOfGraph; ++i) {
        if(check->mark == mark1) {
            flag++;
            find = check;
        }
        if(check->mark == mark2) {
            flag++;
            index = i;
        }
        check = check->next;
    }

    if(flag == 2) {
        if(find->weightOfArcs[index])
            find->weightOfArcs[index] = 0;
        else
            cout << "There's no arc!\n";
    } else {
        cout << "Didn't find nodes!\n";
    }
}

void Graph::changeMark(const string& oldMark, const string& newMark) {
    short flag = 0;
    Node* check = firstNode, *find;
    for(int i = 0; i < sizeOfGraph; ++i) {

        if(check->mark == oldMark) {
            ++flag;
            find = check;
        }
        if(check->mark == newMark) {
            --flag;
            break;
        }
        check = check->next;
    }
    if(flag) {
        find->mark = newMark;
    } else {
        cout << "Didn't find old mark or duplicate!\n";
    }
}

void Graph::changeArc(const int& weight, const string& mark1, const string& mark2) {
    if(weight > 0) {
        short flag = 0, index;
        Node* check = firstNode, *find;
        for(int i = 0; i < sizeOfGraph; ++i) {
            if(check->mark == mark1) {
                flag++;
                find = check;
            }
            if(check->mark == mark2) {
                flag++;
                index = i;
            }
            check = check->next;
        }

        if(flag == 2) {
            find->weightOfArcs[index] = weight;
        } else {
            cout << "Didn't find nodes!\n";
        }
    } else {
        cout << "Arc must be >= 0!\n";
    }
}

int main() {
    Graph graph;
    string newMark = "a", newMark2 = "b", newMark3 = "c" , newMark4 = "d", newMark5 = "e";
    graph.addNode(newMark);
    graph.addNode(newMark2);
    graph.addNode(newMark3);
    graph.addNode(newMark4);
    graph.addNode(newMark5);

    /*for(int i = 0; i < 15; ++i)
    {
        newMark2 += i + 81;
        graph.addNode(newMark2);
    }*/

    graph.addArc(13, "a", "b");
    graph.addArc(7, "a", "d");

    graph.addArc(2, "b", "c");

    graph.addArc(3, "c", "a");
    graph.addArc(3, "c", "e");

    graph.addArc(8, "d", "a");
    graph.addArc(2, "d", "b");
    graph.addArc(5, "d", "c");
    graph.addArc(9, "d", "e");

    graph.addArc(8, "e", "a");

    Node* temp2 = graph.firstNode;

    for(int i = 0; i < graph.sizeOfGraph; ++i) {
        cout << temp2->mark << endl;

        for(int j = 0; j < graph.sizeOfGraph; ++j) {
            if(temp2->relatedVertex[j]) {
                cout << temp2->relatedVertex[j]->mark << '(' << temp2->weightOfArcs[j] << ") ";
            } else {
                cout << "0 ";
            }
        }

        temp2 = temp2->next;
        cout << endl;
    }

    cout << endl;

    graph.deleteArc("a", "b");
    graph.deleteArc("d", "e");

    graph.addArc(13, "a", "b");
    graph.addArc(9, "d", "e");

    graph.changeMark("a", "AAA");

    graph.changeArc(100, "AAA", "b");

    for(Graph::Iterator i = graph.begin(); i != graph.end(); ++i) {
        cout << (*i)->mark << endl;
        int flag = 0;
        for(Node::Iterator j = (*i)->begin(); j != (*i)->end(); ++j) {
            if((*j)) {
                cout << (*j)->mark << '(' << (*i)->weightOfArcs[flag] << ") ";
            } else {
                cout << "0 ";
            }
            flag++;
        }
        cout << endl;
    }
}

