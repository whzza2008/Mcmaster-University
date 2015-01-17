class Minus extends Expr { // NOT BinaryOp!
  Expr left;
  Expr right;
  Minus(Expr x, Expr y) { left = x; right = y; }
  public String toString() { 
    return betweenParens(left) + " - " + betweenParens(right); }
  public boolean isGround() { return false; }
}
