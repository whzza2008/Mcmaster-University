class Plus extends BinaryOp {
  Plus(Expr x, Expr y) { left = x; right = y; }
  public String toString() { 
    // we are the context
    return super.toString(this, " + "); }
  public boolean isSame(Expr e) { return e instanceof Plus; }
}
