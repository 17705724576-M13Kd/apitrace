#ifndef GROUPS_H
#define GROUPS_H

#include <QStringList>

struct Groups {
    enum {GROUPS, RENDER};

    Groups()  : m_index(GROUPS), m_groupsops(false), m_renderops(false)
    {
    }

    Groups(QStringList strList, size_t index=GROUPS)
        : m_index(index), m_groupsops(false),
          m_renderops(false), m_groupsList(strList)
    {
        sanitize();
    }

    Groups(Groups const& groups)
    {
        *this = groups;                              // use Groups operator=
    }

    Groups & operator= (const Groups& other)
    {
        m_index      = other.m_index;
        m_groupsops  = other.m_groupsops;
        m_renderops  = other.m_renderops;
        m_groupsList = other.m_groupsList;           // QStringList operator=
        return *this;
    }

    bool operator== (const Groups& other) const
    {
        return (m_index      == other.m_index 
            &&  m_groupsops  == other.m_groupsops 
            &&  m_renderops  == other.m_renderops 
            &&  m_groupsList == other.m_groupsList); // QStringList operator==
    }

    bool operator!= (const Groups& other) const
    {
        return (!(*this == other));                  // use Groups operator==
    }

    bool contains(const QString &str) const
    {
        return m_groupsList.contains(str.split("/")[0]);
    }

    // Get
    size_t index() const
    {
         return m_index;
    }

    bool groupsops() const
    {
        return m_groupsops;
    }

    bool renderops() const
    {
        return m_renderops;
    }

    QStringList const & groupsList() const
    {
        return m_groupsList;
    }

    // Set
    void setIndex(size_t index)
    {
        m_index = index;
        if (GROUPS == m_index) {
            m_groupsops = m_groupsList.count() ? true : false;
            m_renderops = false;
        } else if (RENDER == m_index) {
            m_renderops = true;
            m_groupsops = false;
        }
    }
    void setGroupsList(QStringList groupsList)
    {
        m_groupsList = groupsList;
        sanitize();
    }

private:
    void sanitize()
    {
        m_groupsops = (m_groupsList.count() && (m_index == GROUPS));

        // Split any strings containing '/' for a single-call list
        QStringList tmplist;
        foreach (QString str, m_groupsList) {
            tmplist << str.split("/");
        }
        if (tmplist.count() > m_groupsList.count()) {
            m_groupsList = tmplist;
        }
    }

private:
    size_t m_index;
    bool   m_groupsops;
    bool   m_renderops;
    QStringList m_groupsList;
};

#endif // GROUPS_H
