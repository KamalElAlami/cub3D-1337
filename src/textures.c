/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sarif <sarif@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 01:16:22 by sarif             #+#    #+#             */
/*   Updated: 2024/11/28 13:33:51 by sarif            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

// uint32_t create_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
//     return (a << 24 | r << 16 | g << 8 | b);
// }

// uint8_t get_red(uint32_t color) { return (color >> 16) & 0xFF; }
// uint8_t get_green(uint32_t color) { return (color >> 8) & 0xFF; }
// uint8_t get_blue(uint32_t color) { return color & 0xFF; }
// uint8_t get_alpha(uint32_t color) { return (color >> 24) & 0xFF; }
void ft_close_window(mlx_t *mlx) {
    mlx_terminate(mlx); // Clean up and close the window
    exit(EXIT_SUCCESS);
}
int ft_textures(t_params *p)
{
	(void)p;
    mlx_t* mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Texture Example", true);
    if (!mlx) {
        fprintf(stderr, "Failed to initialize MLX\n");
        return EXIT_FAILURE;
    }

    // Step 2: Load the texture (from a PNG file)
    mlx_texture_t* texture = mlx_load_png("./src/textures/bricks.png");
    if (!texture) {
        fprintf(stderr, "Failed to load texture\n");
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Step 3: Create an image matching the texture size
    mlx_image_t* image = mlx_new_image(mlx, texture->width, texture->height);
    if (!image) {
        fprintf(stderr, "Failed to create MLX image\n");
        mlx_delete_texture(texture);
        mlx_terminate(mlx);
        return EXIT_FAILURE;
    }

    // Step 4: Copy texture pixels to the image buffer
    for (uint32_t y = 0; y < texture->height; y++) {
        for (uint32_t x = 0; x < texture->width; x++) {
            // Access the pixel at (x, y)
            uint32_t color = ((uint32_t*)texture->pixels)[y * texture->width + x];

            // Set the pixel in the MLX image
            mlx_put_pixel(image, x, y, color);
        }
    }

    // Step 5: Display the image in the window
    for (int x = 0; x < WINDOW_WIDTH; x += texture->width + 10) {
    for (int y = 0; y < WINDOW_HEIGHT; y += texture->height + 10) {
        // Render the image at (x, y)
        mlx_image_to_window(mlx, image, x, y);
    }
}

    // Step 6: Clean up texture (not needed after copying pixels)
    mlx_delete_texture(texture);
	mlx_loop(mlx);

    // Keep the window open
    return EXIT_SUCCESS;
}
