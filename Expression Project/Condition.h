class Condition : public SubExpression
{
public:
    Condition(Expression* left, Expression* right, Expression* condition) :
        SubExpression(left, right,condition)
    {
    }
    int evaluate()
    {
        if (condition->evaluate() == 1) {
            return left->evaluate();
        }
        return right->evaluate();
    }
};
