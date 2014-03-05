//
//  main.c
//  pieceWiseLinearInterpolation
//
//  Created by wansong on 14-3-6.
//  Copyright (c) 2014年 No.Org. All rights reserved.
//

#include <stdio.h>

#define TemCnt 13

unsigned char cg[TemCnt] = {80, 75, 92, 121, 90,91,69, 100,99, 59, 83,92,100};
char cc[TemCnt] = {-5, 3, -1, 6, 20, -9, 0, 12, 31, 30, -29, 29, -12};
char cf[TemCnt] = {-1, 3, 4, 0, -5, 3, 9, 19, 31, 12, 14, 26, -3};
int tems[TemCnt] = {1441, 1480, 1510, 1550, 1586, 1630, 1700, 1790, 1860, 1900, 1960, 2000, 2100};

char getIndex(int curtem)
{//can ensure that user of this function can used the returned value "index" and "index+1" to calculate linear interpolation
//aimed at mcu programs where data mount is small so that char is enough
    char left = 0, right = TemCnt - 1, mid;
    while (left <= right) {
        mid = (left + right) >> 1;
        if (tems[mid] == curtem) {
            return mid;
        }
        else if(tems[mid] < curtem){
            left = mid + 1;
        }
        else{
            right = mid -1;
        }
    }
    if(right < 0){
        return 0;//if curtem is lower than the lowest, then index 0 and 1 will be used
    }
    else if(left >= TemCnt){
        return TemCnt - 2;//if curtem is higher than the highest, then index TemCnt-2 and TemCnt - 1 will be used
    }
    else{
        return right;//return index is from the left adjacent to the searched value (which does not in the tems table)
    }
}

void interPolation(int curtem, unsigned char *curcg, char *curcc, char *curcf)
{
    float tmp;
    char idx = getIndex(curtem);
    tmp = cg[idx] + (cg[idx+1] - cg[idx]) / (tems[idx+1] - tems[idx]) * (curtem - tems[idx]);
    if(tmp > 127.0){
        *curcg = 127;
    }
    else if(tmp < 0.0){
        *curcg = 0;
    }
    else{
        *curcg = (char)tmp;
    }
    tmp = cc[idx] + (cc[idx+1] - cc[idx]) / (tems[idx+1] - tems[idx]) * (curtem - tems[idx]);
    if(tmp > 63.0){
        *curcc = 63;
    }
    else if(tmp < 0.0){
        *curcc = 0;
    }
    else{
        *curcc = (char)tmp;
    }
    tmp = cf[idx] + (cf[idx+1] - cf[idx]) / (tems[idx+1] - tems[idx]) * (curtem - tems[idx]);
    if(tmp > 31.0){
        *curcf = 31;
    }
    else if(tmp < 0.0){
        *curcf = 0;
    }
    else{
        *curcf = (char)tmp;
    }
}

int main(int argc, const char * argv[])
{

    // insert code here...
    printf("Hello, World!\n");
    return 0;
}

