#include <sys/ioctl.h>
#include <stdio.h>
#include <math.h>

void draw_bars(int *array, int size){
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    int ncols = w.ws_col;
    int wiggle = ncols - 15;
    double perc[size];

    int sum = 0;
    int i;
    for(i = 0; i < size; i++){
        sum += array[i];
    }
    
    for(i = 0; i < size; i++){
        int thenum = array[i];
        perc[i] = ((double)thenum/(double)sum) * 100;
    }
    
    // find max to find factor
    double themax = perc[0];
    for(i = 0; i < size; i++){
        if(perc[i] > themax){
            themax = perc[i];
        }
    }

    int factor = floor(wiggle/themax);
    
    for(i = 0; i < size; i++){
        int thenum = perc[i];
        printf("%0.1f%%\t", perc[i]);
        int m;
        for(m = 0; m < factor*thenum; m++){
            printf("#");
        }
        printf("\n");
    }
}