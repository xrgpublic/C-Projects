class Operand : public Expression
{
public:
    static Expression* parse(string& expr);
};
