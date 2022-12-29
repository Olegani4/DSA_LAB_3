#include <iostream>
#include <fstream>
#include "Node_Edge.h"

class Graph {
private:
    Node *nodes = new Node[1];
    long long unsigned int nodesNumber = 0;

    Edge *edges = new Edge[1];
    long long unsigned int edgesNumber = 0;

    std::string nodesFileName, edgesFileName;


    long long unsigned int findEdgeIndex(const std::string &source, const std::string &target) {
        for (auto i = 0; i < edgesNumber; i++)
            if (edges[i].getSource() == source)
                if (edges[i].getTarget() == target)
                    return i;
    }

public:
    Graph(std::string nodesFileName, std::string edgesFileName) {
        this->nodesFileName = std::move(nodesFileName);
        this->edgesFileName = std::move(edgesFileName);
    }

    Node getNodes(unsigned int i) {
        return nodes[i];
    }

    Edge getEdges(unsigned int i) {
        return edges[i];
    }

    long long unsigned int getNodesNumber() {
        return nodesNumber;
    }

    long long unsigned int getEdgesNumber() {
        return edgesNumber;
    }

    void addNode(const Node &newNode) {
        if (nodesNumber == 0) {
            nodes[0] = newNode;
            nodesNumber++;
        } else {
            Node newNodes[nodesNumber + 1];
            for (auto i = 0; i < nodesNumber; i++) {
                newNodes[i] = nodes[i];
            }
            newNodes[sizeof(newNodes) / sizeof(newNodes[0]) - 1] = newNode;
            nodesNumber++;

            delete[] nodes;

            nodes = new Node[sizeof(newNodes) / sizeof(newNodes[0])];
            for (auto i = 0; i < sizeof(newNodes) / sizeof(newNodes[0]); i++) {
                nodes[i] = newNodes[i];
            }
        }
    }

    void addEdge(const Edge &newEdge) {
        if (edgesNumber == 0) {
            edges[0] = newEdge;
            edgesNumber++;
        } else {
            Edge newEdges[edgesNumber + 1];
            for (auto i = 0; i < edgesNumber; i++) {
                newEdges[i] = edges[i];
            }
            newEdges[sizeof(newEdges) / sizeof(newEdges[0]) - 1] = newEdge;
            edgesNumber++;

            delete[] edges;

            edges = new Edge[sizeof(newEdges) / sizeof(newEdges[0])];
            for (auto i = 0; i < sizeof(newEdges) / sizeof(newEdges[0]); i++) {
                edges[i] = newEdges[i];
            }
        }
    }

    Node findNodeById(const std::string &id) {
        for (auto i = 0; i < nodesNumber; i++)
            if (nodes[i].getId() == id)
                return nodes[i];
        return nodes[0];
    }

    void readNodesEdges() {
        std::fstream fRead;
        std::string fLine;
        fRead.open(nodesFileName, std::ios::in);

        if (fRead.is_open()) {
            std::string id, label;

            while (std::getline(fRead, fLine)) {
                unsigned int i = 0;
                while (fLine[i] != ',') {
                    id += fLine[i];
                    i++;
                }
                i++;
                while (i != fLine.size()) {
                    label += fLine[i];
                    i++;
                }
                if (id != "Id") {
                    Node tempNode = *new Node(id, label);
                    addNode(tempNode);
                }
                id = "";
                label = "";
            }

            fLine = "";
            fRead.close();
        }


        fRead.open(edgesFileName, std::ios::in);
        if (fRead.is_open()) {
            std::string source, target, type, weight, book;

            while (std::getline(fRead, fLine)) {
                unsigned int i = 0;
                while (fLine[i] != ',') {
                    source += fLine[i];
                    i++;
                }
                i++;
                while (fLine[i] != ',') {
                    target += fLine[i];
                    i++;
                }
                i++;
                while (fLine[i] != ',') {
                    type += fLine[i];
                    i++;
                }
                i++;
                while (fLine[i] != ',') {
                    weight += fLine[i];
                    i++;
                }
                i++;
                while (i != fLine.size()) {
                    book += fLine[i];
                    i++;
                }

                if (source != "Source") {
                    Edge tempEdge = *new Edge(source, target, type, weight, book);
                    addEdge(tempEdge);
                }
                source = "";
                target = "";
                type = "";
                weight = "";
                book = "";
            }

            fLine = "";
            fRead.close();
        }
        for (auto i = 0; i < edgesNumber; i++) {
            edges[i].assignRef(findNodeById(edges[i].getSource()));
            edges[i].assignRef(findNodeById(edges[i].getTarget()));
        }
    }

    void removeEdge(const std::string &source, const std::string &target) {
        if (edgesNumber == 1) {
            edges[0] = *new Edge();
            edgesNumber--;
        } else if (edgesNumber != 0) {
            auto edgeIndex = findEdgeIndex(source, target);
            Edge newEdges[edgesNumber - 1];
            edgesNumber--;
            for (auto i = 0; i < edgeIndex; i++)
                newEdges[i] = edges[i];
            for (auto i = edgeIndex; i < edgesNumber; i++)
                newEdges[i] = edges[i + 1];

            delete[] edges;

            edges = new Edge[sizeof(newEdges) / sizeof(newEdges[0])];
            for (auto i = 0; i < sizeof(newEdges) / sizeof(newEdges[0]); i++)
                edges[i] = newEdges[i];
        }
    }

    void compareWithGraph(Graph graph2) {
        long long unsigned int n = 1, k = 1;
        bool flagIs = false;

        std::cout << "\n >>> The graph with which was compared has such deceased characters:\n";
        for (auto i = 0; i < nodesNumber; i++) {
            for (auto j = 0; j < graph2.getNodesNumber(); j++) {
                if (graph2.getNodes(j).getId() == getNodes(i).getId()) {
                    flagIs = true;
                    break;
                }
            }
            if (!flagIs) {
                std::cout << n << ": " << getNodes(i).getLabel() << '\n';
                n++;
            }
            flagIs = false;
        }

        std::cout << "\n\n >>> The graph with which was compared has such new characters:\n";
        for (auto i = 0; i < graph2.getNodesNumber(); i++) {
            for (auto j = 0; j < nodesNumber; j++) {
                if (graph2.getNodes(i).getId() == getNodes(j).getId()) {
                    flagIs = true;
                    break;
                }
            }
            if (!flagIs) {
                std::cout << k << ": " << graph2.getNodes(i).getLabel() << '\n';
                k++;
            }
            flagIs = false;
        }
    }

    void findNCharsBiggestWeight(unsigned int n) {
        long long unsigned int bwIndex;
        Edge tempEdges[edgesNumber];
        for (auto i = 0; i < edgesNumber; i++)
            tempEdges[i].setWeight(edges[i].getWeight());

        int weightVal = 0;
        unsigned int loops = 0;
        std::cout << "\n\n >>> Top " << n << " characters with biggest cumulative weight:\n";
        while (loops < n) {
            for (auto i = 0; i < getEdgesNumber(); i++)
                if (weightVal < getEdges(i).getWeight()) {
                    weightVal = getEdges(i).getWeight();
                    bwIndex = i;
                }
            loops++;
            std::cout << loops << ") " << "Source: " << edges[bwIndex].getSource() << "; Target: "
                      << edges[bwIndex].getTarget()
                      << "; Weight: " << edges[bwIndex].getWeight() << ".\n";
            edges[bwIndex].setWeight(0);
            weightVal = 0;
        }

        for (auto i = 0; i < getEdgesNumber(); i++)
            edges[i].setWeight(tempEdges[i].getWeight());
    }

    void findNCharsSmallestWeight(unsigned int n) {
        int biggestWeightVal = 0;
        for (auto i = 0; i < getEdgesNumber(); i++)
            if (biggestWeightVal < getEdges(i).getWeight())
                biggestWeightVal = getEdges(i).getWeight();

        long long unsigned int bwIndex;
        Edge tempEdges[edgesNumber];
        for (auto i = 0; i < edgesNumber; i++)
            tempEdges[i].setWeight(edges[i].getWeight());
        int weightVal;

        unsigned int loops = 0;
        std::cout << "\n\n >>> Top " << n << " characters with smallest cumulative weight:\n";
        while (loops < n) {
            for (auto i = 0; i < getEdgesNumber(); i++)
                if (weightVal > getEdges(i).getWeight()) {
                    weightVal = getEdges(i).getWeight();
                    bwIndex = i;
                }
            loops++;
            std::cout << loops << ") " << "Source: " << edges[bwIndex].getSource() << "; Target: "
                      << edges[bwIndex].getTarget()
                      << "; Weight: " << edges[bwIndex].getWeight() << ".\n";
            edges[bwIndex].setWeight(biggestWeightVal);
            weightVal = biggestWeightVal;
        }
        for (auto i = 0; i < getEdgesNumber(); i++)
            edges[i].setWeight(tempEdges[i].getWeight());

    }
};