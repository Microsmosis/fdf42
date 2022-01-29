void	draw_end_line(void *mlx, void *win, int x, int y, int beginZ, int endZ, int height, int width, int projection)
{
	int	y_temp;
	int	offsetX;
	int	offsetY;
	
	offsetY = 400;
	offsetX = 400;
	if (projection == 1)
	{
		offsetY = -100;
		offsetX = 900;
	}
	if (projection == 0)
	{
		x++;
		y++;
	}
	y *= height;
	x *= width;
	y_temp = y;
	beginZ *= height / 4;
	endZ *= height / 4;
	while (y >= height)
	{
		draw_line(mlx, win, x + offsetX, y + offsetY, beginZ + offsetY, x + offsetX, (y - height) + offsetY, endZ + offsetY, projection, 0xFFFFFF);
		y -= height;
		if (y == height && projection == 0)
			break;
	}
	while (x >= width)
	{
		draw_line(mlx, win, x + offsetX, y_temp + offsetY, beginZ + offsetY, (x - width) + offsetX, y_temp + offsetY, endZ + offsetY, projection, 0xFFFFFF);
		x -= width;
		if (x == width && projection == 0)
			break;
	}
}