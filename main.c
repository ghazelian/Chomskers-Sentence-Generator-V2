#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "CFGengine.h"
#include "grammar.h"

static void return_string(const char *const *words, size_t size) {
  for (size_t i = 0; i < size; i++) {
    if (i != 0)
      putchar(' ');

    printf("%s", words[i]);
  }

  putchar('\n');
}

int main(int argc, char *argv[]) {
    size_t iterations = argc > 1 ? atoi(argv[1]) : 1;

    // This seeds the random number generator for the CFGengine using the current time
    srand(time(NULL));

    for (size_t i = 0; i < iterations; i++) {
        CFG *cfg = CFG_create(grammar_list[rand() % 3]);
        const char **words = CFG_pick_words(cfg);

        return_string(words, cfg->current_symbols_size);

        free(words);
        CFG_destroy(cfg);
    }

    return 0;
}