#include "ft_sudoku.h"

t_bool			check_row_and_col_integrity(const t_grid *grid, const int row_index, const int col_index)
{
	t_bool		avaliable_digits_raw[9] = {false};
	t_bool		avaliable_digits_col[9] = {false};
	int 		i;
	int			current_digit;

	for (i = 0; i < GRID_TOP_DIGIT; ++i)
	{
		current_digit = grid->cells[row_index][i]->reliable_digit;
		if (current_digit != 0)
		{
			if (avaliable_digits_raw[current_digit - 1])
			{
				return (false);
			}
			avaliable_digits_raw[current_digit - 1] = true;
		}

		current_digit = grid->cells[i][col_index]->reliable_digit;
		if (current_digit != 0)
		{
			if (avaliable_digits_col[current_digit - 1])
			{
				return (false);
			}
			avaliable_digits_col[current_digit - 1] = true;
		}
	}

	return (true);
}


t_bool			check_cell_block_integrity(const t_grid *grid, const int cell_pos_x, const int cell_pos_y)
{
	t_bool		avaliable_digits[9] = {false};
	int			i;
	int			j;
	int			current_digit;
	const int block_x_start = ((int)(cell_pos_x / BLOCK_BY_ROW)) * BLOCK_BY_ROW;
	const int block_y_start = ((int)(cell_pos_y / BLOCK_BY_ROW)) * BLOCK_BY_ROW;

	for (i = block_x_start; i < block_x_start + 3; ++i)
	{
		for (j = block_y_start; j < block_y_start + 3; ++j)
		{
			current_digit = grid->cells[i][j]->reliable_digit;
			if (current_digit != 0)
			{
				if (avaliable_digits[current_digit - 1])
				{
					return (false);
				}
				avaliable_digits[current_digit - 1] = true;
			}
		}
	}

	return (true);
}

t_bool			check_whole_grid_integrity(const t_grid *grid)
{
	int			i;
	int			j;

	for (i = 0; i < GRID_TOP_DIGIT; ++i)
	{
		if(!check_row_and_col_integrity(grid, i, i))
			return (false);
	}

	for (i = 0; i < BLOCK_BY_ROW; ++i)
	{
		for (j = 0; j < BLOCK_BY_ROW; ++j)
		{
			if (!check_cell_block_integrity(grid, i * 3, j * 3))
				return (false);
		}
	}
	return (true);
}

void			propage_row_and_col_constraint(t_grid *grid, t_cell *cell)
{
	t_cell		*buffer_cell;
	int			i;
	int			reliable_digit;

	reliable_digit = cell->reliable_digit;

	for (i = 0; i < GRID_TOP_DIGIT; ++i)
	{
		buffer_cell = grid->cells[cell->pos_x][i];
		if (buffer_cell->possible_digits_count != 1)
		{
			if(buffer_cell->possible_digits[reliable_digit - 1])
			{
				buffer_cell->possible_digits[reliable_digit - 1] = false;
				--buffer_cell->possible_digits_count;
			}
		}

		buffer_cell = grid->cells[i][cell->pos_y];
		if (buffer_cell->possible_digits_count != 1)
		{
			if(buffer_cell->possible_digits[reliable_digit - 1])
			{
				buffer_cell->possible_digits[reliable_digit - 1] = false;
				--buffer_cell->possible_digits_count;
			}
		}
	}
}

void			propage_block_constraint(t_grid *grid, t_cell *cell)
{
	t_cell		*buffer_cell;
	int			i;
	int			j;
	int			reliable_digit;

	reliable_digit = cell->reliable_digit;

	const int block_x_start = ((int)(cell->pos_x / BLOCK_BY_ROW)) * BLOCK_BY_ROW;
	const int block_y_start = ((int)(cell->pos_y / BLOCK_BY_ROW)) * BLOCK_BY_ROW;

	for (i = block_x_start; i < block_x_start + 3; ++i)
	{
		for (j = block_y_start; j < block_y_start + 3; ++j)
		{
			buffer_cell = grid->cells[i][j];
			if (buffer_cell->possible_digits_count != 1)
			{
				if(buffer_cell->possible_digits[reliable_digit - 1])
				{
					buffer_cell->possible_digits[reliable_digit - 1] = false;
					--buffer_cell->possible_digits_count;
				}
			}

		}
	}
}

void			propage_constraint(t_grid *grid, t_cell *cell)
{
	propage_row_and_col_constraint(grid, cell);
	propage_block_constraint(grid, cell);
}


void			propage_whole_grid_constraint(t_grid *grid)
{
	int			i;
	int			j;


	for (i = 0; i < GRID_TOP_DIGIT; ++i)
	{
		for (j = 0; j < GRID_TOP_DIGIT; ++j)
		{
			if (grid->cells[i][j]->reliable_digit != 0)
			{
				propage_constraint(grid, grid->cells[i][j]);
			}
		}
	}
}
