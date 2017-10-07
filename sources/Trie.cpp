#include <iostream>
#include <cstring>
#include <cassert>
using namespace std;

const size_t max_sigma=26;

//Trie树的节点类
class Trienode
{
private:
    //儿子节点指针,使用定长数组，保证边的增加、访问、删除在O(1)时间内完成
    Trienode *next[max_sigma];
    int size;
    bool istail;
public:
    Trienode(){
		//初始化时，节点的度数为0，next指针全部赋空值
        memset(next, 0, sizeof(next));
        size=0;
        istail=false;
    }
	
    ~Trienode(){
        if(size)
			for(size_t i=0; i<max_sigma; i++)
                if(next[i]!=NULL)
                    delete next[i];
    }
	
	//查询操作。s:查询的字符串，i:当前所处第几个字符
    bool search(const char s[], size_t i = 0){
		//到达s的字符串尾部，表明成功找到了该字符串
        if(s[i]=='\0')
            return istail;
		
		//当前节点不具有相应儿子节点，表明该字符串不存在
        if(next[s[i]-'a'] == NULL)
            return false;
		
		//继续递归过程
        return next[s[i]-'a']->search(s, i+1);
    }
	
	//插入操作。s:查询的字符串，i:当前所处第几个字符
    void insert(const char s[], size_t i = 0){
		//当前前缀的容量+1
        size++;
		
		//到达s的字符串尾部，表明插入过程结束
        if(s[i] == '\0'){
			//对节点的卫星数据赋值，表示该节点是一个字符串尾端
            istail = true;
            return;
        }
		
		//若相应儿子节点不存在，创建新的节点
        if(next[s[i]-'a'] == NULL)
            next[s[i]-'a'] = new Trienode;
		
	    //继续递归过程
        next[s[i]-'a']->insert(s, i+1);
    }
	
	//删除操作。s:查询的字符串，i:当前所处第几个字符
	//该函数不对操作合法性进行检查，对Trie树中不存在的字符串调用该函数将导致不可预料的后果
    void erase(const char s[], size_t i = 0){
		//当前前缀容量-1
		size--;
		
        if(s[i]=='\0'){
            istail = false;
	        return;
        }
		
		//先递归处理儿子
        next[s[i]-'a']->erase(s, i+1);
		
		//若儿子容量为0，删除该儿子，释放相应空间
        if(next[s[i]-'a']->size == 0){
            delete next[s[i]-'a'];
            next[s[i]-'a'] = NULL;
        }
    }
};

int main ()
{
    Trienode root;
    char str1[] = "ok";
    char str2[] = "okay";
    bool ans1 = root.search(str1);
    assert(ans1 == false);
    root.insert(str1);
    root.insert(str2);
    root.erase(str1);
    bool ans2 = root.search(str2);
    assert(ans2 == true);
    bool ans3 = root.search(str1);
    assert(ans3 == false);
    return 0; 
}
