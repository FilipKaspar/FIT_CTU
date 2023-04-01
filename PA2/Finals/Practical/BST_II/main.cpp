#include <string>
#include <cassert>

using namespace std;

class CTree
{
public:
    CTree() = default;
    ~CTree()
    {
        CNode * head = m_First;
        while(head != nullptr){
            CNode * tmp = head->m_NextOrder;
            delete head;
            head = tmp;
        }
    }
    CTree(const CTree &src) = delete;
    bool operator=(const CTree &other) = delete;
    bool isSet(string key)
    {
        CNode * n = m_Root;
        while (n)
        {
            if (key == n->m_Key)
                return true;
            else if (key > n->m_Key)
                n = n->m_R;
            else
                n = n->m_L;
        }
        return false;
    }
    bool insert(string key)
    {
        if(isSet(key)){
            return false;
        }

        auto * node = new CNode(key);

        if(m_Root == nullptr){
            m_Root = node;
            m_First = node;
            m_Last = node;
            return true;
        }

        CNode * prev = m_Root;

        while(prev->m_NextOrder != nullptr){
            prev = prev->m_NextOrder;
        }
        prev->m_NextOrder = node;
        node->m_PrevOrder = prev;

        CNode * head = m_Root;
        while(head != nullptr){
            if(key < head->m_Key){
                if(head->m_L == nullptr){
                    head->m_L = node;
                    break;
                }
                else{
                    head = head->m_L;
                }
            }
            else{
                if(head->m_R == nullptr){
                    head->m_R = node;
                    break;
                }
                else{
                    head = head->m_R;
                }
            }
        }

        m_Last = node;
        return true;
    }



    bool erase(string key)
    {
        if(!isSet(key)){
            return false;
        }

        CNode * head = m_Root;
        CNode * prev = head;

        while(head != nullptr){
            if(head->m_Key == key){
                // BST
                if(head->m_L == nullptr && head->m_R == nullptr){
                    update(prev, head, nullptr);
                }
                else if(head->m_L == nullptr){
                    CNode * replace = head->m_R;
                    update(prev, head, replace);
                }
                else if(head->m_R == nullptr){
                    CNode * replace = head->m_L;
                    update(prev, head, replace);
                }
                else{
                    CNode * tmp = head;
                    CNode * prev_last = tmp;
                    tmp = tmp->m_R;
                    while(tmp->m_L != nullptr){
                            prev_last = tmp;
                            tmp = tmp->m_L;
                    }

                    if(tmp->m_R != nullptr){
                        if(prev_last->m_L == tmp){
                            prev_last->m_L = tmp->m_L;
                        }
                        else{
                            prev_last->m_R = tmp->m_R;
                        }
                    }
                    else{
                        update(prev_last, tmp, nullptr);
                    }
                    update(prev, head, tmp);
                    if(tmp != head->m_L) tmp->m_L = head->m_L;
                    if(tmp != head->m_R) tmp->m_R = head->m_R;
                }

                // DLL
                if(head == m_First && head == m_Last){
                    m_Root = nullptr;
                    m_First = nullptr;
                    m_Last = nullptr;
                }
                else if(head == m_First){
                    CNode * new_one = head->m_NextOrder;
                    new_one->m_PrevOrder = nullptr;
                    m_First = new_one;
                }
                else if(head == m_Last){
                    CNode * new_one = head->m_PrevOrder;
                    new_one->m_NextOrder = nullptr;
                    m_Last = new_one;
                }
                else{
                    CNode * previous = head->m_PrevOrder;
                    CNode * next = head->m_NextOrder;
                    previous->m_NextOrder = next;
                    next->m_PrevOrder = previous;
                }
                delete head;
                return true;
            }
            else if(key < head->m_Key){
                prev = head;
                head = head->m_L;
            }
            else{
                prev = head;
                head = head->m_R;
            }
        }
        return false;
    }
protected:
    class CNode
    {
    public:
        CNode(string key) : m_Key(key) {}
        string m_Key;
        CNode * m_L = nullptr;
        CNode * m_R = nullptr;
        CNode * m_PrevOrder = nullptr;
        CNode * m_NextOrder = nullptr;
    };

    void update(CNode * prev, CNode * head, CNode * replace){
        if(prev == head){
            m_Root = replace;
        }
        else if(prev->m_L == head){
            prev->m_L = replace;
        }
        else{
            prev->m_R = replace;
        }
    }

    CNode * m_Root = nullptr;
    CNode * m_First = nullptr;
    CNode * m_Last = nullptr;
};

class CTester : public CTree
{
public:
    CTester () = default;
    void test()
    {
        CTester t0;
        assert(t0.insert("PA1")==true);
        assert(t0.m_First->m_Key=="PA1" && t0.m_First->m_NextOrder == nullptr);
        assert(t0.isSet("PA1")==true);
        assert(t0.insert("UOS")==true);
        assert(t0.insert("PA2")==true);
        assert(t0.isSet("PA2")==true);
        assert(t0.isSet("PA3")==false);

        assert(t0.insert("PA2")==false);
        assert(t0.insert("CAO")==true);
        assert(t0.insert("LIN")==true);
        assert(t0.insert("AAG")==true);
        assert(t0.insert("AG1")==true);
        assert(t0.insert("ZDM")==true);

        assert(t0.m_First->m_Key == "PA1"
               && t0.m_First->m_NextOrder->m_Key == "UOS"
               && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "PA2"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "CAO"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "LIN"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AAG"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AG1"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "ZDM");

        assert(t0.m_Last->m_Key == "ZDM"
               && t0.m_Last->m_PrevOrder->m_Key == "AG1"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "AAG"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "LIN"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "CAO"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA2"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "UOS"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA1");

        assert(t0.erase("")==false);

        assert(t0.erase("ZDM")==true);
        assert(t0.m_First->m_Key == "PA1"
               && t0.m_First->m_NextOrder->m_Key == "UOS"
               && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "PA2"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "CAO"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "LIN"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AAG"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AG1");
        assert(t0.m_Last->m_Key == "AG1"
               && t0.m_Last->m_PrevOrder->m_Key == "AAG"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "LIN"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "CAO"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA2"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "UOS"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA1");
        assert(t0.isSet("ZDM")==false);

        assert(t0.erase("AAG")==true);
        assert(t0.m_First->m_Key == "PA1"
               && t0.m_First->m_NextOrder->m_Key == "UOS"
               && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "PA2"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "CAO"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "LIN"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AG1");
        assert(t0.m_Last->m_Key == "AG1"
               && t0.m_Last->m_PrevOrder->m_Key == "LIN"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "CAO"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA2"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "UOS"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA1");
        assert(t0.isSet("AAG")==false);

        assert(t0.erase("CAO")==true);
        assert(t0.m_First->m_Key == "PA1"
               && t0.m_First->m_NextOrder->m_Key == "UOS"
               && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "PA2"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "LIN"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AG1");
        assert(t0.m_Last->m_Key == "AG1"
               && t0.m_Last->m_PrevOrder->m_Key == "LIN"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "PA2"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "UOS"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA1");
        assert(t0.isSet("CAO")==false);

        assert(t0.erase("UOS")==true);
        assert(t0.m_First->m_Key == "PA1"
               && t0.m_First->m_NextOrder->m_Key == "PA2"
               && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "LIN"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AG1");
        assert(t0.m_Last->m_Key == "AG1"
               && t0.m_Last->m_PrevOrder->m_Key == "LIN"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "PA2"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA1");
        assert(t0.isSet("UOS")==false);

        assert(t0.erase("UOS")==false);
        assert(t0.m_First->m_Key == "PA1"
               && t0.m_First->m_NextOrder->m_Key == "PA2"
               && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "LIN"
               && t0.m_First->m_NextOrder->m_NextOrder->m_NextOrder->m_Key == "AG1");
        assert(t0.m_Last->m_Key == "AG1"
               && t0.m_Last->m_PrevOrder->m_Key == "LIN"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "PA2"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_PrevOrder->m_Key == "PA1");
        assert(t0.isSet("UOS")==false);

        assert(t0.erase("LIN")==true);
        assert(t0.m_First->m_Key == "PA1"
               && t0.m_First->m_NextOrder->m_Key == "PA2"
               && t0.m_First->m_NextOrder->m_NextOrder->m_Key == "AG1");
        assert(t0.m_Last->m_Key == "AG1"
               && t0.m_Last->m_PrevOrder->m_Key == "PA2"
               && t0.m_Last->m_PrevOrder->m_PrevOrder->m_Key == "PA1");
        assert(t0.isSet("LIN")==false);

        assert(t0.erase("PA1")==true);
        assert(t0.m_First->m_Key == "PA2"
               && t0.m_First->m_NextOrder->m_Key == "AG1");
        assert(t0.m_Last->m_Key == "AG1"
               && t0.m_Last->m_PrevOrder->m_Key == "PA2");
        assert(t0.isSet("PA1")==false);

        assert(t0.erase("PA2")==true);
        assert(t0.m_First->m_Key == "AG1");
        assert(t0.m_Last->m_Key == "AG1");
        assert(t0.isSet("PA2")==false);

        assert(t0.erase("AG1")==true);
        assert(t0.m_First == t0.m_Last);
        assert(t0.isSet("AG1")==false);

        // FitWiki added
        assert(t0.erase("PA2")==false);

        assert(t0.insert("PA1")==true);
        assert(t0.insert("UOS")==true);
        assert(t0.insert("PA2")==true);
        assert(t0.insert("PA2")==false);
        assert(t0.insert("CAO")==true);
        assert(t0.insert("LIN")==true);
        assert(t0.insert("AAG")==true);
        assert(t0.insert("AG1")==true);
        assert(t0.insert("ZDM")==true);
        assert(t0.insert("FOO")==true);

        assert (t0.erase("CAO")==true);
        assert(t0.erase("CANNOT_ERASED")==false);
        assert (t0.erase("PA1")==true);
        assert (t0.erase("CAO")==false);
        assert (t0.erase("LIN")==true);
        assert (t0.erase("AAG")==true);
        assert (t0.erase("AG1")==true);
        assert (t0.erase("FOO")==true);
        assert (t0.erase("PA2")==true);
        assert (t0.erase("ZDM")==true);
        assert (t0.erase("UOS")==true);

        assert(t0.insert("PA1")==true);
        assert(t0.insert("UOS")==true);
        assert(t0.insert("PA2")==true);
        assert(t0.insert("PA2")==false);
        assert(t0.insert("CAO")==true);
        assert(t0.insert("LIN")==true);
        assert(t0.insert("AAG")==true);
        assert(t0.insert("AG1")==true);
        assert(t0.insert("ZDM")==true);

        assert (t0.erase("UOS")==true);
        assert (t0.erase("PA2")==true);
        assert (t0.erase("ZDM")==true);
        assert (t0.erase("PA1")==true);
        assert (t0.erase("AAG")==true);
        assert (t0.erase("AG1")==true);
        assert (t0.erase("LIN")==true);
        assert (t0.erase("CAO")==true);

        assert(t0.insert("PA1")==true);
        assert(t0.insert("CAO")==true);
        assert(t0.insert("UOS")==true);
        assert(t0.insert("PA2")==true);
        assert(t0.insert("PA2")==false);
        assert(t0.insert("LIN")==true);
        assert(t0.insert("AAG")==true);
        assert(t0.insert("AG1")==true);
        assert(t0.insert("ZDM")==true);

        assert (t0.erase("PA1")==true);
        assert (t0.erase("ZDM")==true);
        assert (t0.erase("UOS")==true);
        assert (t0.erase("PA2")==true);
        assert (t0.erase("AG1")==true);
        assert (t0.erase("CAO")==true);
        assert (t0.erase("AAG")==true);
        assert (t0.erase("LIN")==true);


        assert(t0.insert("20")==true);
        assert(t0.insert("10")==true);
        assert(t0.insert("5")==true);
        assert(t0.insert("15")==true);
        assert(t0.insert("17")==true);
        assert(t0.insert("13")==true);
        assert(t0.insert("14")==true);
        assert(t0.insert("11")==true);
        assert(t0.insert("12")==true);
        assert(t0.insert("3")==true);
        assert(t0.insert("7")==true);
        assert(t0.insert("25")==true);

        assert (t0.erase("10")==true);
        assert (t0.erase("25")==true);
        assert (t0.erase("20")==true);
        assert (t0.erase("17")==true);
    }
};

int main ( )
{
    CTester t;
    t.test();

    return EXIT_SUCCESS;
}