#include "StdAfx.h"
#include "Node.h"

namespace BASE
{
	Node::Node() : m_iID(-1)
	{

	}
	Node::Node(int iID) : m_iID(iID)
	{

	}
	Node::Node(const Node &c) : m_iID(c.m_iID)
	{

	}
}