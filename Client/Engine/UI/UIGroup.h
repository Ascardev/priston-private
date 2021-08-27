#pragma once

namespace UI
{
	typedef std::shared_ptr<class Group> LPGROUP;

	class Group : public Element
	{
	public:
		Group();
		virtual ~Group();

		void SetGroup(std::shared_ptr<Group> pGroup) {m_pGroup = pGroup;}
		void SetIndexObject(int iID) {m_iID = iID;}

		int GetIndexObject() {return m_iID;}
		int GetType() {return TYPE_Group;}
		std::shared_ptr<class Group> GetGroup() { return m_pGroup; }
	protected:
		int m_iID = 0;
		std::shared_ptr<Group> m_pGroup = NULL;
	};
}