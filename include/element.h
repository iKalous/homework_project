#include<stdio.h>

struct div
{
    int width,height;
    int direction; // direction = 0 -> row derection = 1 -> column
    int align_items; // = 0 -> start = 1 -> center = 2 -> end = 3 -> space-evenly
    int justify_items; // the same as above
    int color; // c = 0 -> none c = 1 -> red c = 2 -> blue c = 3 -> green
    int em; // em = 0 -> none em = 1 -> emphasis
    int i; // i = 0 -> none i = 1 -> italic
    int u; // u = 0 -> none u = 1 -> underline
};
struct heading
{
    char ch;
    int color; // c = 0 -> none c = 1 -> red c = 2 -> blue c = 3 -> green
    int em; // em = 0 -> none em = 1 -> emphasis
    int i; // i = 0 -> none i = 1 -> italic
    int u; // u = 0 -> none u = 1 -> underline
    // int height,width;
};
struct paragragh
{
    char ch;
    int color; // c = 0 -> none c = 1 -> red c = 2 -> blue c = 3 -> green
    int em; // em = 0 -> none em = 1 -> emphasis
    int i; // i = 0 -> none i = 1 -> italic
    int u; // u = 0 -> none u = 1 -> underline
    // int height,width;
};
struct image
{
    char ch; // content
};
struct node
{
    int id; // id = 0 -> div id = 1 -> h id = 2 -> p id = 3 -> img
    struct div div;
    struct heading h;
    struct paragragh p;
    struct image img;
};

struct heading_string
{
    char s[55];
    struct heading element;
    int id,width,height;
};
struct paragragh_string
{
    char s[55];
    struct paragragh element;
    int id,width,height;
};
struct image_string
{
    char s[55];
    struct image element;
    int id,width,height;
};
struct kind{ int kind,id; }; // kind = 0 -> div kind = 1 -> h kind = 2 -> p kind = 3 -> img
struct div_string
{
    int id,tot;
    struct div element;
    struct kind stk[110];
};