#include <QLineEdit>
#include <QVariant>
#include <utility>
#include "scene/Renderer.h"
#include "SceneControllerTest.h"
#include "SceneMock.h"

TEST_F(SceneControllerTestFixture, testTextScene) {
 /* sut = new common::SceneController();
  QLineEdit *textFiled = new QLineEdit();
  textFiled->setObjectName("mText");
  textFiled->setText("testCase");
  std::shared_ptr<SceneMock> newEngine = std::make_shared<SceneMock>(0, nullptr);

  sut->registerNewScene(newEngine);
  sut->updateScenField(textFiled);

  QVariant propertyParameters = newEngine->property("sceneParameter");
  if (!propertyParameters.canConvert<QMap<QString, QVariant>>()) {
    ASSERT_TRUE(false);
  }

  QMap<QString, QVariant> parameters = propertyParameters.value<QMap<QString, QVariant>>();
  ASSERT_TRUE(parameters.contains("mText"));
  QString textValue = parameters["mText"].toString();
  EXPECT_EQ("testCase", textValue);*/
}