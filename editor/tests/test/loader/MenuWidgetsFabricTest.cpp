#include "MenuWidgetsFabricTest.h"
#include <QSlider>
#include <QDial>
#include <QLineEdit>

TEST_F(MenuWidgetsFabricTestFixture, testCreateSliderWidget)
{
    QString sliderType = "QSlider";
    QVector<std::pair<QString, QString>> sliderParameters;
    sliderParameters.push_back(std::make_pair("minimum", "0"));
    sliderParameters.push_back(std::make_pair("maximum", "100"));

    auto newWidget = sut->createWidget(sliderType, sliderParameters);

    ASSERT_TRUE(newWidget);

    QSlider* slider = qobject_cast<QSlider*>(newWidget);

    ASSERT_TRUE(slider);
    EXPECT_EQ(0, slider->minimum());
    EXPECT_EQ(100, slider->maximum());
}

TEST_F(MenuWidgetsFabricTestFixture, testCreateDialWidget)
{
    QString sliderType = "QDial";
    QVector<std::pair<QString, QString>> sliderParameters;
    sliderParameters.push_back(std::make_pair("minimum", "0"));
    sliderParameters.push_back(std::make_pair("maximum", "100"));

    auto newWidget = sut->createWidget(sliderType, sliderParameters);

    ASSERT_TRUE(newWidget);

    QDial* slider = qobject_cast<QDial*>(newWidget);

    ASSERT_TRUE(slider);
    EXPECT_EQ(0, slider->minimum());
    EXPECT_EQ(100, slider->maximum());
}

TEST_F(MenuWidgetsFabricTestFixture, testCreateLineEditWidget)
{
    QString type = "QLineEdit";
    QVector<std::pair<QString, QString>> textAreaParameters;
    textAreaParameters.push_back(std::make_pair("text", "hello"));

    auto newWidget = sut->createWidget(type, textAreaParameters);

    ASSERT_TRUE(newWidget);

    QLineEdit* textArea = qobject_cast<QLineEdit*>(newWidget);

    ASSERT_TRUE(textArea);
    std::string text = textArea->text().toStdString();
    EXPECT_EQ("hello", text);
}
