#include "graph/graph.h"
#include "core/assert.h"
#include <string.h>
#include <stdio.h>

void rg_graph_init(RG_Graph* graph)
{
  RG_ASSERT(graph != RG_NULL);
  memset(graph, 0, sizeof(RG_Graph));
  graph->running = RG_FALSE;

  RG_ASSERT(graph->node_count == 0U);
}

bool8 rg_graph_add_node(RG_Graph* graph, RG_Node node)
{
  RG_ASSERT(graph != RG_NULL);
  RG_ASSERT(node.name != RG_NULL);

  if (graph->node_count >= RG_GRAPH_MAX_NODES) {
    fprintf(stderr, "[GRAPH] Cannot add '%s' : graph is full\n", node.name);
    return RG_FALSE;
  }

  node.active = RG_TRUE;
  graph->nodes[graph->node_count] = node;
  graph->node_count++;

  return RG_TRUE;
}

static void graph_shutdown_range(RG_Graph* graph, u32 count)
{
  RG_ASSERT(graph != RG_NULL);
  RG_ASSERT(count <= graph->node_count);

  u32 i;
  for (i = count; i > 0U; i--) {
    RG_Node* node = &graph->nodes[i - 1U];

    if (node->active != RG_TRUE || node->shutdown == RG_NULL) { continue; }
    (void)node->shutdown(graph, node->user_data);
  }
}

bool8 rg_graph_start(RG_Graph* graph)
{
  RG_ASSERT(graph != RG_NULL);
  RG_ASSERT(graph->node_count <= RG_GRAPH_MAX_NODES);

  u32 i;
  for (i = 0U; i < graph->node_count; i++) {
    RG_Node* node = &graph->nodes[i];

    if (node->active != RG_TRUE || node->init == RG_NULL) { continue; }
    //Check every non-void return
    bool8 ok = node->init(graph, node->user_data);
    if (ok != RG_TRUE) {
      fprintf(stderr, "[GRAPH] Node '%s' init failed\n", node->name);
      graph_shutdown_range(graph, i); //go through nodes backwards, clean up memory
      return RG_FALSE;
    }
  }
  graph->running = RG_TRUE;
  return RG_TRUE;
}

bool8 rg_graph_update(RG_Graph* graph)
{
  RG_ASSERT(graph != RG_NULL);
  RG_ASSERT(graph->running == RG_TRUE);

  u32 i;

  for (i = 0U; i < graph->node_count; i++) {
    RG_Node* node = &graph->nodes[i];

    if (node->active != RG_TRUE || node->update == RG_NULL) { continue; }

    bool8 ok = node->update(graph, node->user_data);
    if(ok != RG_TRUE) {
      fprintf(stderr, "[GRAPH] Node '%s' update failed\n", node->name);
      graph->running = RG_FALSE;
      return RG_FALSE;
    }
  }
  return RG_TRUE;
}

void rg_graph_shutdown(RG_Graph* graph)
{
  RG_ASSERT(graph != RG_NULL);
  RG_ASSERT(graph->node_count <= RG_GRAPH_MAX_NODES);

  graph_shutdown_range(graph, graph->node_count);
  graph->running = RG_FALSE;
}

