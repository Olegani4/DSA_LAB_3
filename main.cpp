#include <iostream>
#include "Graph.h"

int main() {
    /* Assigment 1 */
    Graph graph1 = *new Graph("./asoiaf-books/asoiaf-book3-nodes.csv",
                              "./asoiaf-books/asoiaf-book3-edges.csv");
    graph1.readNodesEdges();

    Graph graph2 = *new Graph("./asoiaf-books/asoiaf-book5-nodes.csv",
                              "./asoiaf-books/asoiaf-book5-edges.csv");
    graph2.readNodesEdges();


    /* Assigment 3 */
    graph1.compareWithGraph(graph2);


    /* Assigment 4 */
    graph1.findNCharsBiggestWeight(20);
    graph1.findNCharsSmallestWeight(30);


    /* Assigment 2 */
    // Edge '705' is from "asoiaf-book3-edges.csv"
    std::cout << "\n\n >>> Edge before removal | ";
    std::cout << "Source: " << graph1.getEdges(705).getSource()
              << "; Target: " << graph1.getEdges(705).getTarget() << ".\n";
    graph1.removeEdge("Jon-Snow", "Samwell-Tarly");
    std::cout << " >>> Edge after removal | ";
    std::cout << "Source: " << graph1.getEdges(705).getSource()
              << "; Target: " << graph1.getEdges(705).getTarget() << ".\n";


    return 0;
}
