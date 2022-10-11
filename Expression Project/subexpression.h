class SubExpression : public Expression
{
public:
    SubExpression(Expression* left, Expression* right);
    SubExpression(Expression* left, Expression* right, Expression* condition);
    static Expression* parse(string& expr);
protected:
    Expression* left;
    Expression* right;
    Expression* condition;
    Expression* newLeft = 0;
    Expression* newRight = 0;
};
