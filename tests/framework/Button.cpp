/*
 * Button.cpp
 *
 *  Created on: Jan 17, 2016
 *      Author: filip
 */

#include <fillwave/Log.h>
#include <fillwave/Fillwave.h>
#include "../mocks/Button.h"

FLOGINIT_DEFAULT()

using namespace fillwave;
using namespace fillwave::framework;

using ::testing::AtLeast;
using ::testing::Return;

TEST(ButtonTest, CanBePicked) {
	GLchar* const argv[] = { "./" };
	Engine* engine = new Engine(1, argv);
	pTexture2D texture = engine->storeTexture("data/text.png");
	pTexture2D empty;

	glm::vec3 color(1.0, 1.0, 1.0);
	glm::vec2 position(1.0, 1.0);
	glm::vec2 scale(1.0, 1.0);

//	MockButton button = MockButton(engine, texture, position, scale);

	//EXPECT_CALL(<Which object>, <should call which function>).Times(AtLeast(how many times))
	//ON_CALL(button, pick(color)).Times(AtLeast(1));

//	EXPECT_TRUE(button.isPickable());

	texture.reset();
	delete engine;

}

int main(int argc, char** argv) {
  // The following line must be executed to initialize Google Mock
  // (and Google Test) before running the tests.
  ::testing::InitGoogleMock(&argc, argv);
  return RUN_ALL_TESTS();
}
