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
    QColor color(50, 60, 70);
    auto result = utils::brightenColor(color);
    EXPECT_EQ(QColor(60, 70, 80), result);
}

TEST(HoverButtonTest, DarkenColor)
{
    QColor color(100, 80, 90);
    auto result = utils::darkenColor(color);
    EXPECT_EQ(QColor(80, 60, 70), result);
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