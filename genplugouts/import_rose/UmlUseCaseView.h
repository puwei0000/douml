#ifndef _UMLUSECASEVIEW_H
#define _UMLUSECASEVIEW_H


#include "UmlBaseUseCaseView.h"
#include "Uc.h"
#include <QByteArray>

class UmlItem;
class File;

// This class manages 'use case view'
//
// You can modify it as you want (except the constructor)
class UmlUseCaseView : public UmlBaseUseCaseView, public Uc
{
public:
    UmlUseCaseView(void * id, const QByteArray & n) : UmlBaseUseCaseView(id, n) {
        cpt[kind()] += 1;
    };

    virtual UmlItem * item();

    virtual void readObject(File & f, QByteArray s);

    //read and create a new use case view, its name is the next token

    static void import(UmlItem * parent, File & f);

    //Just to not have warning
    virtual ~UmlUseCaseView();

};

#endif
