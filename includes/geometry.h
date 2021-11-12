#ifndef GEOMETRY_H
# define GEOMETRY_H

# include "vector3.h"

typedef struct s_point
{
	t_vector3	p;
	int			cd;
}				t_point;

typedef struct s_edge
{
	size_t	ptid[2];
}				t_edge;

typedef struct s_geometry
{
	t_point	*pts;
	size_t	npts;
	t_edge	*edges;
	size_t	nedges;
}				t_geometry;

#endif
