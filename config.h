class OnlyOne
{
public:
        static const OnlyOne& Instance()
        {
                static OnlyOne theSingleInstance;
                return theSingleInstance;
        }
private:        
        OnlyOne(){};
        OnlyOne(const OnlyOne& root);
        OnlyOne& operator=(const OnlyOne&);
};