//
// Created by astrea on 9/10/22.
//
#pragma once
#include "hoverbutton.h"
BEGIN_USER_NAMESPACE
class HoverButtonPrivate {
private:
public:
    explicit HoverButtonPrivate(HoverButton *qPtr);
    void setBackground(const QColor &background);

private:
    Q_DECLARE_PUBLIC(HoverButton)
    HoverButton*    q_ptr;
    QColor          m_background;
    int             m_borderRadius;
    bool            m_hovered;
};


END_USER_NAMESPACE
