#ifndef APITRACEFILTER_H
#define APITRACEFILTER_H

#include <QRegExp>
#include <QSortFilterProxyModel>
#include <QStringList>

//LLL
#include "groupsfilter.h"

class ApiTrace;
class ApiTraceCall;

class ApiTraceFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    enum FilterOption {
        NullFilter        = 0,
        ExtensionsFilter  = 1 << 0,
        ResolutionsFilter = 1 << 1,
        ErrorsQueryFilter = 1 << 2,
        ExtraStateFilter  = 1 << 3,
        CustomFilter      = 1 << 4,
    };
    Q_DECLARE_FLAGS(FilterOptions, FilterOption)
public:
    explicit
    ApiTraceFilter(ApiTrace*, QObject *parent = 0);

    FilterOptions filterOptions() const;
    void setFilterOptions(FilterOptions opts);

    void setFilterRegexp(const QRegExp &regexp);
    QRegExp filterRegexp() const;

    void setCustomFilterRegexp(const QString &str);
    QString customFilterRegexp() const;

    QModelIndex indexForCall(ApiTraceCall *call) const;

//--- LLL >>>
    void setGroupsFilter(QStringList, int);
    bool usingGroup(QString) const;
    bool showGroupsOps()     const  {return m_groupsFilter.groupsops();}
    bool showRenderOps()     const  {return m_groupsFilter.renderops();}
    int  groupsTypeIndex()   const  {return m_groupsFilter.index();}

signals:
    void filterChanged(ApiTraceFilter*);
    void refreshFrames();
//<<< LLL ---
   
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const;

private:
    QRegExp m_regexp;
    FilterOptions m_filters;
    QRegExp m_customRegexp;
//LLL
    GroupsFilter m_groupsFilter;
};

#endif
