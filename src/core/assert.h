#ifndef RG_ASSERT_H
#define RG_ASSERT_H

#include <stdio.h>
#include <stdlib.h>

/* Prints file, line number, failed expression and abort on failure */
#define RG_ASSERT(expr)                   \
  do {                                    \
    if (!(expr)) {                       \
      fprintf(stderr,                     \
        "[ASSERT FAIL] %s:%d  expr %s\n", \
        __FILE__, __LINE__, #expr);       \
      abort();                            \
    }                                     \
  } while (0)

#endif /* RG_ASSERT_H */

