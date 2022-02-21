#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <math.h>

//Структура зоны для рисования
typedef struct	s_zone
{
	int		width;
	int		height;
	char	background;
	char	*content;
}	t_zone;

//Структура рисуемого прямоугольника
typedef struct	s_rectangle
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	color;
}	t_rectangle;

//Вывод строки
void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
}

//Считывание первой строки по шаблону и выделение памяти под рисунок
void	mp_zone_malloc(FILE *file, t_zone *zone)
{
	int		i;
	int		square;

	if (fscanf(file, "%d %d %c\n", &zone->width, &zone->height, &zone->background) != 3)
		return ;
	if (zone->width <= 0 || zone->width > 300 || zone->height <= 0 || zone->height > 300)
		return ;
	square = zone->width * zone->height;
	zone->content = (char *)malloc(sizeof(char *) * square);
	if (zone->content == NULL)
		return ;
	i = 0;
	while (i < square)
	{
		zone->content[i] = zone->background;
		i++;
	}
}

//Определение типа пикселя (2 - граница, 1 - внутри прямоугольника, 0 - вне прямоугольника)
int	mp_pixel_in_rectangle(float x, float y, t_rectangle *rectangle)
{
	if (x >= rectangle->x && x <= rectangle->x + rectangle->width && y >= rectangle->y && y <= rectangle->y + rectangle->height)
	{
		if ((x - rectangle->x < 1.00000000) || (rectangle->x + rectangle->width - x < 1.00000000) || (y - rectangle->y < 1.00000000) || (rectangle->y + rectangle->height - y < 1.00000000))
			return (2);
		return (1);
	}
	return (0);
}

//Рисование одного прямоугольника
void	mp_rectangle_draw(t_zone *zone, t_rectangle *rectangle)
{
	int	i;
	int	j;
	int	pixel_type;

	i = 0;
	while (i < zone->height)
	{
		j = 0;
		while (j < zone->width)
		{
			pixel_type = mp_pixel_in_rectangle((float)j, (float)i, rectangle);
			if ((rectangle->type == 'r' && pixel_type == 2) || (rectangle->type == 'R' && pixel_type > 0))
				zone->content[(i * zone->width) + j] = rectangle->color;
			j++;
		}
		i++;
	}
}

//Циклическое рисование всех прямоугольников
int	mp_rectangles_draw(FILE *file, t_zone *zone)
{
	t_rectangle	tmp;
	int			ret;

	while ((ret = fscanf(file, "%c %f %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.width, &tmp.height, &tmp.color)) == 6)
	{
		if (tmp.width <= 0.00000000 || tmp.height <= 0.00000000 || (tmp.type != 'r' && tmp.type != 'R'))
			return (0);
		mp_rectangle_draw(zone, &tmp);
	}
	if (ret != -1)
		return (0);
	return (1);
}

//Вывод контента зоны
void	mp_zone_content_print(t_zone *zone)
{
	int	i;

	i = 0;
	while (i < zone->height)
	{
		write(1, zone->content + (i * zone->width), zone->width);
		ft_putstr("\n");
		i++;
	}
}

//Основная функция
int	main(int argc, char **argv)
{
	FILE	*file;
	t_zone	zone;

	if (argc != 2)
	{
		ft_putstr("Error: argument\n");
		return (1);
	}
	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		ft_putstr("Error: Operation file corrupted\n");
		return (1);
	}
	zone.width = 0;
	zone.height = 0;
	zone.background = 0;
	zone.content = NULL;
	mp_zone_malloc(file, &zone);
	if (zone.content == NULL)
	{
		ft_putstr("Error: Operation file corrupted\n");
		fclose(file);
		return (1);
	}
	if (mp_rectangles_draw(file, &zone) == 0)
	{
		ft_putstr("Error: Operation file corrupted\n");
		fclose(file);
		free(zone.content);
		return (1);
	}
	mp_zone_content_print(&zone);
	fclose(file);
	free(zone.content);
	return (0);
}
