#include <iostream>
#include <string>

using namespace std;

struct Node {
    string mark;
    Node *next = nullptr, *prev = nullptr;
    int *weightOfArcs;
};

class Graph {
public:
    Node *firstNode, *lastNode;
    int sizeOfGraph = 0;

    void addNode(string mark);
    void addArc(const int& weight, string mark1, string mark2);
    void deleteNode(string mark);
    void deleteArc(string mark1, string mark2);
    void changeMark(string oldMark, string newMark);
    void changeArc(const int& weight, string mark1, string mark2);
};

void Graph::addNode(string mark) {
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
        for(int i = 0; i < sizeOfGraph + 1; ++i) {
            temp->weightOfArcs[i] = 0;
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
                for (int j = 0; j < sizeOfGraph; ++j) {
                    weightOfArcs_temp[j] = temp2->weightOfArcs[j];
                }
                weightOfArcs_temp[sizeOfGraph] = 0;
                delete[] temp2->weightOfArcs;
                temp2->weightOfArcs = weightOfArcs_temp;
                temp2 = temp2->next;
            }
        }
        ++sizeOfGraph;
    } else {
        cout << "Mark is duplicated!\n";
    }
}

void Graph::addArc(const int& weight, string mark1, string mark2) {
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
            if(find->weightOfArcs[index] == 0)
                find->weightOfArcs[index] = weight;
            else
                cout << "Arc already exists!\n";
        } else {
            cout << "Didn't find nodes!\n";
        }
    } else {
        cout << "Arc must be >= 0!\n";
    }
}

void Graph::deleteNode(string mark) {
    short flag;
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

int main() {
    Graph graph;
    string newMark = "a", newMark2 = "b", newMark3 = "c" , newMark4 = "d", newMark5 = "e";
    graph.addNode(newMark);
    graph.addNode(newMark2);
    graph.addNode(newMark3);
    graph.addNode(newMark4);
    graph.addNode(newMark5);

    /*for(int i = 0; i < 10; ++i)
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
            cout << temp2->weightOfArcs[j] << ' ';
        }

        temp2 = temp2->next;
        cout << endl;
    }

    //graph.deleteNode("a");
    //graph.deleteNode("b");

    Node* temp = graph.firstNode;

    for(int i = 0; i < graph.sizeOfGraph; ++i) {

        cout << temp->mark << endl;

        for(int j = 0; j < graph.sizeOfGraph; ++j) {
            cout << temp->weightOfArcs[j] << ' ';
        }

        temp = temp->next;
        cout << endl;
    }

}

