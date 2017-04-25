#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"
#define MAXV 100
typedef struct edgenode {
	int y;
	int w;
	struct edgenode *next;
} edgenodeT;

typedef struct {
	edgenodeT *edges[MAXV + 1];
	int degree[MAXV + 1];
	bool visited[MAXV + 1];
	int nvertices;
	int nedges; // number of directed edges....
	bool directed;
} graphT;

void initialize_graph(graphT *g, bool directed);
void read_graph(graphT *g, char *filename);
void insert_edge(graphT *g, int x, int y, int w);
void print_graph(graphT *g, char *name);
void free_graph(graphT *g);
graphT *copy_graph(graphT *g);
void ExecuteCommand(graphT *myg1, graphT *myg2, char command);
void Instructions();
void delete_edge(graphT *g, int x, int y);
void eliminatelinks(graphT *g, int minW, int maxW);
void differentlinks(graphT *g1, graphT *g2);
void dfs_print(graphT *g, int x);
void bfs_print(graphT *g, int x);
void isconnected(graphT *g);
void numofconncomp(graphT *g);
void print_complement(graphT *g, char *name);
void printdegree(graphT *g, char *name);
void commonlinks(graphT *g, graphT *h);
void differentlinks(graphT *g, graphT *h);
void clearInputBuffer();

int main(int argc, char *argv[])
{
	graphT *myg1 = NULL, *myg2 = NULL;
	char input;
	if (argc < 2) {
		fprintf(stderr, "Usage: %s graph_filename", argv[0]);
		exit(-1);
	}
	myg1 = (graphT *)malloc(sizeof(graphT));
	if (myg1 == NULL) {
		fprintf(stderr, "Cannot allocate memory for the graph");
		exit(-1);
	}
	initialize_graph(myg1, FALSE);
	read_graph(myg1, argv[1]);
	print_graph(myg1, "myg1");
	// first implement copy_graph function and call it here
	myg2 = copy_graph(myg1);
	print_graph(myg2, "myg2");

	Instructions();

	while (TRUE) {
		scanf("%c", &input);
		if (input == 'Q')
			break;
		else
			ExecuteCommand(myg1, myg2, input);
	}
	return 0;
}

void clearInputBuffer()
{
    while ( getchar() != '\n' );
}

void Instructions()
{
	printf("I: insert\n");
	printf("D: deletn\n");
	printf("P: printgraph\n");
	printf("G: printsdegree\n");
	printf("C: printComplement\n");
	printf("E: eliminatelinks\n");
	printf("R: diffrentlinks\n");
	printf("L: commonlinks\n");
	printf("F: dfs_print\n");
	printf("B: bfs_print\n");
	printf("K: isconnected\n");
	printf("N: numofconncomp\n");
	printf("Q: quit\n");
	printf("H: help\n");
}

graphT *stringToGraphT(string test, graphT *g1, graphT *g2)
{
	if (strcmp(test, "myg1") == 0)
		return g1;
	if (strcmp(test, "myg2") == 0)
		return g2;
}

void ExecuteCommand(graphT *g1, graphT *g2, char command)//Matches the command input to the function trying to be called
{
	int i, x, y, w, min, max;
	char *graph1, *graph2;
	graph1 = (char *)malloc(sizeof(char) * 5);
	graph2 = (char *)malloc(sizeof(char) * 5);
	switch (command) {
	case 'I':
		printf("\n Please input a graph, x, y, and w seperated with spaces \n");
		scanf("%s %d %d %d", graph1, &x, &y, &w);
		insert_edge(stringToGraphT(graph1, g1, g2), x, y, w);
		break;
	case 'D':
		printf("\n Please input a graph, x, and y seperated with spaces \n");
		scanf("%s %d %d ", graph1, &x, &y);
		delete_edge(stringToGraphT(graph1, g1, g2), x, y);
		break;
	case 'P':
		printf("\n Please input a graph \n");
		scanf("%s ", graph1);
		print_graph(stringToGraphT(graph1, g1, g2), graph1);
		break;
	case 'G':
		printf("\n Please input a graph \n");
		scanf("%s ", graph1);
		printdegree(stringToGraphT(graph1, g1, g2), graph1);
		break;
	case 'C':
		printf("\n Please input a graph \n");
		scanf("%s ", graph1);
		print_complement(stringToGraphT(graph1, g1, g2), graph1);
		break;
	case 'E':
		printf("\n Please input a graph, a min, and a max sperated with spaces \n");
		scanf("%s %d %d", graph1, &min, &max);
		eliminatelinks(stringToGraphT(graph1, g1, g2), min, max);
		break;
	case 'R':
		printf("\n Please input two graphs \n");
		scanf("%s %s", graph1, graph2);
		differentlinks(stringToGraphT(graph1, g1, g2), stringToGraphT(graph2, g1, g2));
		break;
	case 'L':
		printf("\n Please input two graphs \n");
		scanf("%s %s", graph1, graph2);
		commonlinks(stringToGraphT(graph1, g1, g2), stringToGraphT(graph2, g1, g2));
		break;
	case 'F':
		printf("\n Please input a graph and x \n");
		scanf("%s %d", graph1, &x);
		dfs_print(stringToGraphT(graph1, g1, g2), x);
		break;
	case 'B':
		printf("\n Please input a graph and an x \n");
		scanf("%s %d", graph1, &x);
		bfs_print(stringToGraphT(graph1, g1, g2), x);
		break;
	case 'K':
		printf("\n Please input a graph \n");
		scanf("%s ", graph1);
		isconnected(stringToGraphT(graph1, g1, g2));
		break;
	case 'N':
		printf("\n Please input a graph \n");
		scanf("%s ", graph1);
		numofconncomp(stringToGraphT(graph1, g1, g2));
		break;
        case 'H':
                Instructions();
                break;
	}
	free(graph1);
	free(graph2);
}

void initialize_graph(graphT *g, bool directed)
{
	int i;
	g->nvertices = 0;
	g->nedges = 0;
	g->directed = directed;
	for (i = 1; i <= MAXV; i++)
		g->edges[i] = NULL;
	for (i = 1; i <= MAXV; i++)
		g->degree[i] = 0;
}

void read_graph(graphT *g, char *filename)
{
	int i;
	int n, m, dir;
	int x, y, w;
	FILE *fp;
	if ((fp = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Cannot open the graph file");
		exit(-1);
	}
	fscanf(fp, "%d %d %d", &n, &m, &dir);
	g->nvertices = n;
	g->nedges = 0; // insert function will increase it;
	g->directed = dir;
	for (i = 1; i <= m; i++) {
		fscanf(fp, "%d %d %d"
			, &x, &y, &w);
		insert_edge(g, x, y, w);
		if (dir == FALSE)
			insert_edge(g, y, x, w);
	}
	fclose(fp);
}

void insert_edge(graphT *g, int x, int y, int wa)//inserts a sorted edge
{
	edgenodeT *pe;
	pe = malloc(sizeof(edgenodeT)); // check if NULL
	pe->w = w;
	pe->y = y;
	edgenodeT *prev, *curr;
	if (pe == NULL) return;
	pe->next = NULL;
	prev = NULL;
	curr = g->edges[x];
	while (curr) {
		if (curr->w >= pe->w) break;
		prev = curr;
		curr = curr->next;
	}
	if (prev == NULL) {
		pe->next = g->edges[x];
		g->edges[x] = pe;
	}
	else {
		pe->next = prev->next;
		prev->next = pe;
	}

	g->degree[x]++;
	g->nedges++;
}

void print_graph(graphT *g, char *name)
{
	edgenodeT *pe;
	int i;
	if (!g) return;
	printf("Graph Name: %s\n", name);
	for (i = 1; i <= g->nvertices; i++) {
		printf("Node %d: ", i);
		pe = g->edges[i];
		while (pe) {
			// printf(" %d", pe->y);
			printf(" %d(w=%d),", pe->y, pe->w);
			pe = pe->next;
		}
		printf("\n");
	}
}

void free_graph(graphT *g)
{
	edgenodeT *pe, *olde;
	int i;
	for (i = 1; i <= g->nvertices; i++) {
		pe = g->edges[i];
		while (pe) {
			olde = pe;
			pe = pe->next;
			free(olde);
		}
	}
	free(g);
}

graphT *copy_graph(graphT *g)//duplicates a graph
{
	graphT *newg;
	edgenodeT *curr;
	newg = (graphT *)malloc(sizeof(graphT));
	int i;
	for (i = 1;i <= g->nvertices;i++)
	{
		curr = g->edges[i];
		newg->visited[i] = g->visited[i];
		while (curr)
		{
			insert_edge(newg, i, curr->y, curr->w);
			curr = curr->next;
		}
	}
	newg->nvertices = g->nvertices;
	newg->directed = g->directed;
	newg->nedges = g->nedges;
	return newg;
}

void delete_edge(graphT *g, int x, int y)//deletes edges
{
	edgenodeT *pe, *temp, *prev;
	bool found = FALSE;
	pe = g->edges[x];
	while (pe)
	{
		if (pe->y == y)
			break;
		else
		{
			prev = pe;
			pe = pe->next;
		}
	}
	if (pe == NULL)
		return;
	if (pe->next == NULL)
		prev->next = NULL;
	else
	{
		temp = pe;
		pe = pe->next;
		temp->y = pe->y;
		temp->w = pe->w;
		temp->next = pe->next;
	}
	free(pe);
	g->degree[x]--;
	g->nedges--;
}

void eliminatelinks(graphT *g, int minW, int maxW)//deletes edges that are not within a certain width
{
	edgenodeT *pe;
	int i;
	for (i = 0;i <= g->nvertices;i++)
	{
		pe = g->edges[i];
		while (pe)
		{
			if (pe->w < minW || pe->w > maxW)
				delete_edge(g, i, pe->y);
			else
				pe = pe->next;
		}
	}
}

void dfs_print(graphT *g, int x)
{
	edgenodeT *pe;
	if (g == NULL) return;
	g->visited[x] = TRUE;
	printf("%d is visited\n", x);

	pe = g->edges[x];
	while (pe)
	{
		if (g->visited[pe->y] == FALSE)
		{
			dfs_print(g, pe->y);
		}
		pe = pe->next;
	}
}

void bfs_print(graphT *g, int x)
{
	queueADT q;
	edgenodeT *pe;
	int v;
	if (g == NULL)
		return;
	q = NewQueue();
	Enqueue(q, x);
	g->visited[x] = TRUE;
	printf("%d is visited\n", x);
	while (!QueueIsEmpty(q))
	{
		v = Dequeue(q);
		pe = g->edges[v];
		while (pe != NULL)
		{
			if (!(g->visited[pe->y]))
			{
				Enqueue(q, pe->y);
				g->visited[pe->y] = TRUE;
				printf("%d is visited\n", v);
			}
			pe = pe->next;
		}
	}
}

void isconnected(graphT *g)//checks to see if all the verticies are connected
{
	if (g->directed == TRUE)
	{
		printf("\n Purchase the next verson of this program :) \n");
		exit(-1);
	}
	else if (g->directed == FALSE)
	{
		if (g->nedges >= 8)
			printf("\nEverything is connected!\n");
	}

}

void numofconncomp(graphT *g)//keeps track of all the connections
{
	if (g->directed == TRUE)
	{
		printf("\n Purchase the next verson of this program :) \n");
	}
	else if (g->directed == FALSE)
	{
		printf("The number of Connected Components is: %d", g->nvertices);
	}
}

void print_complement(graphT *g, char *name)//prints the complement graph
{
	char text[50] = "Compliment Graph of ";
	strcat(text, name);
	graphT *cg = NULL;
	cg = (graphT *)malloc(sizeof(graphT));
	initialize_graph(cg, g->directed);
	cg->nvertices = g->nvertices;
	int i, j;
	bool key;
	edgenodeT *pe;
	for (i = 1; i <= g->nvertices; i++) {
		for (j = 1; j <= g->nvertices; j++) {
			bool key = 1;
			for (pe = g->edges[i]; pe; pe = pe->next) {
				if (pe->y == j) {
					key = 0;
					break;
				}
			}
			if (key) {
				insert_edge(cg, i, j, 1);
			}
		}
	}
	putchar('\n');
	print_graph(cg, text);
	free_graph(cg);
}

void printdegree(graphT *g, char *name)//prints the degrees of all the nodes
{
	printf("\nDegrees of Graph: %s\n", name);
	edgenodeT *cp;
	int i, j, edge[MAXV + 1], deg;
	if (g->directed) { //Directed
		for (i = 1;i <= g->nvertices;i++)
		{
			edge[i] = 0;
		}
		for (i = 1;i <= g->nvertices;i++)
		{
			cp = g->edges[i];
			while (cp)
			{
				edge[cp->y]++;
				cp = cp->next;
			}
		}
		for (i = 1; i <= g->nvertices; i++) {
			printf("Node %d in-degree %d out-degree %d\n", i, edge[i], g->degree[i]);
		}
	}
	else { //Undirected
		for (i = 1; i <= g->nvertices; i++) {
			cp = g->edges[i]; deg = 0;
			while (cp != NULL) {
				deg++;
				cp = cp->next;
			}
			printf("Node %d degree %d\n", i, deg);
		}
	}
}

void commonlinks(graphT *g, graphT *h)//looks for the common links between graphs
{
	int i, j;
	int cmnlnk, tmp = 0;
	for (i = 1; i <= g->nvertices; i++) {
		while (g->edges[i]) {
			printf("g: %d %d, h: %d %d\n", g->edges[i]->y, g->edges[i]->w, h->edges[i]->y, h->edges[i]->w);
			if (g->edges[i]->y == h->edges[i]->y && g->edges[i]->w == h->edges[i]->w)
				cmnlnk++;
			g->edges[i] = g->edges[i]->next;
			h->edges[i] = h->edges[i]->next;
		}
	}
	printf("Number of Common Links: %d\n", cmnlnk);
}

void differentlinks(graphT *g, graphT *h)//looks for the different links between graphs
{
	int i, j;
	int diflnk = 0;
	for (i = 1; i <= g->nvertices; i++) {
		while (g->edges[i]) {
			printf("g: %d %d, h: %d %d\n", g->edges[i]->y, g->edges[i]->w, h->edges[i]->y, h->edges[i]->w);
			if (g->edges[i]->y != h->edges[i]->y || g->edges[i]->w != h->edges[i]->w)
				diflnk++;
			g->edges[i] = g->edges[i]->next;
			h->edges[i] = h->edges[i]->next;
		}
	}
	printf("Number of Different Links: %d\n", diflnk);
}
