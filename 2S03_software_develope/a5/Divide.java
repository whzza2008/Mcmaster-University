class Divide extends Expr { // NOT BinaryOp!
  Expr left;
  Expr right;
  Divide(Expr x, Expr y) { left = x; right = y; }
  public String toString() { 
    return betweenParens(left) + " / " + betweenParens(right); }
  public boolean isGround() { return false; }
}
