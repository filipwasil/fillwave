#include <QLineEdit>
#include <QVariant>
#include <QMap>
#include <utility>
#include "scene/Renderer.h"
#include "SceneControllerTest.h"
#include "SceneMock.h"

TEST_F(SceneControllerTestFixture, testTextScene) {
  sut = new common::SceneController();
  std::pair<QString, QVariant> menuElement = {
      "mText",
      QVariant("testCase")
  };
  QMap<QString, QVariant> emptyVarList;
  std::shared_ptr<SceneMock> newEngine = std::make_shared<SceneMock>(1, nullptr, emptyVarList);

  sut->registerNewScene(newEngine);
  sut->updateScenField(menuElement);

  QVariant propertyParameters = newEngine->property("sceneParameter");
  if (!propertyParameters.canConvert<QMap<QString, QVariant>>()) {
    ASSERT_TRUE(false);
  }

  QMap<QString, QVariant> parameters = propertyParameters.value<QMap<QString, QVariant>>();
  ASSERT_TRUE(parameters.contains("mText"));
  QString textValue = parameters["mText"].toString();
  EXPECT_EQ("testCase", textValue);
}