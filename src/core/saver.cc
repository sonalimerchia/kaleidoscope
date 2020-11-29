#include <core/saver.h>
#include <stdio.h>
#include <stdlib.h>
#include <nfd.h>

namespace kaleidoscope {

void Saver::Save(const visualizer::Sketchpad &pad) {
  nfdchar_t *savePath = NULL;
  nfdresult_t result = NFD_SaveDialog( "png,jpg", NULL, &savePath );
  if ( result == NFD_OKAY )
  {
    puts("Success!");
    puts(savePath);
    free(savePath);
  }
  else if ( result == NFD_CANCEL )
  {
    puts("User pressed cancel.");
  }
  else
  {
    printf("Error: %s\n", NFD_GetError() );
  }

}

}