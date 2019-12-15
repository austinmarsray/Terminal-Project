#pragma once

class Node
{
private:
	int code;		//结点编号
	double longitude;	//经度
	double latitude;  //纬度
	double weight;    //权重
	Node *next;
public:
	Node() { next = nullptr; }

	Node(int code, double longitude, double latitude, double weight) 
		:code(code), longitude(longitude), latitude(latitude),weight(weight) { next = nullptr; }

	Node(const Node &node)
	{
		code = node.code;
		longitude = node.longitude;
		latitude = node.latitude;
		weight = node.weight;
		next = node.next;
	}

	void setinfo(int code, double longitude, double latitude, double weight)
	{
		this->code = code;
		this->longitude = longitude;
		this->latitude = latitude;
		this->weight = weight;
		next = nullptr;
	}
	bool hasNext()
	{
		if (next != nullptr)
			return true;
		else
			return false;
	}
	void setweight(double weight)
	{
		this->weight = weight;
	}
	void setNext(Node *nextNode)
	{
		next = nextNode;
	}
	friend class Graph;
};