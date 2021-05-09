/*********************************************
* file:	~\tnd004\lab\lab4b\dsets.cpp         *
* remark: interface for disjoint sets        *
**********************************************/
 #pragma once

constexpr int defaultSize = 10;

class DSets
{
public:
    // -- CONSTRUCTORS
    explicit DSets(int theSize = defaultSize);

    // -- DESTRUCTOR
    ~DSets();

	//Disallow copying
	DSets(const DSets&) = delete;
	DSets& operator=(const DSets&) = delete;

    // -- MEMBER FUNCTIONS

    // create initial sets
    void init();

    // join sets named r and s where r != s
    // i.e. join trees with roots r and s
    void join(int r, int s);

    // return name of current set for x
    // i.e. return root of tree for x
    int find(int x);

    // just in case ...
    void print() const;

private:
    // -- DATA MEMBERS
    int *array;
    int  size;
};
