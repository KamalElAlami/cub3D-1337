#include "../includes/cub3d.h"

void draw_line(t_graphics *graphic, t_player *player)
{
	const int LINE_LENGTH = 20;
	int player_x = (int)(player->posx);
	int player_y = (int)(player->posy);
	
	int end_x = player_x + (int)(player->dirx * LINE_LENGTH);
	int end_y = player_y + (int)(player->diry * LINE_LENGTH);
	int dx = end_x - player_x;
	int dy = end_y - player_y;
	int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

	float x_inc = dx / (float)steps;
	float y_inc = dy / (float)steps;

	float x = player_x;
	float y = player_y;

	for (int i = 0; i <= steps; i++)
	{
		mlx_put_pixel(graphic->img, (int)roundf(x + 1), (int)roundf(y), 0xFF0000FF);
		mlx_put_pixel(graphic->img, (int)roundf(x), (int)roundf(y), 0xFF0000FF);
		mlx_put_pixel(graphic->img, (int)roundf(x - 1), (int)roundf(y), 0xFF0000FF);
		mlx_put_pixel(graphic->img, (int)roundf(x), (int)roundf(y -1), 0xFF0000FF);
		mlx_put_pixel(graphic->img, (int)roundf(x), (int)roundf(y), 0xFF0000FF);
		mlx_put_pixel(graphic->img, (int)roundf(x), (int)roundf(y + 1), 0xFF0000FF);
		x += x_inc;
		y += y_inc;
	}
}

void draw_direction_line(t_graphics *graphic, t_player *player)
{
	const int LINE_LENGTH = 20;
	int player_x = (int)(player->posx);
	int player_y = (int)(player->posy);
	
	int end_x = player_x + (int)(player->dirx * LINE_LENGTH);
	int end_y = player_y + (int)(player->diry * LINE_LENGTH);
	int dx = end_x - player_x;
	int dy = end_y - player_y;
	int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);

	float x_inc = dx / (float)steps;
	float y_inc = dy / (float)steps;

	float x = player_x;
	float y = player_y;

	for (int i = 0; i <= steps; i++)
	{
		mlx_put_pixel(graphic->img, (int)roundf(x + 1), (int)roundf(y), 0xFF0000FF);
		mlx_put_pixel(graphic->img, (int)roundf(x), (int)roundf(y), 0xFF0000FF);
		mlx_put_pixel(graphic->img, (int)roundf(x - 1), (int)roundf(y), 0xFF0000FF);
		mlx_put_pixel(graphic->img, (int)roundf(x), (int)roundf(y -1), 0xFF0000FF);
		mlx_put_pixel(graphic->img, (int)roundf(x), (int)roundf(y), 0xFF0000FF);
		mlx_put_pixel(graphic->img, (int)roundf(x), (int)roundf(y + 1), 0xFF0000FF);
		x += x_inc;
		y += y_inc;
	}
}

void render_player(t_graphics *graphic, t_player *player)
{
	const int PLAYER_SIZE = 8;

	int player_x = (int)player->posx ;
	int player_y = (int)player->posy ;
	
	uint32_t player_color = 0xFF0000FF;
	for (int y = -PLAYER_SIZE/2; y < PLAYER_SIZE/2; y++)
	{
		for (int x = -PLAYER_SIZE/2; x < PLAYER_SIZE/2; x++)
		{
			if (x*x + y*y <= (PLAYER_SIZE/2)*(PLAYER_SIZE/2))
			{
				mlx_put_pixel(graphic->img, player_x + x, player_y + y, player_color);
			}
		}
	}
	draw_direction_line(graphic, player);
}

void draw_player(void *ptr)
{
	t_player *p = ptr;
	render_player(p->params->graph, p);
}


void mlxdrawmap(t_graphics *graphic, t_params *parameters)
{
	(void)graphic;
    int i;
    int j;
    int x;
    int y;
    uint32_t color;

    i = 0;
    while (parameters->map[i])
    {
        j = 0;
        while (parameters->map[i][j])
        {
            if (parameters->map[i][j] == '1' || parameters->map[i][j] == '\n')
                color = 0x000000FF;
            else
                color = 0xFFFFFFFF;
            x = 0;
            while (x < TILE_SIZE - 1)
            {
                y = 0;
                while (y <  TILE_SIZE - 1)
                {
                    mlx_put_pixel(graphic->img, j * 32 + x, i * 32 + y, color);
                    y++;
                }
                x++;
            }
            j++;
        }
        i++;
    }
}


void draw_map(void *ptr) {
    t_params   *p = ptr;

    mlxdrawmap(p->graph, p);
}

void    draw_ray(t_graphics *data, t_player *player, double ray_angle, double distance)
{
	// Starting point (player position)
	double start_x = player->posx;
	double start_y = player->posy;
	
	// Length of the ray (you can adjust this)
	int ray_length = (int)floor(distance);
	
	// Calculate end point using cos and sin
	double end_x = start_x + (cos(ray_angle) * ray_length);
	double end_y = start_y + (sin(ray_angle) * ray_length);
	
	// Variables for DDA line drawing
	double dx = end_x - start_x;
	double dy = end_y - start_y;
	
	// Number of steps needed (use the bigger delta)
	int steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	
	// Calculate increment per step
	double x_inc = dx / (double)steps;
	double y_inc = dy / (double)steps;
	
	// Start drawing from player position
	double x = start_x;
	double y = start_y;
	
	// Draw the line step by step
	for (int i = 0; i <= steps; i++)
	{
		// Put pixel if it's within window bounds
		if (x >= 0 && x < player->params->w_width && y >= 0 && y < player->params->w_height)
			mlx_put_pixel(data->img, (int)x, (int)y, 0xFF0000ff);
		
		// Move to next position
		x += x_inc;
		y += y_inc;
	}
}