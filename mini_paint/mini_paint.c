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

//Структура рисуемого круга
typedef struct	s_circle
{
	char	type;
	float	x;
	float	y;
	float	radius;
	char	color;
}	t_circle;

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

//Определение типа пикселя (2 - окружность, 1 - внутри круга, 0 - вне круга)
int	mp_pixel_in_circle(float x, float y, t_circle *circle)
{
	float	length;

	length = sqrtf(powf(x - circle->x, 2.0) + powf(y - circle->y, 2.0));
	if (length <= circle->radius)
	{
		if ((circle->radius - length) < 1.00000000)
			return (2);
		return (1);
	}
	return (0);
}

//Рисование одного круга
void	mp_circle_draw(t_zone *zone, t_circle *circle)
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
			pixel_type = mp_pixel_in_circle((float)j, (float)i, circle);
			if ((circle->type == 'c' && pixel_type == 2) || (circle->type == 'C' && pixel_type > 0))
				zone->content[(i * zone->width) + j] = circle->color;
			j++;
		}
		i++;
	}
}

//Циклическое рисование всех кругов
int	mp_circles_draw(FILE *file, t_zone *zone)
{
	t_circle	tmp;
	int			ret;

	while ((ret = fscanf(file, "%c %f %f %f %c\n", &tmp.type, &tmp.x, &tmp.y, &tmp.radius, &tmp.color)) == 5)
	{
		if (tmp.radius <= 0.00000000 || (tmp.type != 'c' && tmp.type != 'C'))
			return (0);
		mp_circle_draw(zone, &tmp);
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
	if (mp_circles_draw(file, &zone) == 0)
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
