#define SCREEN_WIDTH 1190  //窗口显示像素
#define SCREEN_HIGTH 960
#define RATIO 61//图片显示像素
//控制上,下,左,右,退出
#define KEY_UP    'w'
#define KEY_LEFT  'a'
#define KEY_RIGTH 'd'
#define KEY_DOWN  's'
#define KEY_QUIT  'q'


enum DIRECT{
	UP,
	LEFT,
	RIGHT,
	DOWN
};

enum _PROPS{
	WALL,
	FLOOR,
	BOX_DES,
	BOX,
	MAN, 
	HIT,
	ALL
};
typedef enum DIRECT DIRECT;
typedef _PROPS PROPS;

struct _POST{
	int x;
	int y;
};
struct _POST man;
typedef _POST POST;