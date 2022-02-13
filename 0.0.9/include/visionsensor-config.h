/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature SIG_1 = vex::vision::signature (1, -2763, 1, -1381, -1, 9455, 4727, 0.7, 0);
vex::vision::signature SIG_2 = vex::vision::signature (2, 819, 6199, 3509, -873, 851, -11, 1, 0);
vex::vision::signature SIG_3 = vex::vision::signature (3, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 6425, 11257, 8841, -3439, -1919, -2679, 2.7, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 8129, 11797, 9963, -3305, -2259, -2782, 4.6, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision Vision1 = vex::vision (vex::PORT1, 150, SIG_1, SIG_2, SIG_3, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/