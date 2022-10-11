class Equals : public SubExpression
{
public:
    Equals(Expression* left, Expression* right) :
        SubExpression(left, right)
    {
    }
    int evaluate()
    {
        if (left->evaluate() == right->evaluate()) {
            return 1;
        }
        return 0;
    }
};
