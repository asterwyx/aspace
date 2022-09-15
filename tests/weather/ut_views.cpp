#include <gtest/gtest.h>
#include "views/listview.h"
#include "weatherdata.h"
#include "views/listwidget.h"
USE_USER_NAMESPACE

TEST(ListViewTest, ListViewConstructAndDelete)
{
    ListView *view = new ListView;
    EXPECT_NE(nullptr, view);
    delete view;
}


TEST(ListViewTest, ScrollTo)
{
    ListView view;
    view.scrollTo(QModelIndex());
    SUCCEED();
}

TEST(ListViewTest, ListWidget)
{
    FutureWeather weather;
    ListWidget widget(&weather);
    EXPECT_EQ(LIST_WIDGET_HEIGHT, widget.height());
}