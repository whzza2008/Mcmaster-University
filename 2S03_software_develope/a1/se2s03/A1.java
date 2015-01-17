package se2s03;

public class A1 {
    public int cases(int v, int u, int w) {
        if(v<=3){
            if (u<=-5){
                if(w<=12){
                    return 7;
                }
                else{
                    return 9;
                }
            }
            else{
               if(w<=4){return 10;}
               else {return 1;}
            }
        }
        else{
            if(w<=2){
                if(u<=9){return 6;}
                else {return 3;}
            }
            else{
                if(u<=-6){return 5;}
                else{return 2;}
            }
        }
    } 
}
