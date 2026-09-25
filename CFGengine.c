#include "CFGengine.h"

static bool starts_with_vowel(const char s) {
  return (s == 'a' || s == 'e' || s == 'i' || s == 'o' || s == 'u');
}

static int find_symbol_in_rule(const tag_dictionary *rules, tag symbol) {
  for (size_t i = 0; rules[i].key != TAG_END; i++) {
    if (rules[i].key == symbol)
      return i;
  }

  return -1;
}

static int find_symbol_in_lexicon(const lexicon_dictionary *lexicon,
                                        tag symbol) {
  for (size_t i = 0; lexicon[i].key != TAG_END; i++) {
    if (lexicon[i].key == symbol)
      return i;
  }

  return -1;
}

static int append_tag_list(tag **symbols, size_t *size, size_t *capacity,
                           tag value) {
  if (*size >= *capacity) {
    size_t new_capacity = (*capacity == 0) ? 8 : *capacity * 2;

    tag *temp = realloc(*symbols, new_capacity * sizeof(*temp));

    if (temp == NULL)
      return 0;

    *symbols = temp;
    *capacity = new_capacity;
  }

  (*symbols)[(*size)++] = value;

  return 1;
}

static size_t CFG_expand(CFG *self, const tag *symbols, tag **out) {
  tag *new_symbols = NULL;
  size_t size = 0;
  size_t capacity = 0;

  for (size_t i = 0; symbols[i] != TAG_END; i++) {
    int index = find_symbol_in_rule(self->rules, symbols[i]);

    if (index != -1) {
      tag *expanded = NULL;
      size_t expanded_size = CFG_expand(self, self->rules[index].values, &expanded);

      for (size_t j = 0; j < expanded_size; j++) {
        append_tag_list(&new_symbols, &size, &capacity, expanded[j]);
      }

      free(expanded);
    } else {
      append_tag_list(&new_symbols, &size, &capacity, symbols[i]);
    }
  }

  *out = new_symbols;

  return size;
}

CFG *CFG_create(const tag_dictionary *rules) {
  CFG *self = (CFG *)malloc(sizeof(*self));

  self->rules = rules;
  self->current_symbols_size =
      CFG_expand(self, (const tag[]){S, 0}, &self->current_symbols);

  return self;
}

const char **CFG_pick_words(CFG *self) {
  const char **words = malloc(self->current_symbols_size * sizeof(*words));

  for (size_t i = 0; i != self->current_symbols_size; i++) {
    int key_index = find_symbol_in_lexicon(lexicon, self->current_symbols[i]);
    int random_value_index = rand() % lexicon[key_index].size;

    words[i] = lexicon[key_index].values[random_value_index];

    if (i != 0 && strcmp(words[i - 1], "a") == 0 &&
        starts_with_vowel(words[i][0])) {
      words[i - 1] = "an";
    }
  }

  return words;
}

void CFG_destroy(CFG *self) {
  if (self != NULL) {
    free(self->current_symbols);
    free(self);
  }
}