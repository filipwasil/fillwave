#include "MenuWidgetsFabricTest.h"
#include <QSlider>
#include <QDial>
#include <QLineEdit>

TEST_F(MenuWidgetsFabricTestFixture, testCreateSliderWidget) {
    QString sliderType = "QSlider";
    QVector<std::pair<QString, QString>> sliderParameters;
    sliderParameters.push_back(std::make_pair("minimum", "1"));
    sliderParameters.push_back(std::make_pair("maximum", "100"));
    sliderParameters.push_back(std::make_pair("accesibleName", "TestCase"));
    sliderParameters.push_back(std::make_pair("maxWidth", "150"));

    auto newWidget = sut->createWidget(sliderType, sliderParameters);

    ASSERT_TRUE(newWidget);

    QSlider* slider = qobject_cast<QSlider*>(newWidget);

    ASSERT_TRUE(slider);
    EXPECT_EQ(1, slider->minimum());
    EXPECT_EQ(100, slider->maximum());

    std::string name = slider->accessibleName().toStdString();
    EXPECT_EQ("TestCase", name);

    EXPECT_EQ(150, slider->maximumWidth());
}

TEST_F(MenuWidgetsFabricTestFixture, testCreateDialWidget) {
    QString sliderType = "QDial";
    QVector<std::pair<QString, QString>> sliderParameters;
    sliderParameters.push_back(std::make_pair("minimum", "1"));
    sliderParameters.push_back(std::make_pair("maximum", "100"));
    sliderParameters.push_back(std::make_pair("accesibleName", "TestCase"));
    sliderParameters.push_back(std::make_pair("maxWidth", "150"));

    auto newWidget = sut->createWidget(sliderType, sliderParameters);

    ASSERT_TRUE(newWidget);

    QDial* slider = qobject_cast<QDial*>(newWidget);

    ASSERT_TRUE(slider);
    EXPECT_EQ(1, slider->minimum());
    EXPECT_EQ(100, slider->maximum());

    std::string name = slider->accessibleName().toStdString();
    EXPECT_EQ("TestCase", name);

    EXPECT_EQ(150, slider->maximumWidth());
}

TEST_F(MenuWidgetsFabricTestFixture, testCreateLineEditWidget) {
    QString type = "QLineEdit";
    QVector<std::pair<QString, QString>> textAreaParameters;
    textAreaParameters.push_back(std::make_pair("defaultText", "hello"));
    textAreaParameters.push_back(std::make_pair("accesibleName", "TestCase"));
    textAreaParameters.push_back(std::make_pair("maxWidth", "150"));

    auto newWidget = sut->createWidget(type, textAreaParameters);

    ASSERT_TRUE(newWidget);

    QLineEdit* textArea = qobject_cast<QLineEdit*>(newWidget);

    ASSERT_TRUE(textArea);
    std::string text = textArea->text().toStdString();
    EXPECT_EQ("hello", text);

    std::string name = textArea->accessibleName().toStdString();
    EXPECT_EQ("TestCase", name);

    EXPECT_EQ(150, textArea->maximumWidth());
}
