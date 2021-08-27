#pragma once

namespace BASE
{
	class Node
	{
	public:
		Node();
		Node(int iID);
		Node(const Node &c);
		virtual ~Node(){}

		int GetID() {return m_iID;}
		void SetID(int iID) {m_iID = iID;}
		virtual void Reset(){}
	private:
		int m_iID;
	};
}