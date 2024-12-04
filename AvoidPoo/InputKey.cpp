#include "InputKey.h"

// 키보드 입력받는 함수
int InputKey::Input()
{
    int input = _getch();
    if (input == 224)
    {
        input = _getch();
    }

    switch (input)
    {
    case Key::UP:
        return Key::UP;
    case Key::DOWN:
        return Key::DOWN;
    case Key::LEFT:
        return Key::LEFT;
    case Key::RIGHT:
        return Key::RIGHT;
    case Key::SPACE:
        return Key::SPACE;
    case Key::R:
        return Key::R;
    case Key::W:
        return Key::W;
    default:
       return input;
        break;
    }
    
}
