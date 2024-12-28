#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "element.h"
#include "minmax.h"

struct node map[15][55];
struct heading_string nH[110];
struct paragragh_string nP[110];
struct image_string nI[110];
struct div_string nD[110];
int toth = 0,totp = 0,toti = 0,totd = 0;

int num(char ch)
{
    if(ch == 'd') return 0;
    if(ch == 'h') return 1;
    if(ch == 'p') return 2;
    if(ch == 'i') return 3;
}
char s[10010];

struct div_string read_div(int divp)
{
    struct div_string cur; char ch; int x;
    
    cur.element = (struct div){ 0,0,0,0,0,0,0,0,0 };
    cur.tot = 0, cur.id = divp;

    for(int i = 1;i <= 3; ++ i) ch = getchar();
    for(int fg = 0,L;ch != '>';ch = getchar())
    {
        for(;ch == ' ' || ch == '\n';ch = getchar());
        if(ch == 'w')
        {
            for(;ch != '"';ch = getchar());
            scanf("%d",&x), cur.element.width = x;
        }
        if(ch == 'h')
        {
            for(;ch != '"';ch = getchar());
            scanf("%d",&x), cur.element.height = x;
        }
        if(ch == 'd')
        {
            for(int i = 1;i <= 8; ++ i) ch = getchar();
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '=' || ch == '"';ch = getchar());
            if(ch == 'r') 
                cur.element.direction = 0, L = 2;
            else
                cur.element.direction = 1, L = 5;
            for(int i = 1;i <= L; ++ i) ch = getchar();
            for(;ch != '"';ch = getchar());
        }
        if(ch == 'a')
        {
            for(int i = 1;i <= 10; ++ i) ch = getchar();
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '=' || ch == '"';ch = getchar());
            if(ch == 's')
            {
                ch = getchar();
                if(ch == 't') 
                    L = 3, cur.element.align_items = 0;
                else 
                    L = 10, cur.element.align_items = 3;
            }
            if(ch == 'c')
                L = 5, cur.element.align_items = 1;
            if(ch == 'e')
                L = 2, cur.element.align_items = 2;
            for(int i = 1;i <= L; ++ i) ch = getchar();
            for(;ch != '"';ch = getchar());
        }
        if(ch == 'j')
        {
            for(int i = 1;i <= 14; ++ i) ch = getchar();
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '=' || ch == '"';ch = getchar());
            if(ch == 's')
            {
                ch = getchar();
                if(ch == 't') 
                    L = 3, cur.element.justify_items = 0;
                else 
                    L = 10, cur.element.justify_items = 3;
            }
            if(ch == 'c')
                L = 5, cur.element.justify_items = 1;
            if(ch == 'e')
                L = 2, cur.element.justify_items = 2;
            for(int i = 1;i <= L; ++ i) ch = getchar();
            for(;ch != '"';ch = getchar());
        }
        if(ch == 'c')
        {
            for(int i = 1;i <= 4; ++ i) ch = getchar();
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '=' || ch == '"';ch = getchar());
            if(ch == 'r')
                L = 2, cur.element.color = 0;
            if(ch == 'b')
                L = 3, cur.element.color = 1;
            if(ch == 'g')
                L = 4, cur.element.color = 2;
            for(int i = 1;i <=  L; ++ i) ch = getchar();
            for(;ch != '"';ch = getchar());
        }
        if(ch == 'e')
            ch = getchar(), cur.element.em = 1;
        if(ch == 'i')
            cur.element.i = 1;
        if(ch == 'u')
            cur.element.u = 1;
        if(ch == '>') break;
    }
    return cur;
}
struct heading_string read_heading(int hp)
{
    char ch; int len = 0,L,fg = 0;
    struct heading_string cur;
    cur.element = (struct heading) { 0,0,0,0,0 };
    cur.height = 1, cur.width = 0, cur.id = hp;
    // get elements
    for(ch = getchar();ch != '>';ch = getchar())
    {
        for(;ch == ' ' || ch == '\n';ch = getchar());
        if(ch == 'c')
        {
            for(int i = 1;i <= 4; ++ i) ch = getchar();
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '=' || ch == '"';ch = getchar());
            if(ch == 'r')
                L = 2, cur.element.color = 0;
            if(ch == 'b')
                L = 3, cur.element.color = 1;
            if(ch == 'g')
                L = 4, cur.element.color = 2;
            for(int i = 1;i <=  L; ++ i) ch = getchar();
            for(;ch != '"';ch = getchar());
        }
        if(ch == 'e')
            ch = getchar(), cur.element.em = 1;
        if(ch == 'i')
            cur.element.i = 1;
        if(ch == 'u')
            cur.element.u = 1;
    }
    // get string
    for(ch = getchar();ch != '<';ch = getchar())
    {
        cur.s[len++] = ch;
        if(cur.s[len] >= 'a' && cur.s[len] <= 'z')
            cur.s[len] = cur.s[len] - 'a' + 'A';
    } cur.width = len;
    for(;ch != '>';ch = getchar());
    return cur;
}
struct paragragh_string read_paragragh(int pp)
{
    char ch; int len = 0,L,fg = 0;
    struct paragragh_string cur;
    cur.element = (struct paragragh) { 0,0,0,0,0 };
    cur.height = 1, cur.width = 0, cur.id = pp;
    // get elements
    for(ch = getchar();ch != '>';ch = getchar())
    {
        for(;ch == ' ' || ch == '\n';ch = getchar());
        if(ch == 'c')
        {
            for(int i = 1;i <= 4; ++ i) ch = getchar();
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '=' || ch == '"';ch = getchar());
            if(ch == 'r')
                L = 2, cur.element.color = 0;
            if(ch == 'b')
                L = 3, cur.element.color = 1;
            if(ch == 'g')
                L = 4, cur.element.color = 2;
            for(int i = 1;i <=  L; ++ i) ch = getchar();
            for(;ch != '"';ch = getchar());
        }
        if(ch == 'e')
            ch = getchar(), cur.element.em = 1;
        if(ch == 'i')
            cur.element.i = 1;
        if(ch == 'u')
            cur.element.u = 1;
    }
    // get string
    for(ch = getchar();ch != '<';ch = getchar())
        cur.s[len++] = ch;
    cur.width = len;
    for(;ch != '>';ch = getchar());
    return cur;
}
struct image_string read_image(int ip)
{
    char ch; int len = 0,L,fg = 0;
    struct image_string cur;
    cur.height = 1, cur.width = 0, cur.id = ip;
    for(ch = getchar();ch != '>' && ch != '<';ch = getchar())
    {
        for(;ch == ' ' || ch == '\n' || ch == '"';ch = getchar());
        if(ch == 's')
        {
            for(;ch != '"';ch = getchar());
            for(ch = getchar();ch != '"';ch = getchar())
                cur.s[len++] = ch;
        }
        if(ch == 'w')
        {
            for(;ch != '"';ch = getchar());
            scanf("%d",&cur.width);
        }
    }
    cur.height = len / cur.width;
    for(ch = getchar();ch != '>';ch = getchar());
    return cur;
}

int read(int divp)
{
    char ch = getchar();
    int mxwidth = 0,mxheight = 0,totwidth = 0,totheight = 0;
    struct div_string curd;
    struct heading_string curh;
    struct paragragh_string curp;
    struct image_string image;
    curd = nD[divp];
    curd.id = divp; curd.tot = 0;
    // curd.element = (struct div){ 0,0,0,0,0,0,0,0,0 };

    for(;ch != /*EOF*/ '#';ch = getchar())
    {
        // for(;ch == ' ' || ch == '\n' || ch == '"';ch = getchar());
        if(ch == '<')
        {
            for(ch = getchar();ch == ' ' || ch == '\n';ch = getchar());
            if(ch == '/') 
            { //
                char kind = getchar();
                for(ch = getchar();ch != '>';ch = getchar());
                nD[divp] = curd, nD[divp].id = divp;
                // if(nD[divp].element.direction == 1)
                //     nD[divp].element.height = mxheight, nD[divp].element.width = totwidth;
                // else
                //     nD[divp].element.height = totheight, nD[divp].element.width = mxwidth;
                if(nD[divp].element.height == 0)
                    nD[divp].element.height = nD[divp].element.direction == 1 ? mxheight : totheight;
                if(nD[divp].element.width == 0)
                    nD[divp].element.width = nD[divp].element.direction == 1 ? totwidth : mxwidth;
                return divp;
            }
            else
            {
                for(;ch == ' ' || ch == '\n';ch = getchar());
                if(num(ch) == 0)
                {
                    puts("hey div");
                    nD[++totd] = read_div(totd); int now = totd; read(totd);
                    curd.stk[++ curd.tot] = (struct kind){ 0,now };
                    mxheight = max(mxheight,nD[now].element.height);
                    mxwidth = max(mxwidth,nD[now].element.width);
                    totwidth += nD[now].element.width;
                    totheight += nD[now].element.height;
                }
                if(num(ch) == 1)
                {
                    puts("hey heading");
                    nH[++toth] = read_heading(toth); int now = toth;
                    curd.stk[++ curd.tot] = (struct kind){ 1,now };
                    mxheight = max(mxheight,nH[now].height);
                    mxwidth = max(mxwidth,nH[now].width);
                    totwidth += nH[now].width;
                    totheight += nH[now].height;
                }
                if(num(ch) == 2)
                {
                    puts("hey paragragh");
                    nP[++totp] = read_paragragh(totp); int now = totp;
                    curd.stk[++ curd.tot] = (struct kind){ 2,now };
                    mxheight = max(mxheight,nP[now].height);
                    mxwidth = max(mxwidth,nP[now].width);
                    totwidth += nP[now].width;
                    totheight += nP[now].height;
                }
                if(num(ch) == 3)
                {
                    puts("hey image");
                    nI[++toti] = read_image(toti); int now = toti;
                    curd.stk[++ curd.tot] = (struct kind){ 3,now };
                    mxheight = max(mxheight,nI[now].height);
                    mxwidth = max(mxwidth,nI[now].width);
                    totwidth += nI[now].width;
                    totheight += nI[now].height;
                }
            }
        }
    }
    nD[divp] = curd, nD[divp].id = divp;
    if(nD[divp].element.height == 0)
        nD[divp].element.height = nD[divp].element.direction == 1 ? mxheight : totheight;
    if(nD[divp].element.width == 0)
        nD[divp].element.width = nD[divp].element.direction == 1 ? totwidth : mxwidth;
}

void print(int divp)
{
    printf("div : %d---------------------------\n",divp);
    for(int i = 1;i <= nD[divp].tot; ++ i)
        printf("%d %d\n",nD[divp].stk[i].kind,nD[divp].stk[i].id);

    printf("width :%d\n",nD[divp].element.width);
    printf("height :%d\n",nD[divp].element.height);
    printf("direction :%d\n",nD[divp].element.direction);
    printf("align_items :%d\n",nD[divp].element.align_items);
    printf("justify_items :%d\n",nD[divp].element.justify_items);
    printf("color :%d\n",nD[divp].element.color);
    printf("em :%d\n",nD[divp].element.em);
    printf("i :%d\n",nD[divp].element.i);
    printf("u :%d\n",nD[divp].element.u);
    for(int i = 1;i <= nD[divp].tot; ++ i)
    {
        int opt = nD[divp].stk[i].kind,id = nD[divp].stk[i].id;
        if(opt == 0)
            print(id);
        if(opt == 1)
        {
            puts("******************************");
            for(int i = 0;i < nH[id].width; ++ i)
                printf("%c",nH[id].s[i]);
            puts("");
            printf("color :%d\n",nH[id].element.color);
            printf("width :%d\n",nH[id].width);
            printf("em :%d\n",nH[id].element.em);
            printf("i :%d\n",nH[id].element.i);
            printf("u :%d\n",nH[id].element.u);
        }
        if(opt == 2)
        {
            puts("******************************");
            for(int i = 0;i < nP[id].width; ++ i)
                printf("%c",nP[id].s[i]);
            puts("");
            printf("color :%d\n",nP[id].element.color);
            printf("width :%d\n",nP[id].width);
            printf("em :%d\n",nP[id].element.em);
            printf("i :%d\n",nP[id].element.i);
            printf("u :%d\n",nP[id].element.u);
        }
        if(opt == 3)
        {
            puts("******************************");
            for(int i = 0;i < nI[id].height; ++ i)
            {
                for(int j = 0;j < nI[id].width; ++ j)
                    printf("%c",nI[id].s[i * nI[id].width + j]);
                puts("");
            }
            puts("");
        }
    }
}

int main()
{
    // freopen("test_IO.in","r",stdin);
    // freopen("test_IO.out","w",stdout);
    nD[0].id = 0, nD[0].element.height = 0, nD[0].element.width = 0, nD[0].tot = 0;
    read(0);
    print(0);

    return 0;
}