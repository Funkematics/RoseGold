#include "platform/platform.h"
#include "core/assert.h"
#include <stdio.h>
#include <GLFW/glfw3.h>


static bool8 platform_init(RG_Graph* graph, void* user_data)
{
  RG_ASSERT(graph != RG_NULL);
  RG_ASSERT(user_data != RG_NULL);

  RG_PlatformState* state = (RG_PlatformState*)user_data;

  if (glfwInit() != GLFW_TRUE) {
    fprintf(stderr, "[PLATFORM] glfwInit failed\n");
    return RG_FALSE;
  }

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
  glfwWindowHint(GLFW_RESIZEABLE, GLFW_FALSE);

  GLFWwindow* window = glfwCreateWindow(
    state->config.width,
    state->config.height,
    state->config.title,
    RG_NULL,           // This sets windowed mode when null
    RG_NULL            // This sets no context sharing when null
  );

  if(window == RG_NULL) {
    fprintf(stderr, "[PLATFORM] glfwCreateWindow failed\n");
    glfwTerminate(); 
    return RG_FALSE; //Start exiting gracefully (hopefully)
  }

  state->window = (void*)window;
  state->should_close = RG_FALSE;

  return RG_TRUE;
}


static bool8 platform_update(RG_Graph* graph, void* user_data)
{
  RG_ASSERT(graph != NULL);
  RG_ASSERT(user_data != RG_NULL);

  RG_PlatformState* state   = (RG_PlatformState*)user_data;
  GLFWWindow*       window  = (GLFWwindow*)state->window;

  RG_ASSERT(window != RG_NULL);

  glfwPollEvents();

  if (glfwWindowShouldClose(window) == GLFW_TRUE) {
    state->should_close = RG_TRUE;
    graph->running      = RG_FALSE;
  }
  return RG_TRUE;
}


static bool8 platform_shutdown(RG_Graph* graph, void* user_data)
{
  RG_ASSERT(graph != RG_NULL);
  RG_ASSERT(user_data != RG_NULL);

  RG_PlatformState* state = (RG_PlatformState*)user_data;

  if (state->window != RG_NULL) {
    glfwDestroyWindow((GLFWwindow*)state->window);
    state->window = RG_NULL;
  }

  glfwTerminate();
  return RG_TRUE;
}


RG_Node rg_platform_make_node(RG_PlatformState* state, RG_WindowConfig config)
{
  RG_ASSERT(state != RG_NULL);
  RG_ASSERT(config.width > 0);

  state->config         = config;
  state->window         = RG_NULL;
  state->should_close   = RG_FALSE;       //Always keep this false, rg_graph_add_node updates this. 

  RG_Node node;
  node.name             = "platform";
  node.init             = platform_init;
  node.update           = platform_update;
  node.shutdown         = platform_shutdown;
  node.user_data        = (void*)state;
  node.active           = RG_FALSE;

  return node;
}

bool8 rg_platform_should_close(const RG_PlatformState* state)
{
  RG_ASSERT(state != RG_NULL);
  RG_ASSERT(state->should_close == RG_TRUE || state->should_close == RG_FALSE);

  return state->should_close;
}
