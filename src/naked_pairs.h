#pragma once

#include "sudoku.h"

typedef struct NakedPairs_impl
{
    Cell *p_cell1;
    Cell *p_cell2;

    int value1;
    int value2;
} NakedPairs;

// find naked pairs in a board
int naked_pairs(SudokuBoard *p_board);

// unset candidates for a row/col/box
void unset_pairs(Cell **p_cells, int value1, int value2, Cell *p_cell1, Cell *p_cell2);

// find naked pair cell in a board and return the number of pair
void find_naked_pairs(Cell **p_cells, NakedPairs *p_naked_pairs, int *p_counter);