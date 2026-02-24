#ifndef RG_GRAPH_H
#define RG_GRAPH_H

#include "core/types.h"

/* Spec states we must always have upper bounds on EVERYTHING */
#define RG_GRAPH_MAX_NODES 32U

/* Forward declaration for graph struct, we define it immediately after node struct below */
typedef struct RG_Graph RG_Graph;

typedef bool8 (*RG_NodeFn)(RG_Graph* graph, void* user_data);

typedef struct {
  const char*   name;
  RG_NodeFn     init;
  RG_NodeFn     update;
  RG_NodeFn     shutdown;
  void*         user_data;          // Note: This sacrifices type safety for generality
  bool8         active;
} RG_Node;

struct RG_Graph {
  RG_Node       nodes[RG_GRAPH_MAX_NODES];
  u32           node_count;
  bool8         running;
};

void  rg_graph_init     (RG_Graph* graph);
bool8 rg_graph_add_node (RG_Graph* graph, RG_Node node);
bool8 rg_graph_start    (RG_Graph* graph);
bool8 rg_graph_update   (RG_Graph* graph);
void  rg_graph_shutdown (RG_Graph* graph);

#endif /* RG_GRAPH_H */
