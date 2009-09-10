#ifndef GRAVEYARDWIDGET_H
#define GRAVEYARDWIDGET_H

#include "cardpilewidget.h"

namespace client {

/**
 * @author MacJariel <MacJariel@gmail.com>
 */
class GraveyardWidget : public CardPileWidget
{
Q_OBJECT
public:
    GraveyardWidget(QWidget *parent = 0);
    ~GraveyardWidget();

    void init();

    virtual CardWidget* pop();
    virtual void push(CardWidget* card);

    void setFirstCard(const CardData&);
    void setSecondCard(const CardData&);

private:
    CardWidget* setCard(const CardData&);

    CardWidget* mp_firstCard;
    CardWidget* mp_secondCard;

};
}


#endif // GRAVEYARDWIDGET_H
