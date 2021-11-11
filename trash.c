#include<stdio.h>
typedef struct RGB {
    double r;
    double g;
     double b;
} RGB;
struct RGB colorConverter(int hexValue)
{
  RGB rgbColor;
  rgbColor.r = ((hexValue >> 16) & 0xFF) / 255.0;  // Extract the RR byte
  rgbColor.g = ((hexValue >> 8) & 0xFF) / 255.0;   // Extract the GG byte
  rgbColor.b = ((hexValue) & 0xFF) / 255.0;        // Extract the BB byte

  return rgbColor; 
}
int main(int argc, char const *argv[])
{
    int value;
    scanf("%x",&value);
    RGB new=colorConverter(value);
    printf("the value is %f",new.r,new.g,new.b);
    return 0;
}
