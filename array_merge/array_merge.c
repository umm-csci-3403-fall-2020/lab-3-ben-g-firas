#include "array_merge.h"
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

bool is_complete(int num_arrays, int *positions)
{
    for (int i = 0; i < num_arrays; i++)
    {
        if (positions[i] > -1)
        {
            return false;
        }
    }
    return true;
}

int *array_merge(int num_arrays, int *sizes, int **values)
{
    int *comparison_positions = (int *)calloc(num_arrays, sizeof(int));
    int out_size = 0;
    for (int i = 0; i < num_arrays; i++)
    {
        comparison_positions[i] = sizes[i] - 1; // Gets the index of the last element for each array
        out_size += sizes[i];                   // The maximum number of values in the output
    }

    int *output = (int *)calloc(out_size, sizeof(int));
    int **input = (int **)calloc(out_size, sizeof(int)); // MIGHT NEED MORE SIZE FOR POINTERS
    for (int i = 0; i < num_arrays; i++)
    {
        input[i] = (int *)calloc(sizes[i], sizeof(int));
        for (int j = 0; j < num_arrays; j++)
        {
            input[i][j] = values[i][j];
        }
    }

    int end_pos = 1;

    while (!is_complete(num_arrays, comparison_positions))
    {
        int min_value = INT_MAX;
        int val_array = -1;
        for (int i = 0; i < num_arrays; i++)
        {
            if (comparison_positions[i] > -1 && input[val_array][comparison_positions[i]] <= min_value)
            {
                min_value = input[val_array][comparison_positions[i]];
                val_array = i;
            }
        }

        int pos = 0;
        while (true)
        {
            if (pos > end_pos)
            {
                output[end_pos] = min_value;
                end_pos++;
                comparison_positions[val_array]--;
                break;
            }
            else if (output[pos] > min_value)
            {
                input[val_array][comparison_positions[val_array]] = output[pos];
                output[pos] = min_value;
                break;
            }
            else if (output[pos] == min_value)
            {
                comparison_positions[val_array]--;
                break;
            }
            else
            {
                pos++;
            }
        }
    }

    output = (int *)realloc(output, end_pos * sizeof(int));
    for (int i = 0; i < num_arrays; i++)
    {
        free(input[i]);
    }

    free(input);
    free(comparison_positions);

    output[0] = end_pos;
    return output;
}
