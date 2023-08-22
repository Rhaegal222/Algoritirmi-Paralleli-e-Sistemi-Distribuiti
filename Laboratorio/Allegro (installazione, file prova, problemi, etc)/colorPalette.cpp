#include <allegro.h>
#include <iostream>
#include <stdlib.h>
using namespace std;

// file prova per verificare corretta installazione di Allegro

int main(){
  allegro_init(); //Allegro initialization
  install_keyboard();//Set up for keyboard input
  set_color_depth(24);
  BITMAP *bitmap= create_bitmap(256, 256);
  set_gfx_mode(GFX_AUTODETECT_WINDOWED,256,256,0,0);
  for(int row = 0;row < 255;row++){
      for(int column = 0;column < 255;column++){
        putpixel(bitmap,column,row,makecol( row,column, 128 ) );
      }//end loop row
  }//end loop on column
  blit(bitmap, screen, 0, 0, 0, 0, 256, 256);
  readkey();

  return 0;//Return 0 to indicate a successful run.
}//end main function
END_OF_MAIN()

// mpic++ ./colorPalette.cpp -lalleg
// mpirun ./a.out -np 2