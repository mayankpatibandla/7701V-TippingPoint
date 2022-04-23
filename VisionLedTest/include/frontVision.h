/*vex-vision-config:begin*/
#include "vex.h"
vex::vision::signature F_SIG_1 = vex::vision::signature (1, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature F_SIG_2 = vex::vision::signature (2, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature F_SIG_3 = vex::vision::signature (3, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature F_SIG_4 = vex::vision::signature (4, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature F_SIG_5 = vex::vision::signature (5, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature F_SIG_6 = vex::vision::signature (6, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision::signature F_SIG_7 = vex::vision::signature (7, 0, 0, 0, 0, 0, 0, 2.5, 0);
vex::vision frontVision = vex::vision (vex::PORT3, 50, F_SIG_1, F_SIG_2, F_SIG_3, F_SIG_4, F_SIG_5, F_SIG_6, F_SIG_7);
/*vex-vision-config:end*/