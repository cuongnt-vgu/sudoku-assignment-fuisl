#include "naked_pairs.h"
#include <stdlib.h>
#include <stdio.h>

int naked_pairs(SudokuBoard *p_board)
{
    int naked_pairs_counter = 0;
    NakedPairs naked_pairs[BOARD_SIZE * BOARD_SIZE];

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        find_naked_pairs(p_board->p_rows[i], naked_pairs, &naked_pairs_counter);
        find_naked_pairs(p_board->p_cols[i], naked_pairs, &naked_pairs_counter);
        find_naked_pairs(p_board->p_boxes[i], naked_pairs, &naked_pairs_counter);
   }

    return naked_pairs_counter;
}

void find_naked_pairs(Cell **p_cells, NakedPairs *p_naked_pairs,
                      int *p_counter)
{

    for (int i = 0; i < BOARD_SIZE-1; i++)
    {
        if (p_cells[i]->fixed)
        {
            continue;
        }
        for (int j = i+1; j < BOARD_SIZE; j++)
        {
            if (p_cells[j]->fixed)
            {
                continue;
            }

            if (p_cells[i]->num_candidates == 2 && p_cells[j]->num_candidates == 2)
            {
                int *candidates_j = get_candidates(p_cells[j]);
                int *candidates_i = get_candidates(p_cells[i]);
                if ((candidates_i[0] == candidates_j[0]) && (candidates_i[1] == candidates_j[1]))
                {
                    // Check if the pair is already in the list
                    bool duplicate = false;
                    for (int k = 0; k < *p_counter; k++)
                    {
                        if (p_naked_pairs[k].p_cell1 == p_cells[i] && p_naked_pairs[k].p_cell2 == p_cells[j])
                        {
                            duplicate = true;
                            break;
                        }
                    }

                    if (!duplicate)
                    {
                        p_naked_pairs[*p_counter].p_cell1 = p_cells[i];
                        p_naked_pairs[*p_counter].p_cell2 = p_cells[j];
                        p_naked_pairs[*p_counter].value1 = candidates_i[0];
                        p_naked_pairs[*p_counter].value2 = candidates_i[1];
                        *p_counter += 1;

                        unset_pairs(p_cells, candidates_i[0], candidates_i[1], p_cells[i], p_cells[j]);
                    }
                }
                free(candidates_i);
                free(candidates_j);
            }
        }
    }
}

void unset_pairs(Cell **p_cells, int value1, int value2, Cell *p_cell1, Cell *p_cell2)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (p_cells[i]->fixed || p_cells[i]->num_candidates == 1 || p_cells[i] == p_cell1 || p_cells[i] == p_cell2)
        {
            continue;
        }
        int *candidates = get_candidates(p_cells[i]);

        for (int j = 0; j < p_cells[i]->num_candidates; j++)
        {
            if (candidates[j] == value1 || candidates[j] == value2)
            {
                unset_candidate(p_cells[i], candidates[j]);
            }
        }
        free(candidates);
    }
}