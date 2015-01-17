package se2s03;

public class BadCode {
    
    
    public static int f5(int x, int y, int z) {
        int i,aa,bb,cc;
        i = (x * x) + 20;
        
        if (i <= 0) {
            bb = (z * y) - 11;
        }
        else{i = (y * y) + 20;
             bb = (41 * z) + (x - 56);}
        if (i <= 0) {
            cc = (x * x) * z;
        }
        else{i = (z * z) + 20;
             cc = (18 * y) + (y - x);}
        if (i <= 0) {
            aa = z - 41;
        }
        else{aa = (11 * x) + (56 - y);}
        return (aa + bb) + cc;
    }
}

