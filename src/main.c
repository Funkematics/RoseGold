#include "graph/graph.h"
#include "platform/platform.h"
#include "core/assert.h"
#include <stdio.h>

int main(void)
{
  RG_Graph graph;
  RG_PlatformState platform_state;

  rg_graph_init(&graph);

  RG_WindowConfig win_cfg;
  win_cfg.title   = "RoseGold";
  win_cfg.width   = 1280;
  win_cfg.height  = 720;

  RG_Node platform_node = rg_platform_make_node(&platform_state, win_cfg);

  bool8 ok = rg_graph_add_node(&graph, platform_node);
  RG_ASSERT(ok == RG_TRUE);

  ok = rg_graph_start(&graph);
  if (ok != RG_TRUE) {
    fprintf(stderr, "[MAIN] Graph failed to start\n");
    return 1;
  }

  while (graph.running == RG_TRUE) {
    ok = rg_graph_update(&graph);
    if (ok != RG_TRUE) { break; }
  }

  // Teardown
  rg_graph_shutdown(&graph);

  printf("[MAIN] Clean shutdown.\n");
  return 0;
}
