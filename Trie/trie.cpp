#include <bits/stdc++.h>
using namespace std;

class Node
{

public:
    Node *child[26] = {nullptr};
    bool isWord = false;
    int cntEndWith = 0;
    int cntPrefix = 0;

    bool containsKey(char ch)
    {
        return (child[ch - 'a'] != nullptr);
    }

    void put(char ch, Node *node)
    {
        child[ch - 'a'] = node;
    }

    Node *get(char ch)
    {
        return child[ch - 'a'];
    }

    void setEnd()
    {
        isWord = true;
    }

    void remEnd()
    {
        isWord = false;
    }

    bool isEnd()
    {
        return isWord;
    }

    void increaseEnd()
    {
        ++cntEndWith;
    }

    void increasePrefix()
    {
        ++cntPrefix;
    }

    void deleteEnd()
    {
        --cntEndWith;
    }

    void reducePrefix()
    {
        --cntPrefix;
    }

    int getEnd()
    {
        return cntEndWith;
    }

    int getPrefix()
    {
        return cntPrefix;
    }
};

class Trie
{

private:
    Node *root;

public:
    Trie()
    {
        root = new Node();
    }

    // insert string into trie data structure
    void insert(string &word)
    {
        Node *temp = root;
        for (int i = 0; i < word.size(); ++i)
        {
            if (!temp->containsKey(word[i]))
                temp->put(word[i], new Node());
            temp = temp->get(word[i]);
            temp->increasePrefix();
        }
        temp->increaseEnd();
        temp->setEnd();
    }

    // if given word exist
    bool search(string &word)
    {
        Node *temp = root;
        for (int i = 0; i < word.size(); ++i)
        {
            if (!temp->containsKey(word[i]))
                return false;
            temp = temp->get(word[i]);
        }
        return temp->isEnd();
    }

    // if word with given prefix exist
    bool startsWith(string &prefix)
    {
        Node *temp = root;
        for (int i = 0; i < prefix.size(); ++i)
        {
            if (!temp->containsKey(prefix[i]))
                return false;
            temp = temp->get(prefix[i]);
        }
        return true;
    }

    // count frequency of given word
    int countWordsEqualTo(string &word)
    {
        Node *temp = root;
        for (int i = 0; i < word.size(); ++i)
        {
            if (temp->containsKey(word[i]))
                temp = temp->get(word[i]);
            else
                return 0;
        }
        return temp->getEnd();
    }

    // count words contains same given Prefix
    int countWordsStartingWith(string &word)
    {
        Node *temp = root;
        for (int i = 0; i < word.size(); ++i)
        {
            if (temp->containsKey(word[i]))
                temp = temp->get(word[i]);
            else
                return 0;
        }
        return temp->getPrefix();
    }

    // erase word
    // assuming that word exists
    void erase(string &word)
    {
        Node *temp = root;
        for (int i = 0; i < word.size(); ++i)
        {
            if (temp->containsKey(word[i]))
            {
                temp = temp->get(word[i]);
                temp->reducePrefix();
            }
            else
                return;
        }
        temp->deleteEnd();

        // if no more count of word exist then set isWord to false word not exist
        if (temp->getEnd() == 0)
            temp->remEnd();
    }
};

// Trie *obj = new Trie();
// obj->insert(word);
// obj->search(word); // is exist
// obj->startsWith(word); // prefix exist
// obj->countWordsEqualTo(word); // freq of word
// obj->countWordsStartingWith(str) // freq of prefix
// obj->erase(word);

int32_t main()
{
    Trie *obj = new Trie();

    vector<string> words = {"apple", "app", "apps", "apxe", "bac", "bat"};
    for (auto itr : words)
        obj->insert(itr);

    string str = "app";
    cout << obj->search(str) << endl;                 // 1
    cout << obj->startsWith(str) << endl;             // 1
    cout << obj->countWordsEqualTo(str) << endl;      // 1
    cout << obj->countWordsStartingWith(str) << endl; // 3

    obj->erase(str); // rem

    cout << obj->search(str) << endl; // 0

    return 0;
}