#pragma once

class Node
{
private:
	int code;		//�����
	double longitude;	//����
	double latitude;  //γ��
	double weight;    //Ȩ��
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