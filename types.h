#ifndef TYPES_H
#define TYPES_H

#include <stddef.h>

#define ARRAY_SIZE(a) sizeof(a) / sizeof(a[0])

typedef enum {
  TAG_END = 0,
  S, S_finite,
  N, NP, NP_name, N_name,
  V_intr, V_trans, VP, VP_finite,
  Adj, AdjP,
  Adv,
  P,
  Det, DP,
  C_n, C_v, CP,
  Conj_c, Conj_p
} tag;

typedef struct {
  tag key;
  const tag *values; // Terminated by TAG_END
} tag_dictionary;

typedef struct {
  tag key;
  const char **values;
  size_t size;
} lexicon_dictionary;

#endif