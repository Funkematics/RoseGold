#ifndef RG_PLATFORM_H
#define RG_PLATFORM_H

#include "core/types.h"
#include "graph/graph.h"

typedef struct {
  const char* title;
  i32         width;
  i32         height;
} RG_WindowConfig;

typedef struct {
  void*           window;
  RG_WindowConfig config;
  bool8           should_close;
} RG_PlatformState;

RG_Node rg_platform_make_node(RG_PlatformState* state, RG_WindowConfig config);

bool8 rg_platform_should_close(const RG_PlatformState* state);

#endif /* RG_PLATFORM_H */
