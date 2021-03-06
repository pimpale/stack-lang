#include <stdio.h>

#include "function.h"
#include "parse.h"
#include "parseable.h"
#include "table.h"
#include "vector.h"

int main(int argc, char** argv) {
  Vector stack;
  Table funtab;

  // Instantiate environment
  initVector(&stack);
  initTable(&funtab);

  // Populate default function
  initPrelude(&funtab);

  if (argc > 1) {
    // Parse each file
    for (int i = 1; i < argc; i++) {
      Parseable fileParseable;
      FILE* file = fopen(argv[i], "r");
      if (file != NULL) {
        initParseableFile(&fileParseable, file);
        // Parse
        parse(&fileParseable, &stack, &funtab);
        freeParseable(&fileParseable);
      } else {
        fprintf(stderr, "ERROR: could not open file %s\n", argv[i]);
      }
    }
  } else {
    // Read from stdin
    Parseable input;
    initParseableFile(&input, stdin);
    // Parse
    parse(&input, &stack, &funtab);
    freeParseable(&input);
  }

  // Free resources
  freeVector(&stack);
  freeTable(&funtab);
}
