#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#include "state.h"
#include "list.h"
#include "node.h"
#include "io.h"

unsigned int nodesExpanded;
unsigned int nodesGenerated;
unsigned int solutionLength;
double runtime;

//Instancia das solucoes por meio de busca, nesse caso em largura e em A*
SolutionPath* BFS_search(State *, State *);
SolutionPath* AStar_search(State *, State *);

int main(void) {

    State initial;           //estado inicial
    State goalState;         //estado final
    goalStateF(&goalState);

    //solution path of each search method
    SolutionPath *bfs;
    SolutionPath *aStar;

    //digitar o estado inicial
    printf("estado inicial [][]:\n");
    inputState(&initial);

    printf("estado inicial[][]:\n");
    printBoard(initial.board);
//
    printf("estado final:\n");
    printBoard(goalState.board);

    //Busca A*
    aStar = AStar_search(&initial, &goalState);
    printf("\n-------------------------- ALGORITMO A* --------------------------\n");
    printSolution(aStar);

    //reset the counters
    nodesExpanded = 0;
    nodesGenerated = 0;
    solutionLength = 0;
    runtime = 0;

    //Busca em Largura - BFS
    bfs = BFS_search(&initial, &goalState);
    printf("\n------------------------- AlGORITMO BFS --------------------------\n");
    printSolution(bfs);

    //Libertar
    destroySolution(&bfs);
    destroySolution(&aStar);

    return 0;
}

SolutionPath* BFS_search(State *initial, State *goal) {
    NodeList *queue = NULL;
    NodeList *children = NULL;
    Node *node = NULL;

    clock_t start = clock();

    //inicializa a queue com o nó raiz da arvore de busca 
    pushNode(createNode(0, manhattanDist(initial, goal), initial, NULL), &queue);
    Node *root = queue->head->currNode;

    //enquando houver um nó na queue para expandir
    while(queue->nodeCount > 0) {

        node = popNode(&queue);

        //ise for o objectivo final
        if(statesMatch(node->state, goal))
            break;

        //caso contrario ira espandir e incrementar
        children = getChildren(node, goal);
        ++nodesExpanded;

        //adiciona o no filho a queue
        pushList(&children, queue);
    }

    runtime = (double)(clock() - start) / CLOCKS_PER_SEC;

    SolutionPath *pathHead = NULL;
    SolutionPath *newPathNode = NULL;

    while(node) {
        newPathNode = malloc(sizeof(SolutionPath));
        newPathNode->action = node->state->action;
        newPathNode->next = pathHead;
        pathHead = newPathNode;

        //incrementa o nr de movimentos
        ++solutionLength;
        node = node->parent;
    }

    --solutionLength; //uncount the root node

    //desaloca a arvore gerada
    destroyTree(root);

    return pathHead;
}

SolutionPath* AStar_search(State *initial, State *goal) {
    NodeList *queue = NULL;
    NodeList *children = NULL;
    Node *node = NULL;

    clock_t start = clock();

    //Inicializa o No da arvore de busca
    pushNode(createNode(0, manhattanDist(initial, goal), initial, NULL), &queue);
    Node *root = queue->head->currNode; //for deallocating generated tree

    //Enquanto existir um nó para ser expandido
    while(queue->nodeCount > 0) {
        node = popNode(&queue);
        if(statesMatch(node->state, goal))
            break;
        children = getChildren(node, goal);
        ++nodesExpanded;
        pushListInOrder(&children, queue);
    }

    runtime = (double)(clock() - start) / CLOCKS_PER_SEC;


    SolutionPath *pathHead = NULL;
    SolutionPath *newPathNode = NULL;

    while(node) {
        newPathNode = malloc(sizeof(SolutionPath));
        newPathNode->action = node->state->action;
        newPathNode->next = pathHead;
        pathHead = newPathNode;

        //incrementa o nr de movimento e passa para o proximo no
        ++solutionLength;
        node = node->parent;
    }

    --solutionLength; //nao conta o numero de movimentos

    //desaloca a arvore gerada
    destroyTree(root);

    return pathHead;
}
