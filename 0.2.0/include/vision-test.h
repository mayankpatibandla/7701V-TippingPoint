/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature REDMOGO = vex::vision::signature (1, 6229, 8323, 7276, -975, -167, -571, 3, 0);
vex::vision::signature BLUEMOGO = vex::vision::signature (2, -3753, -3067, -3410, 2417, 10831, 6624, 3.1, 0);
vex::vision::signature YELLOWMOGO = vex::vision::signature (3, 749, 1159, 954, -3811, -3255, -3532, 7.2, 0);
vex::vision::signature SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision frontVisionSensor = vex::vision (vex::PORT11, 50, REDMOGO, BLUEMOGO, YELLOWMOGO, SIG_4, SIG_5, SIG_6, SIG_7);
/*vex-vision-config:end*/