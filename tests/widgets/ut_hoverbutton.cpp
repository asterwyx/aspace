#include <gtest/gtest.h>
#include <QColor>
#include "hoverbutton.h"
#include "hoverbutton_p.h"
#include "common_def.h"
USE_USER_NAMESPACE

TEST(HoverButtonTest, RevertColor)
{
    QColor color(123, 134, 235);
    auto result = utils::revertColor(color);
    EXPECT_EQ(QColor(255 - 123, 255 - 134, 255 - 235), result);
}

TEST(HoverButtonTest, BrightenColor)
{
    QColor color(50, 55, 60);
    auto result = utils::brightenColor(color);
    EXPECT_EQ(QColor(60, 66, 72), result);
}

TEST(HoverButtonTest, DarkenColor)
{
    QColor color(100, 60, 50);
    auto result = utils::darkenColor(color);
    EXPECT_EQ(QColor(80, 48, 40), result);
}

TEST(HoverButtonTest, Background)
{
    HoverButton button;
    button.d_ptr->m_background = Qt::yellow;
    EXPECT_EQ(QColor(Qt::yellow), button.background());
    button.d_ptr->m_background = Qt::blue;
    EXPECT_EQ(QColor(Qt::blue), button.background());
}

TEST(HoverButtonTest, SetBackground)
{
    HoverButton button;
    button.setBackground(Qt::yellow);
    EXPECT_EQ(QColor(Qt::yellow), button.d_ptr->m_background);
    button.setBackground(Qt::blue);
    EXPECT_EQ(QColor(Qt::blue), button.d_ptr->m_background);
}