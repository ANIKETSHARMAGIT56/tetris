#include "../include/coordinates.h"
#include <stdio.h>
#include <stdint.h>
unsigned char match[4]={255,255,255,255};
int max(int a, int b, int c, int d)  
{
    if (a > b) {  
        if (a > c) {  
            if (a > d) {  
                return a;  
            }  
            else {  
                return d;  
            }  
        }  
    }  
    else if (b > c) {  
        if (b > d) {  
            return b;  
        }  
        else {
            return d;  
        }  
    }  
    else if (c > d) {  
        return c;  
    }  
    else {
        return d;  
    }
}
int min(int a, int b, int c, int d)  
{
    if (a < b) {  
        if (a < c) {  
            if (a < d) {  
                return a;  
            }  
            else {  
                return d;  
            }  
        }  
    }  
    else if (b < c) {  
        if (b < d) {  
            return b;  
        }  
        else {
            return d;  
        }  
    }  
    else if (c < d) {  
        return c;  
    }  
    else {
        return d;  
    }
}
void searchval(int shape,int orientation,int value)
{
    char index=0;
    for (int i = 0; i < 4; i++)
    {
       if (shapes[shape-1][orientation-1][i][0]==value)
       {
           match[index]=i;
           index++;
       }
        
    }
}
int16_t colldownfunc(int shape ,int orientation ,int box ,int xy)
{
    int p;
    for (int i = 0; i <=max(
        shapes[shape-1][orientation-1][0][0],
        shapes[shape-1][orientation-1][1][0],
        shapes[shape-1][orientation-1][2][0],
        shapes[shape-1][orientation-1][3][0]);
        i++)
    {
        
    }
    return p;
}
int main()
{
// printf("%d",colldownfunc(1,2,0,0));
// printf("%d\n",colldownfunc(1,2,0,1));
// printf("%d",colldownfunc(1,2,1,0));
// printf("%d\n",colldownfunc(1,2,1,1));
// printf("%d",colldownfunc(1,2,2,0));
// printf("%d\n",colldownfunc(1,2,2,1));
// printf("%d",colldownfunc(1,2,3,0));
// printf("%d\n",colldownfunc(1,2,3,1));
// printf("%d\n",min(-1,2,3,1));
searchval(1,1,2);
printf("%d\n",match[0]);
printf("%d\n",match[1]);
printf("%d\n",match[2]);


}