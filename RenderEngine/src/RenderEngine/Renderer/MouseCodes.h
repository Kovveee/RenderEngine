#pragma once

using MouseCode = short int;
namespace MouseButton
{
	enum MouseCode
	{
		BUTTON0 = 0,
		BUTTON1 = 1,
		BUTTON2 = 2,
		BUTTON3 = 3,
		BUTTON4 = 4,
		BUTTON5 = 5,
		BUTTON6 = 6,
		BUTTON7 = 7,

		BUTTON_LAST = BUTTON7,
		BUTTON_LEFT = BUTTON1,
		BUTTON_RIGHT = BUTTON2,
		BUTTON_MIDDLE = BUTTON3
	};
}
