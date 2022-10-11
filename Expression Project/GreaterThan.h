class GreaterThan : public SubExpression
{
public:
    GreaterThan(Expression* left, Expression* right) :
        SubExpression(left, right)
    {
    }
    int evaluate()
    {
        cout << left->evaluate() << " " << right->evaluate();
        if (left->evaluate() > right->evaluate()) {
            return 1;
        }
        return 0;
    }
};

