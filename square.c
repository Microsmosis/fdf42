
void	square(void *mlx, void *win, int beginX, int beginY, int endX, int endY)
{
	draw_line(mlx, win, x1, y1, x2 + 50, y2 + 25, 0xFFFFFF); // higher horizontal 
	draw_line(mlx, win, x1 - 50, y1 + 25, x2, y2 + 50, 0xFFFFFF); // lower horizontal
	draw_line(mlx, win, x1 - 50, y1 + 25, x2, y2, 0xFFFFFF); // left vertical
	draw_line(mlx, win, x1, y1 + 50, x2 + 50, y2 + 25, 0xFFFFFF); // right vertical
}


void	square(void *mlx, void *win)
{
	draw_line(mlx, win, 500, 300, 550, 325, 0xFFFFFF); // higher horizontal 
	draw_line(mlx, win, 450, 325, 500, 350, 0xFFFFFF); // lower horizontal
	draw_line(mlx, win, 450, 325, 500, 300, 0xFFFFFF); // left vertical
	draw_line(mlx, win, 500, 350, 550, 325, 0xFFFFFF); // right vertical
}

void	square2d(void *mlx, void *win, int x1, int y1, int x2, int y2)
{
	draw_line(mlx, win, x1, y1, x2, y2, 0xFFFFFF); // higher horizontal 
	draw_line(mlx, win, x1, y1, x1, y2 + 25, 0xFFFFFF); // left vertical
	draw_line(mlx, win, x1, y1 + 25, x2, y2 + 25, 0xFFFFFF); // lower horizontal
	draw_line(mlx, win, x1 + 25, y1 + 25, x2, y2 - 1, 0xFFFFFF); // right vertical
}


void	grid2(void *mlx, void *win, int x_len, int y_len)
{
	int		i = 100;
	int		j = 125;
	int		k = 200;
	int		counter = 0;
	int		size = 0;
	
	while (size < y_len)
	{
		while (counter < x_len)
		{
			square2d(mlx, win, i, k, j, k);
			i += 25;
			j += 25;
			counter++;
		}
		size++;
		counter = 0;
		i = 100;
		j = 125;
		k += 25;
	}
}

					// ISOMETRIC SQUARE GRID // 

/* void	square(void *mlx, void *win, int x1, int y1, int x2, int y2)
{
	draw_line(mlx, win, x1, y1, x2, y2, 0xFFFFFF); // higher horizontal 
	draw_line(mlx, win, x1 - 50, y1 + 25, x2 - 50, y2 + 25, 0xFFFFFF); // lower horizontal
	draw_line(mlx, win, x1 - 50, y1 + 25, x2 - 50, y2 - 25, 0xFFFFFF); // left vertical
	draw_line(mlx, win, x1, y1 + 50, x2, y2, 0xFFFFFF); // right vertical
} */

/* void	grid(void *mlx, void *win, int x_len, int y_len)
{
	int		i = 600;
	int		j = 250;
	int		counter = 0;
	int		size = 0;
	
	while (size < x_len)
	{
		while (counter < y_len)
		{
			square2d(mlx, win, i + 200, j, i + 250, j + 25);
			i += 50;
			j += 25;
			counter++;
		}
		size++;
		counter = 0;
		i = 600;
		j = 250;
		i -= 50 * size;
		j += 25 * size;
	}
} */