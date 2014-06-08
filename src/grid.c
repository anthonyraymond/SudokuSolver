#include "ft_sudoku.h"

t_grid			*create_grid(char *input_string)
{
	int				i;
	int				j;
	t_grid			*grid;

	(void)input_string;
	char *debug_array[] = {
		"800000000",
		"003600000",
		"070090200",
		"050007000",
		"000045700",
		"000100030",
		"001000068",
		"008500010",
		"090000400"
	};

	grid = malloc(sizeof(t_grid));

	grid->reliable_cells_count = 0;

	for (i = 0; i < GRID_TOP_DIGIT; ++i)
	{
		for (j = 0; j < GRID_TOP_DIGIT; ++j)
		{
			t_cell *cell;
			t_digit digit = (int) (debug_array[i][j] - 48);

			cell = (t_cell*) create_cell(digit, i, j);
			grid->cells[i][j] = cell;
			if (cell->reliable_digit != 0)
			{
				++grid->reliable_cells_count;
			}
		}
	}

	for (i = 0; i < GRID_TOP_DIGIT; ++i)
	{
		for (j = 0; j < GRID_TOP_DIGIT; ++j)
		{
			if (grid->cells[i][j]->reliable_digit != 0)
			{
				propage_constraint(grid, grid->cells[i][j]->reliable_digit, i, j);
			}
		}
	}

	return (grid);
}

void			destroy_grid(t_grid *grid)
{
	if (grid != NULL)
	{
		int			i;
		int			j;
		for (i = 0; i < GRID_TOP_DIGIT; ++i)
		{
			for (j = 0; j < GRID_TOP_DIGIT; ++j)
			{
				destroy_cell(grid->cells[i][j]);
			}
		}

		free(grid);
	}
}

void			print_grid(t_grid *grid)
{
	int			i;
	int			j;
	char		buffer[6] = "";
	char		output[462] = "";


	for (i = 0; i < GRID_TOP_DIGIT; ++i)
	{
		strcat(output, "|");
		for (j = 0; j < GRID_TOP_DIGIT; ++j)
		{
			if (grid->cells[i][j]->reliable_digit != 0)
			{
				sprintf(buffer, " %d |", grid->cells[i][j]->reliable_digit);
			}
			else
			{
				sprintf(buffer, " %c |", ' ');
			}
			strcat(output, buffer);

			if ((j + 1) % BLOCK_BY_ROW == 0 && (j + 1) != CELLS_BY_ROW)
			{
				strcat(output, "#|");
			}
		}

		strcat(output, "\n");
		if ((i + 1) % BLOCK_BY_ROW == 0 && (i + 1) != CELLS_BY_ROW)
		{
			strcat(output, "#########################################\n");
		}
	}

	strcat(output, "\0");
	printf("%s\n", output);
}

void			copy_grid(t_grid *dest, t_grid *origin)
{
	int			i;
	int			j;

	memcpy(&dest->reliable_cells_count, &origin->reliable_cells_count, sizeof(uint8_t));

	for (i = 0; i < GRID_TOP_DIGIT; ++i)
	{
		for (j = 0; j < GRID_TOP_DIGIT; ++j)
		{
			dest->cells[i][j] = malloc(sizeof(t_cell));
			copy_cell(dest->cells[i][j], origin->cells[i][j]);
		}
	}
}
