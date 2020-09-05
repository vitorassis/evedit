#define WIDTH 10
#define HEIGTH 23

void frame(){
    int i=1;

    gotoxy(20, 2);printw("evedit");

    for(i; i<WIDTH; i++){
        gotoxy(i, 1);printw("=");
        gotoxy(i, HEIGTH);printw("=");
    }
}