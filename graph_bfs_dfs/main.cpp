//
//  main.cpp
//  graph_bfs_dfs
//
//  Created by Igor Makaruks on 20/03/2015.
//  Copyright (c) 2015 Chewmba. All rights reserved.
//

#include <iostream>


#include <random>
#include <functional>

#include <vector>

#include <set>

#include <map>
#include <queue>

using namespace std;

/**
 * Definition for undirected graph.
 */
struct UndirectedGraphNode
{
	using Node = UndirectedGraphNode;

    int label;
    vector<UndirectedGraphNode *> neighbours;
    UndirectedGraphNode(int x) : label(x) {};

	using Visitor = function<void(UndirectedGraphNode*)>;

	void bfs(Visitor visitor)
	{
		set<Node*> qed;
		queue<Node*> q;
		q.push(this);
		qed.insert(this);	
		while (q.size() > 0)
		{
			auto current = q.front();
            q.pop();
			visitor(current);
			for (auto& x : current->neighbours)
			{
				if (qed.find(x) == qed.end())
				{
					q.push(x);
					qed.insert(x);
				}
			}

		} // while

	}

	string serialize()
	{
		string ser;
		auto nodeToString = [=, &ser] (UndirectedGraphNode* node)
		{
			string ret;
			ret = to_string(node->label);
			for (auto& x : node->neighbours)
			{
				ret = ret + ",";
				ret += to_string(x->label);
			}
			//return ret;
			ser = ser + ret + "#";
		};

		this->bfs(nodeToString);
		return ser;
	}	

    UndirectedGraphNode* clone()
    {
        map<Node*, Node*> nodesMap;
        //Node* ret = nullptr;
        auto visitor = [=, &nodesMap] (Node* node)
        {
            auto getNodeNew = [=, &nodesMap] (Node* node)
            {
                Node* nodeNew{nullptr};
                if (nodesMap.find(node) == nodesMap.end())
                {
                    nodeNew = new Node(node->label);
                    nodesMap[node] = nodeNew;
                }
                else
                    nodeNew = nodesMap[node];
                return nodeNew;
            }; // getNodeNew
            
            Node* nodeNew{getNodeNew(node)};
            
            for (auto& x : node->neighbours)
            {
                Node* neibNew{getNodeNew(x)};
                nodeNew->neighbours.push_back(neibNew);
            
            }
        
        };
        
        bfs(visitor);
        
        return nodesMap[this];
    
    }

	static UndirectedGraphNode* createFromString(const string& s)
	{
		set<int> processedSet;
		map<int, UndirectedGraphNode*> nodeMap;
		
		// creates single node
		auto createNode = [=,&processedSet, &nodeMap](const string& nodeString)
		{
			// Format "1,2,3,4,5"
			// where first element is this node's id
			// others - neighbours
			if (nodeString.size() == 0)
				return (UndirectedGraphNode*)nullptr;
			auto pos = nodeString.find(",");
			if (pos == string::npos)
			{
				auto ret = new UndirectedGraphNode(stoi(nodeString));
				return ret;
			}
			else
			{
				auto s = nodeString;
				int headValue = stoi(s.substr(0, pos));
				// remove processed part
				s.replace(0, pos+1, "");

				//auto head = new UndirectedGraphNode(headValue);
                //UndirectedGraphNode* head = nullptr;
                if (nodeMap.find(headValue) == nodeMap.end())
                {
                    auto head = new UndirectedGraphNode(headValue);
                    // add head to map
                    nodeMap[headValue] = head;
                }
                auto head = nodeMap[headValue];
				// add to processed set
				processedSet.insert(headValue);

				while (s.size() > 0)
				{
					pos = nodeString.find(",");
					int val{-1};
					if (pos == string::npos)
					{
						val = stoi(s);
						s.clear();
					}
					else
					{
						auto sval = s.substr(0, pos);
						val = stoi(sval);
						s.replace(0, pos+1, "");
					}
					
					//UndirectedGraphNode* neighbour = nullptr;
					if (nodeMap.find(val) == nodeMap.end())
					{
						auto neighbour = new UndirectedGraphNode(val);
						nodeMap[val] = neighbour;
					}
					
					head->neighbours.push_back(nodeMap[val]);
								
				} // while
				return head;
			} // else
		};

        auto tmp = s;
		UndirectedGraphNode* root = nullptr;
		bool finished = false;
	//	while ( tmp.size() > 0)
		while ( !finished)
		{
			auto pos = tmp.find("#");
			if (pos != string::npos)
			{
				auto s_ = tmp.substr(0, pos);
				cout << s_ << endl;
				tmp = tmp.substr(pos+1);
				auto r = createNode(s_);
				root = !root ? r : root;
			}
			else
			{
				cout << tmp << endl;
				auto r = createNode(tmp);
				root = !root ? r : root;
				finished = true;
			}
		}
		
		return root;
		//return nullptr;
	}
};



int main(int argc, const char * argv[])
{
	random_device rd;
	mt19937 engineMt(rd());

	uniform_int_distribution<int> unif100(0, 100);	
	auto random_100 = bind(unif100 , engineMt);

	string tmp = "0,1,2#1,2#2,2";

	auto graph = UndirectedGraphNode::createFromString(tmp);

    // insert code here...
    std::cout << "Hello, World!\n";
    
    cout << graph->serialize() << endl;
    
    auto g2 = graph->clone();
    cout << g2->serialize() << endl;
    
    return 0;
}
