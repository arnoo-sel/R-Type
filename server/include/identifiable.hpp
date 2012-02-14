#ifndef IDENTIFIABLE
#define IDENTIFIABLE

class Identifiable
{
public:
    Identifiable();
    virtual ~Identifiable();
    int         getId() const;

private:
    int         _id;
    static int _nextId;
};

#endif // IDENTIFIABLE
