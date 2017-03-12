#include "scene/Renderer.h"
#include <QLineEdit>
#include <QGLWidget>
#include <QMap>
#include <QVariant>
#include "SceneControllerTest.h"

TEST_F(SceneControllerTestFixture, testTextScene) {
    QGLWidget *textScene = new Renderer(0, nullptr);
    sut = new loader::SceneController(textScene);
    QLineEdit *textFiled = new QLineEdit();
    textFiled->setObjectName("mText");
    textFiled->setText("testCase");

    sut->updateScenField(textFiled);

    QVariant propertyParameters = textScene->property("sceneParameter");
    if (!propertyParameters.canConvert<QMap<QString, QVariant>>()) {
        ASSERT_TRUE(false);
    }
    QMap<QString, QVariant> parameters = propertyParameters.value<QMap<QString, QVariant>>();
    ASSERT_TRUE(parameters.contains("mText"));
    QString textValue = parameters["text"].toString();
    EXPECT_EQ("testCase", textValue);
}