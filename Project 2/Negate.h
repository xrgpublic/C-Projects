class Negate : public SubExpression
{
public:
    Negate(Expression* left, Expression* right) :
        SubExpression(left, right)
    {
    }
    int evaluate()
    {
        if (left->evaluate() == 1) {
            return 0;
        }
        return 1;
    }
};
