#include <string>
#include <utility>

class Node {
private:
    std::string id, label;

public:
    Node(std::string id, std::string label) {
        this->id = std::move(id);
        this->label = std::move(label);
    }

    Node() = default;

    std::string getId() {
        return id;
    }

    std::string getLabel() {
        return label;
    }

};

class Edge {
private:
    std::string source, target, type, weight, book;

    Node sourceNode;
    Node targetNode;
    bool firstRef = false;

public:
    Edge(std::string source, std::string target, std::string type, std::string weight, std::string book) {
        this->source = std::move(source);
        this->target = std::move(target);
        this->type = std::move(type);
        this->weight = std::move(weight);
        this->book = std::move(book);
    }

    Edge() = default;

    std::string getSource() {
        return source;
    }

    std::string getTarget() {
        return target;
    }

    int getWeight() {
        return std::stoi(weight);
    }

    std::string getType() {
        return type;
    }

    std::string getBook() {
        return book;
    }


    void setWeight(int weightNum) {
        weight = std::to_string(weightNum);
    }

    Node getSourceNode() {
        return sourceNode;
    }

    Node getTargetNode() {
        return targetNode;
    }

    void assignRef(const Node& nodeRef) {
        if (!firstRef) {
            sourceNode = nodeRef;
            firstRef = true;
        } else {
            targetNode = nodeRef;
        }
    }
};