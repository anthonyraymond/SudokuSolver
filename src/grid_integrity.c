#include "ft_sudoku.h"

bool			check_row_and_col_integrity(t_grid *grid, int row_index, int col_index)
{
	int 		i;
	bool		avaliable_digits_raw[9] = {false};
	bool		avaliable_digits_col[9] = {false};
	t_digit		current_digit;

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


bool			check_cell_block_integrity(t_grid *grid, int cell_pos_x, int cell_pos_y)
{
	int			i;
	int			j;
	int			block_x_start;
	int			block_y_start;
	bool		avaliable_digits[9] = {false};
	t_digit		current_digit;

	block_x_start = ((int)(cell_pos_x / BLOCK_BY_ROW)) * BLOCK_BY_ROW;
	block_y_start = ((int)(cell_pos_y / BLOCK_BY_ROW)) * BLOCK_BY_ROW;

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

bool			check_whole_grid_integrity(t_grid *grid)
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

void			propage_row_and_col_constraint(t_grid *grid, t_digit reliable_digit, int cell_pos_x, int cell_pos_y)
{
	int			i;
	t_cell		*buffer_cell;

	for (i = 0; i < GRID_TOP_DIGIT; ++i)
	{
		buffer_cell = grid->cells[cell_pos_x][i];
		if (buffer_cell->possible_digits_count != 1)
		{
			if(buffer_cell->possible_digits[reliable_digit - 1])
			{
				buffer_cell->possible_digits[reliable_digit - 1] = false;
				--buffer_cell->possible_digits_count;
			}
		}

		buffer_cell = grid->cells[i][cell_pos_y];
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

void			propage_block_constraint(t_grid *grid, t_digit reliable_digit, int cell_pos_x, int cell_pos_y)
{
	int			i;
	int			j;
	int			block_x_start;
	int			block_y_start;
	t_cell		*buffer_cell;

	block_x_start = ((int)(cell_pos_x / BLOCK_BY_ROW)) * BLOCK_BY_ROW;
	block_y_start = ((int)(cell_pos_y / BLOCK_BY_ROW)) * BLOCK_BY_ROW;

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

void			propage_constraint(t_grid *grid, t_digit reliable_digit, int cell_pos_x, int cell_pos_y)
{
	propage_row_and_col_constraint(grid, reliable_digit, cell_pos_x, cell_pos_y);
	propage_block_constraint(grid, reliable_digit, cell_pos_x, cell_pos_y);
}
