#ifndef POINT_H
#define POINT_H

typedef struct {
	int X; /* absis   */
	int Y; /* ordinat */
} Point;

/* *** Notasi Akses: Selektor POINT *** */
#define Absis(P) (P).X
#define Ordinat(P) (P).Y

#endif
