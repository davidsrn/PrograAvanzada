#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>

int population = 40000;
int lambda[3] = {6000, 10500, 8100};
int miuT = 3600;
double timePassed = 0;

int main(int argc, char* argv[]) {
  srand(time(0));
  int i = 0;
  int currentLambda = 0;
  double aTime = 0;
  double ssTime = 0;
  double sstart = 0, sends = 0, w=0, wq;

  for(i = 0; i < population; i++) {
    if(timePassed >= 60 && currentLambda < 2) {
      currentLambda++;
    }
    if(timePassed > 2*60){
      miuT = 4800;
    }
    if(i != 0) {
      aTime = aTime - ((1/lambda[currentLambda]) * log(rand()));
      printf("%lf ", aTime);
      ssTime = (1/miuT) * log(rand());
      printf("%lf\n ", ssTime);
      sends= ssTime + sstart;
      if(sends < aTime){
        sstart = aTime;
      }else{
        sstart = sends;
      }
    }
    w = sends - aTime;
    wq = sstart - aTime;
    printf("%lf\n", w);
  }
  return 0;
}
