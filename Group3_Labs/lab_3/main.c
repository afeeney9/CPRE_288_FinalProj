#include "lcd.h"
#include "cyBot_uart.h"
#include "cyBot_Scan.h"
#include "Timer.h"
#include <math.h>

void printString(char *arr){
    int i=0;
    while(arr[i]){
        cyBot_sendByte(arr[i]);
        i++;
     }
    cyBot_sendByte('\n');
    cyBot_sendByte('\r');
}

int main(void) {
    timer_init();
    lcd_init();
    cyBOT_init_Scan(0b0011);
    cyBot_uart_init();
    right_calibration_value = 290500;
    left_calibration_value = 1235500;
    int i;
    int smallWidth[2] = {1000000,25000000};
    int objects[40];
    while(1){
    float distVals[91];
        char x = cyBot_getByte();
        if(x == 'm'){
          cyBOT_Scan_t scan;
          for(i=0; i<= 180; i+=2){
           cyBOT_Scan(i, &scan);
           distVals[i/2] = scan.sound_dist;
          }
          i = 1;
          int count = 0;
          int obj = 0;
          while(i<=91){
              if(distVals[i] - 4 < distVals[i-1] && distVals[i-1] < distVals[i]+4 && distVals[i-1] < 100){
                  count++;
              }else{
                  count =0;
              }
              if(count > 3){
                  obj++;
                  objects[(obj-1)*4] = obj;
                  objects[((obj-1)*4)+1] = i*2 - 8;
                  int dist = distVals[i-4]+distVals[i-3]+distVals[i-2]+distVals[i-1];
                  while(distVals[i] - 4 < distVals[i-1] && distVals[i-1] < distVals[i]+4 && distVals[i-1] < 100){
                      dist+= distVals[i];
                      count++;
                      i++;
                  }
                  objects[((obj-1)*4)+2] = dist/count;
                  objects[((obj-1)*4)+3] = i*2 - ((i-count)*2);

                  int width = ((dist/count) * (dist/count) *2) - (4* (dist/count) * cos(objects[((obj-1)*4)+3]));
                  if( width < smallWidth[0]){
                      smallWidth[0] = width;
                      smallWidth[1] = objects[((obj-1)*4)+1];
                  }
                  count = 0;
                  i--;
              }
              i++;
          }
          cyBOT_Scan(smallWidth[1], &scan);


               char buffer[100];
               char head[] = "Degrees        Distance  (cm)";
               printString(head);
               for(i =0; i <= 90; i++){
                   snprintf(buffer, 100, "%d              %f", i*2, distVals[i]);
                   printString(buffer);
               }
               char head2[] = "Object# Angle    Distance     Width";
               printString(head2);
               for(i = 0; i < obj; i++){
                   snprintf(buffer, 100, "%d        %d      %d           %d", objects[i*4], objects[(i*4)+1], objects[(i*4)+2], objects[(i*4)+3]);
                                  printString(buffer);
               }
               snprintf(buffer, 100, "smallest angle location: %d", smallWidth[1]);
                                             printString(buffer);
        }

    }
    return 0;
}

