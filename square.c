
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
