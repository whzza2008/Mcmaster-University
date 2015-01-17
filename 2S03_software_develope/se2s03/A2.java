package se2s03;

public class A2 {
    public int Rec(int n) {
        int a0 = 3, a1 = -2, an = 0 ;
        int x = 2, y = -1 ;
        
        if ( n == 0 ) return a0;
        if ( n == 1 ) return a1;
        
        for ( int i=2; i <= n; i++ ) {
            an= x * a0 + y * a1;
            a0 = a1;
            a1 = an;
        }
        return an;
    }
}
