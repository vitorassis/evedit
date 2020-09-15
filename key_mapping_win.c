void triggerKey(dLine **lines, char tecla, int **exit, int **curX, int **curY, int **typed){
    switch (tecla) {
        case 13:
            insertLine(lines, NEXT_LINE);
            **typed = 1;
        break;
        case 8:
            removeChar(lines, CURR_CHAR);
            **typed = 1;
        break;
        default:
            insertChar(&(*lines)->curr, tecla, NEXT_CHAR);
            **typed = 1;
    }
}