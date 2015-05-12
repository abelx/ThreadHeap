#include <map>
using namespace std;
class CListNode;

class CFreeNodeTree
{
public:
	void Insert(CListNode*);
	CListNode* Delete(size_t);
	void Delete(CListNode*);
	bool Empty();
private:
	multimap<size_t, int> m_Tree;
};
