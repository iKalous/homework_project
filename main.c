#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "element.h"
#include "minmax.h"

int flag[15][55]; // = 1 starter = 2 ender
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
        for(;ch == ' ' || ch == '\n' || ch == '\t';ch = getchar());
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
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '\t' || ch == '=' || ch == '"';ch = getchar());
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
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '\t' || ch == '=' || ch == '"';ch = getchar());
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
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '\t' || ch == '=' || ch == '"';ch = getchar());
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
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '\t' || ch == '=' || ch == '"';ch = getchar());
            if(ch == 'r')
                L = 2, cur.element.color = 1;
            if(ch == 'b')
                L = 3, cur.element.color = 2;
            if(ch == 'g')
                L = 4, cur.element.color = 3;
            if(ch == 'w')
                L = 4, cur.element.color = 0;
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
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '\t' || ch == '=' || ch == '"';ch = getchar());
            if(ch == 'r')
                L = 2, cur.element.color = 1;
            if(ch == 'b')
                L = 3, cur.element.color = 2;
            if(ch == 'g')
                L = 4, cur.element.color = 3;
            if(ch == 'w')
                L = 4, cur.element.color = 0;
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
        if(cur.s[len - 1] >= 'a' && cur.s[len - 1] <= 'z')
            cur.s[len - 1] = cur.s[len - 1] - 'a' + 'A';
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
        for(;ch == ' ' || ch == '\n' || ch == '\t';ch = getchar());
        if(ch == 'c')
        {
            for(int i = 1;i <= 4; ++ i) ch = getchar();
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '\t' || ch == '=' || ch == '"';ch = getchar());
            if(ch == 'r')
                L = 2, cur.element.color = 1;
            if(ch == 'b')
                L = 3, cur.element.color = 2;
            if(ch == 'g')
                L = 4, cur.element.color = 3;
            if(ch == 'w')
                L = 4, cur.element.color = 0;
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
        for(;ch == ' ' || ch == '\n' || ch == '\t' || ch == '"';ch = getchar());
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
    struct image_string curi;
    curd = nD[divp];
    curd.id = divp; curd.tot = 0;

    for(;ch != EOF;ch = getchar())
    {
        if(ch == '<')
        {
            for(ch = getchar();ch == ' ' || ch == '\n' || ch == '\t';ch = getchar());
            if(ch == '/') 
            { //
                char kind = getchar();
                for(ch = getchar();ch != '>';ch = getchar());
                nD[divp] = curd, nD[divp].id = divp;
                if(nD[divp].element.height == 0)
                    nD[divp].element.height = nD[divp].element.direction == 1 ? mxheight : totheight;
                if(nD[divp].element.width == 0)
                    nD[divp].element.width = nD[divp].element.direction == 1 ? totwidth : mxwidth;
                return divp;
            }
            else
            {
                for(;ch == ' ' || ch == '\n' || ch == '\t';ch = getchar());
                if(num(ch) == 0)
                {
                    nD[++totd] = read_div(totd); int now = totd; read(totd);
                    curd.stk[++ curd.tot] = (struct kind){ 0,now };
                    mxheight = max(mxheight,nD[now].element.height);
                    mxwidth = max(mxwidth,nD[now].element.width);
                    totwidth += nD[now].element.width;
                    totheight += nD[now].element.height;
                }
                if(num(ch) == 1)
                {
                    nH[++toth] = read_heading(toth); int now = toth;
                    curd.stk[++ curd.tot] = (struct kind){ 1,now };
                    mxheight = max(mxheight,nH[now].height);
                    mxwidth = max(mxwidth,nH[now].width);
                    totwidth += nH[now].width;
                    totheight += nH[now].height;
                }
                if(num(ch) == 2)
                {
                    nP[++totp] = read_paragragh(totp); int now = totp;
                    curd.stk[++ curd.tot] = (struct kind){ 2,now };
                    mxheight = max(mxheight,nP[now].height);
                    mxwidth = max(mxwidth,nP[now].width);
                    totwidth += nP[now].width;
                    totheight += nP[now].height;
                }
                if(num(ch) == 3)
                {
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

int get(int H,int h,int tot,int opt)
{
    if(opt == 0) return 0;
    if(opt == 1 || opt == 3) return (H - h) / (tot + 1);
    if(opt == 2) return (H - h);
}

void pushdown_div(int divp,int p)
{
    struct div cur = nD[divp].element;
    if(nD[p].element.color == 0)
        nD[p].element.color = cur.color;
    if(nD[p].element.em == 0)
        nD[p].element.em = cur.em;
    if(nD[p].element.i == 0)
        nD[p].element.i = cur.i;
    if(nD[p].element.u == 0)
        nD[p].element.u = cur.u;
}
void pushdown_heading(int divp,int p)
{
    struct div cur = nD[divp].element;
    if(nH[p].element.color == 0)
        nH[p].element.color = cur.color;
    if(nH[p].element.em == 0)
        nH[p].element.em = cur.em;
    if(nH[p].element.i == 0)
        nH[p].element.i = cur.i;
    if(nH[p].element.u == 0)
        nH[p].element.u = cur.u;
}
void pushdown_paragragh(int divp,int p)
{
    struct div cur = nD[divp].element;
    if(nP[p].element.color == 0)
        nP[p].element.color = cur.color;
    if(nP[p].element.em == 0)
        nP[p].element.em = cur.em;
    if(nP[p].element.i == 0)
        nP[p].element.i = cur.i;
    if(nP[p].element.u == 0)
        nP[p].element.u = cur.u;
}
void pushdown_image() {}

void draw(int divp,int x1,int y1,int x2,int y2)
{
    int dx = 0,dy = 0,px = 0,py = 0;
    struct div_string curd = nD[divp];
    struct heading_string curh;
    struct paragragh_string curp;
    struct image_string curi;

    int totheight = 0,totwidth = 0;
    for(int i = 1;i <= curd.tot; ++ i)
    {
        int opt = curd.stk[i].kind,id = curd.stk[i].id;
        if(opt == 0)
            totheight += nD[id].element.height, totwidth += nD[id].element.width;
        if(opt == 1)
            totheight += 1, totwidth += nH[id].width;
        if(opt == 2)
            totheight += 1, totwidth += nP[id].width;
        if(opt == 3)
            totheight += nI[id].height, totwidth += nI[id].width;
    }
    
    int align = curd.element.align_items, justify = curd.element.justify_items;
    if(align == 0) dx = 0;
    if(align == 1) 
        dx += (curd.element.height - totheight) / 2;
    if(align == 2) 
        dx += curd.element.height - totheight;
    if(align == 3) 
        dx += (curd.element.height - totheight) / (curd.tot + 1), px = dx;
    
    if(justify == 0) dy = 0;
    if(justify == 1) 
        dy += (curd.element.width - totwidth) / 2;
    if(justify == 2) 
        dy += curd.element.width - totwidth;
    if(justify == 3) 
        dy += (curd.element.width - totwidth) / (curd.tot + 1), py = dy;

    if(curd.element.direction == 0) // in row
    {
        for(int i = 1;i <= curd.tot; ++ i)
        {
            int opt = curd.stk[i].kind,id = curd.stk[i].id;
            if(opt == 0)
            {
                dy = get(curd.element.width,nD[id].element.width,1,justify);
                pushdown_div(divp,id);
                draw(curd.stk[i].id,x1 + dx,y1 + dy,x1 + dx + nD[id].element.height - 1,y1 + dy + nD[id].element.width - 1);
                dx += nD[id].element.height;
            }
            if(opt == 1)
            {
                dy = get(curd.element.width,nH[id].width,1,justify);
                pushdown_heading(divp,id);
                flag[dx + x1][dy + y1 + 0] += 1;
                flag[dx + x1][dy + y1 + nH[id].width - 1] += 2;
                for(int i = 0;i < nH[id].width; ++ i)
                    map[dx + x1][dy + y1 + i].h = nH[id].element,
                    map[dx + x1][dy + y1 + i].h.ch = nH[id].s[i],
                    map[dx + x1][dy + y1 + i].id = 1;
                ++dx;
            }
            if(opt == 2)
            {
                dy = get(curd.element.width,nP[id].width,1,justify);
                pushdown_paragragh(divp,id);
                flag[dx + x1][dy + y1 + 0] += 1;
                flag[dx + x1][dy + y1 + nP[id].width - 1] += 2;
                for(int i = 0;i < nP[id].width; ++ i)
                    map[dx + x1][dy + y1 + i].p = nP[id].element,
                    map[dx + x1][dy + y1 + i].p.ch = nP[id].s[i],
                    map[dx + x1][dy + y1 + i].id = 2;
                ++dx;
            }
            if(opt == 3)
            {
                dy = get(curd.element.width,nI[id].width,1,justify);
                pushdown_image(divp,id);
                for(int i = 0;i < nI[id].height; ++ i)
                    for(int j = 0;j < nI[id].width; ++ j)
                        map[dx + x1 + i][dy + y1 + j].img = nI[id].element,
                        map[dx + x1 + i][dy + y1 + j].img.ch = nI[id].s[i * nI[id].width + j],
                        map[dx + x1 + i][dy + y1 + j].id = 3;
                dx += nI[id].height;
            } 
            dx += px;
        }
    }
    else
    {
        for(int i = 1;i <= curd.tot; ++ i)
        {
            int opt = curd.stk[i].kind,id = curd.stk[i].id;
            if(opt == 0)
            {
                dx = get(curd.element.height,nD[id].element.height,1,align);
                pushdown_div(divp,id);
                draw(curd.stk[i].id,x1 + dx,y1 + dy,x1 + dx + nD[id].element.height - 1,y1 + dy + nD[id].element.width - 1);
                dy += nD[id].element.width;
            }
            if(opt == 1)
            {
                dx = get(curd.element.height,1,1,align);
                pushdown_heading(divp,id);
                flag[dx + x1][dy + y1 + 0] += 1;
                flag[dx + x1][dy + y1 + nH[id].width - 1] += 2;
                for(int i = 0;i < nH[id].width; ++ i)
                    map[dx + x1][dy + y1 + i].h = nH[id].element,
                    map[dx + x1][dy + y1 + i].h.ch = nH[id].s[i],
                    map[dx + x1][dy + y1 + i].id = 1;
                dy += nH[id].width;
            }
            if(opt == 2)
            {
                dx = get(curd.element.height,1,1,align);
                pushdown_paragragh(divp,id);
                flag[dx + x1][dy + y1 + 0] += 1;
                flag[dx + x1][dy + y1 + nP[id].width - 1] += 2;
                for(int i = 0;i < nP[id].width; ++ i)
                    map[dx + x1][dy + y1 + i].p = nP[id].element,
                    map[dx + x1][dy + y1 + i].p.ch = nP[id].s[i],
                    map[dx + x1][dy + y1 + i].id = 2;
                dy += nP[id].width;
            }
            if(opt == 3)
            {
                dx = get(curd.element.height,nI[id].height,1,align);
                pushdown_image(divp,id);
                for(int i = 0;i < nI[id].height; ++ i)
                    for(int j = 0;j < nI[id].width; ++ j)
                        map[dx + x1 + i][dy + y1 + j].img = nI[id].element,
                        map[dx + x1 + i][dy + y1 + j].img.ch = nI[id].s[i * nI[id].width + j],
                        map[dx + x1 + i][dy + y1 + j].id = 3;
                dy += nI[id].width;
            }
            dy += py;
        }
    }
}

int check = 0;

void print_heading(struct heading cur)
{
    if(cur.color == 1) printf("\033[31m"), check = 1;
    if(cur.color == 2) printf("\033[34m"), check = 1;
    if(cur.color == 3) printf("\033[32m"), check = 1;
    if(cur.em == 1) printf("\033[1m"), check = 1;
    if(cur.i == 1) printf("\033[3m"), check = 1;
    if(cur.u == 1) printf("\033[4m"), check = 1;
    printf("%c",cur.ch);
}
void print_paragragh(struct paragragh cur)
{
    if(cur.color == 1) printf("\033[31m"), check = 1;
    if(cur.color == 2) printf("\033[34m"), check = 1;
    if(cur.color == 3) printf("\033[32m"), check = 1;
    if(cur.em == 1) printf("\033[1m"), check = 1;
    if(cur.i == 1) printf("\033[3m"), check = 1;
    if(cur.u == 1) printf("\033[4m"), check = 1;
    printf("%c",cur.ch);
}
void print_image(struct image cur)
{
    printf("%c",cur.ch);
}

void print()
{
    for(int i = 0;i < 10; ++ i)
    {
        check = 0;
        for(int j = 0;j < 50; ++ j)
        {
            int id = map[i][j].id;
            if(id == 0) printf(" ");
            if(id == 1) 
            {
                if(flag[i][j] == 1)
                    check = 0, print_heading(map[i][j].h);
                else if(flag[i][j] == 2 && check)
                    printf("%c\033[0m",map[i][j].h.ch);
                else if(flag[i][j] == 3)
                {
                    check = 0, print_heading(map[i][j].h);
                    if(check) printf("\033[0m");
                }
                else printf("%c",map[i][j].h.ch);
            }
            if(id == 2) 
            {
                if(flag[i][j] == 1)
                    check = 0, print_paragragh(map[i][j].p);
                else if(flag[i][j] == 2 && check)
                    printf("%c\033[0m",map[i][j].p.ch);
                else if(flag[i][j] == 3)
                {
                    check = 0, print_paragragh(map[i][j].p);
                    if(check) printf("\033[0m");
                }
                else printf("%c",map[i][j].p.ch);
            }
            if(id == 3) print_image(map[i][j].img);
        }
        puts("");
    }
}

int main()
{
    freopen("test_IO.in","r",stdin);
    freopen("test_IO.out","w",stdout);
    nD[0].id = 0, nD[0].element.height = 0, nD[0].element.width = 0, nD[0].tot = 0;
    read(0);
    nD[0].element.height = 10, nD[0].element.width = 50;
    for(int i = 1;i <= totd; ++ i)
        if(nD[i].element.width == 0 || nD[i].element.height == 0) nD[i].element.width = 0, nD[i].element.height = 0;
    draw(0,0,0,9,49);
    print();
    return 0;
}