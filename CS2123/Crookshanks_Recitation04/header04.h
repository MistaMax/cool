#define true 1
#define false 0
#define New(type) ((type) malloc(sizeof *((type) NULL)))
#define NewArray(n, type) ((type *) malloc((n) * sizeof (type)))

typedef int bool;
typedef char *string;

typedef struct Point
{
    double x;
    double y;
} PointT;

typedef struct Rect
{
    PointT location;
    char color;
    double w;//width
    double h;//height
} RectT;

int chk_overlap(RectT *r1, RectT *r2);
void InputRect(RectT *r, string text);

