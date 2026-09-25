#ifndef CFGENGINE_H
#define CFGENGINE_H

#include "lexicon.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  const tag_dictionary *rules;
  tag *current_symbols;
  size_t current_symbols_size;
} CFG;

CFG *CFG_create(const tag_dictionary *rules);
const char **CFG_pick_words(CFG *self);
void CFG_destroy(CFG *self);

#endif