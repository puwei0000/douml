#ifndef BROWSEROPERATIONATTRIBUTE_H
#define BROWSEROPERATIONATTRIBUTE_H
#include "BrowserNode.h"
#include "BrowserOperation.h"
#include "OperationData.h"
#include "ParamData.h"
#include "Labeled.h"

class BrowserView;

class BrowserNodeAbstractRemove : public BrowserNode
{

protected:
    BrowserNodeAbstractRemove(BrowserView* view);
    virtual BrowserNode * duplicate(BrowserNode * , QString){return 0;}
    virtual void prepare_update_lib() const {}
    virtual void menu(){}
    virtual void apply_shortcut(QString ){}
    virtual UmlCode get_type() const {return UmlAssociation;}
    virtual QString get_stype() const {return QString();}
    virtual int get_identifier() const {return -1;}
    virtual BasicData * get_data() const {return 0;}
    virtual void save(QTextStream &, bool , QString & ){}

};


class BrowserOperationAttribute: public BrowserNodeAbstractRemove
{
    BrowserOperation* operation = nullptr;
    ParamData* data = nullptr;
public:
    BrowserOperationAttribute(BrowserView* view, BrowserOperation* _operation, ParamData* _data);
    void set_name(QString);
    QString get_name() const;
    void set_direction(QString);
    QString get_direction() const;
    void set_param_type(QString);
    AType get_param_type() const;
    void set_default_value(QString);
    QString get_default_value() const;
    void set_passage_type(QString);
    QString get_passage_type() const;
    bool is_writable() const
    {
        if(operation)
            return operation->is_writable();
        return false;
    }
    bool is_get_set()
    {
        return ((OperationData*)operation->get_data())->get_or_set();
    }
    void modified(){operation->package_modified();}
    virtual const QPixmap * pixmap(int) const;

};

class BrowserOperationReturnType: public BrowserNodeAbstractRemove
{
    BrowserOperation* operation = nullptr;
    OperationData* data;
public:
    BrowserOperationReturnType(BrowserView* view, BrowserOperation* _operation);
    void set_param_type(QString);
    AType get_param_type() const;
};
#endif // BROWSEROPERATIONATTRIBUTE_H
