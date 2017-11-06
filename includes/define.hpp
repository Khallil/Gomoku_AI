# ifndef DEFINE
# define DEFINE

#define FENx  1000
#define FENy 1000

# define SIZE_X 19
# define SIZE_Y 19

# define INTERVAL 10

# define SQUARE_SIZE FENy / 40
# define POSx SQUARE_SIZE + x * FENy / SIZE_Y
# define POSy SQUARE_SIZE + y * FENy / SIZE_Y

# define NONE 'n'
# define BLACK 'b'
# define WHITE 'w'
# define SELECTED 's'
# define MAX_DEPTH 4
# define COUNT 3

typedef struct vector
{
  unsigned short x;
  unsigned short y;
  vector(unsigned short x, unsigned short y) : x(x), y(y)
  {  }
  vector(){}
}       vector;



# endif
