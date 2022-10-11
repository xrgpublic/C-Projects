class Or : public SubExpression
{
public:
    Or(Expression* left, Expression* right) :
        SubExpression(left, right)
    {
    }
    int evaluate()
    {
        if (left->evaluate() == 1 || right->evaluate() == 1) {
            return 1;
        }
        return 0;
    }
};