/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-11-18 14:56:04 by hbreeze           #+#    #+#             */
/*   Updated: 2024-11-18 14:56:04 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_H
# define FRACT_H

# include "libft.h"
# include "MLX42.h"

# include <math.h>
# include <pthread.h>

# ifndef NUM_THREADS
#  define NUM_THREADS 11
# endif

# define MY_PI 3.14159265358979323846

/**
 * just call it a f'n image m8
 */
typedef mlx_image_t	t_img;

//  ██████  ██████  ███    ███ ██████  ██      ███████ ██   ██ 
// ██      ██    ██ ████  ████ ██   ██ ██      ██       ██ ██  
// ██      ██    ██ ██ ████ ██ ██████  ██      █████     ███   
// ██      ██    ██ ██  ██  ██ ██      ██      ██       ██ ██  
//  ██████  ██████  ██      ██ ██      ███████ ███████ ██   ██ 

/**
 * @brief A representation of a complex number.
 * @param real the real part
 * @param imag the imaginary part
 */
typedef struct s_complex
{
	_Float64x	real;
	_Float64x	imag;
}	t_complex;

t_complex complex_mul(t_complex a, t_complex b);

t_complex complex_add(t_complex a, t_complex b);

t_complex complex_scale(t_complex z, double scale);


/**
 * @brief a complex plane
 * @param x_min the minimum of the x plane.
 * @param x_max the maximum of the x plane.
 * @param y_min the minimum of the y plane.
 * @param y_max the maximum of the y plane.
 */
typedef struct s_cplane
{
	_Float64x	x_min;
	_Float64x	x_max;
	_Float64x	y_min;
	_Float64x	y_max;
}	t_cplane;

/**
 * @brief a fratal descriptor.
 * @param width Screen space width.
 * @param height Screen space height.
 * @param plane the complex plane to map to/from.
 * @param get_depth function to get the depth of a given point.
 * @param data extra data for use in get_depth.
 * @param del function to free data if needed (leave as null if not needed);
 */
typedef struct s_fract
{
	size_t		width;
	size_t		height;
	t_cplane	*plane;
	float		max_depth;
	size_t		(*get_depth)(t_complex *, const size_t, const void *);
	void		*data;
	void		(*del)(void *);
}	t_fract;

/**
 * @brief Fract cleanup function.
 */
void		destory_fract(t_fract *fract);

t_complex	*create_complex(float real, float imag);

/**
 * @brief map a point in screenspace to complex space.
 * @param fract the fractol (containing the cplane).
 * @param col screenspace x coordinate
 * @param row screenspace y coordinate
 */
t_complex	map_to_complex(const t_fract *fract, int col, int row);

/**
 * @brief get depth for mandelbrot set.
 * @param c point in complex space.
 * @param max_depth the max depth to stop at.
 * @param data IGNORED!
 * 
 * Mandelbrot set is produced by applying  z[n + 1] = z[n]^2 + c
 * until either an escape condition is met or the iterations (n) meets
 * max_depth. Where z starts at 0 and C is the point in complex space.
 */
size_t		mandelrot(t_complex *c, const size_t max_depth, const void *data);

/**
 * @brief get depth for julia set.
 * @param z point in complex space.
 * @param max_depth the max_depth to stop at.
 * @param c the complex julia set descriptor.
 * 
 * Julia set is produced by applying a similar concept
 * to Madelbrot but is the given point in complex space, and c
 * is a fixed value, z[n + 1] = z[n]^2 + c can be applied
 * again until max_depth or the escape condition is met.
 */
size_t		julia(t_complex *z, const size_t max_depth, const void *c);

/**
 * @brief Creates a cplane of given size.
 * @returns __Memory allocated__ cplane.
 */
t_cplane	*create_cplane(_Float64x x_min, _Float64x x_max,
				_Float64x y_min, _Float64x y_max);

/**
 * @brief Creates a fratal.
 * @returns __Memory allocated__ cplane.
 */
t_fract		*create_fract(int screen[2], t_cplane *plane,
				size_t (*fn)(t_complex *, const size_t, const void *),
				void *data);

//  ██████  ██████  ███████ ██   ██ 
// ██       ██   ██ ██       ██ ██  
// ██   ███ ██████  █████     ███   
// ██    ██ ██   ██ ██       ██ ██  
//  ██████  ██   ██ ██      ██   ██ 


typedef struct
{
	int32_t	start[2];
	int32_t	end[2];
}	t_mdata;


/**
 * @brief the main simulation struct.
 * @param mlx the mlx instance.
 * @param current_fract the current fractal to draw.
 * @param canvas the current image to use
 * @param redraw DEFUNCT
 * @param scale scale (default 1.0)
 */
typedef struct s_sim
{
	mlx_t	*mlx;
	t_fract	*current_fract;
	float	*depth;
	t_img	*canvas;
	int32_t	pos[2];
	int32_t	iter[2];
	float	scale;
	int		recalc;
	int		redraw;
	int		*depth_array;
	t_mdata	*mos;
}	t_sim;

/**
 * @brief simuation cleanup func.
 */
void	destory_sim(t_sim *sim);

void	draw_fract(void *data);


/**
 * @brief Scrolling function to scroll through
 * 	the fractal at mouse pos.
 */
void	scroll_through(double xdelta, double ydelta, void *param);

void	click_hook(mouse_key_t button, action_t action,
			modifier_key_t mods, void *param);

void	redraw_hook(void *param);


// ███    ███ ██    ██ ██      ████████ ██ 
// ████  ████ ██    ██ ██         ██    ██ 
// ██ ████ ██ ██    ██ ██         ██    ██ 
// ██  ██  ██ ██    ██ ██         ██    ██ 
// ██      ██  ██████  ███████    ██    ██ 

typedef struct
{
	t_fract	*fract;
	int		offset;
	int		count;
	int		*data;
}	t_thread_data;

void	process_frame(int *data, t_fract *f, t_sim *sim);

void	draw_depth_map(t_sim *sim);

// ███████ ██████   ██████   ██████  ██   ██ ██    ██ 
// ██      ██   ██ ██    ██ ██    ██ ██  ██   ██  ██  
// ███████ ██████  ██    ██ ██    ██ █████     ████   
//      ██ ██      ██    ██ ██    ██ ██  ██     ██    
// ███████ ██       ██████   ██████  ██   ██    ██    

typedef struct s_polynomial {
	t_complex	(*polynomial)(t_complex *z);    // Function for P(z)
	t_complex	(*derivative)(t_complex *z);    // Function for P'(z)
	t_complex	*roots;
	int			root_count;
} t_polynomial;


size_t newton_depth(t_complex *c, size_t max_depth, const void *data);

#endif