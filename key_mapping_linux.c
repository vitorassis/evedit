void triggerKey(linha **linhas, cursor **atual, int **exit, int **topo){
    carac *antCar;
    linha *antLin;
    char tecla = getch();
    switch (tecla) {
        case 27:    //TECLAS ESPECIAIS LINUX
            switch (getch()) {
                case 91:    //SETAS + PG LINUX
                    switch (getch()) {
                        case 54: //PGDOWN
                            // top = (top + MAX_YCURSOR-MIN_YCURSOR < lines->size) ? top + MAX_YCURSOR-MIN_YCURSOR : top;
                            // getch();
                            // clearEditor();

                            //pgdown func
                        break;
                        case 53: //PGUP
                            // top -= top < (MAX_YCURSOR-MIN_YCURSOR) ? 0 : (MAX_YCURSOR-MIN_YCURSOR);
                            // getch();
                            // clearEditor();

                            //pgup func
                        break;
                        case 66: //SETA P BAIXO
                            moveLinha(atual, PROX);
                        break;
                        case 65: //SETA P CIMA
                            moveLinha(atual, ANTE);
                        break;
                        case 68: //SETA P ESQUERDA
                            moveCarac(atual, ANTE);
                    }
                break;               
                case 79:    //FN KEYS
                    switch (getch()) {
                        case 83: // f4
                            **exit=1;
                        break;
                    }
                    
                break;             
            }
        break;
        case 10:
            addLinha((*atual)->aLinha);
            moveLinha(atual, PROX);
        break;
        case 127:
            if((*(*atual)->aCarac)->valor != 0){
                antCar = (*(*atual)->aCarac)->ant;
                removeCarac((*atual)->aCarac);
                (*atual)->aCarac = &antCar;
            }else {            
                antLin = (*(*atual)->aLinha)->ant;
                removeLinha((*atual)->aLinha); 
                (*atual)->aLinha = &antLin;
                (*atual)->aCarac = &(*(*atual)->aLinha)->caracs;
            }
        break;
        default:
            addCarac((*atual)->aCarac, tecla);
            moveCarac(atual, PROX);
    }
}