#ifndef TREEDUMP_H_INCLUDED
#define TREEDUMP_H_INCLUDED

int graph_dump(const Tree* tree);
void node_graph_dump(Node* node, FILE* dotfile);
void edge_graph_dump(Node* node, FILE* dotfile);


#endif // TREEDUMP_H_INCLUDED
