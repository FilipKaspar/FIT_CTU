#include<stdio.h>
#include<math.h>


int vypocitaniobrazce()


int main(void){

    double a = 1,b = 1,c = 1, s;
    double area1, perimeter1, area2, perimeter2;
    char obrazec1, obrazec2;

    printf("Obrazec #1\n");

    scanf(" %c ", &obrazec1);

        switch(obrazec1){
            case'T':{
                if(scanf("%lf %lf %lf", &a, &b, &c) != 3 || a + b <= c || a + c <= b || c + b <= a
                   || (fabs((a + b) - c) <= 1e-9*fabs(a + b + c))){
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                s = (a + b + c) / (double)2;
                area1 = sqrt(s*((s-a)*(s-b)*(s-c)));
                perimeter1 = a + b + c;
                break;
            }
            case'R':{
                if(scanf("%lf %lf", &a, &b) != 2 || a <= 0 || b <= 0 || a == b){
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                area1 = a * b;
                perimeter1 = (double)2*(a + b);
                break;
            }
            case'S':{
                if(scanf("%lf", &a) != 1 || a <= 0){
                    printf("Nespravny vstup.\n");
                    return 1;
                }
                area1 = a * a;
                perimeter1 = (double)4 * a;
                break;
            }
            default:{
                printf("Nespravny vstup.\n");
                return 1;
            }
    }


    return 0;
}
