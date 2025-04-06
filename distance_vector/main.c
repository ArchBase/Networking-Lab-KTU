#include <stdio.h>

#define INF 9999  // Representation of infinity
#define MAX_NODES 10

int nodes;  // Number of routers (nodes)
int cost[MAX_NODES][MAX_NODES];  // Cost matrix
int distance[MAX_NODES][MAX_NODES];  // Distance table

// Function to implement Distance Vector Routing
void distanceVectorRouting() {
    int i, j, k;
    
    // Initialize distance table with cost matrix
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            distance[i][j] = cost[i][j];
        }
    }

    // Apply Bellman-Ford Algorithm
    for (k = 0; k < nodes - 1; k++) { // Iterate n-1 times
        for (i = 0; i < nodes; i++) { // Each router
            for (j = 0; j < nodes; j++) { // Each destination
                for (int via = 0; via < nodes; via++) { // Each possible path
                    if (distance[i][via] + distance[via][j] < distance[i][j]) {
                        distance[i][j] = distance[i][via] + distance[via][j];
                    }
                }
            }
        }
    }

    // Print the final distance vector table
    printf("\nFinal Distance Vector Table:\n");
    for (i = 0; i < nodes; i++) {
        printf("Router %d: ", i + 1);
        for (j = 0; j < nodes; j++) {
            if (distance[i][j] == INF)
                printf(" INF ");
            else
                printf(" %d ", distance[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int i, j;

    // Get the number of nodes
    printf("Enter the number of routers: ");
    scanf("%d", &nodes);

    // Get the cost adjacency matrix
    printf("Enter the cost matrix (use %d for infinity):\n", INF);
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            scanf("%d", &cost[i][j]);

            // If there is no direct connection, set to infinity
            if (i != j && cost[i][j] == 0) {
                cost[i][j] = INF;
            }
        }
    }

    // Run the Distance Vector Routing Algorithm
    distanceVectorRouting();

    return 0;
}
