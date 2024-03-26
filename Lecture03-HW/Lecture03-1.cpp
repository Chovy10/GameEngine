#include <iostream>
#include <bitset>

enum ForeColour {
    Default = 0,
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
};

void changeTextColor(int colorCode) {
    std::cout << "\x1b[" << colorCode << "m";
}

void drawRectangle(int colorCode) {
    changeTextColor(colorCode);

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 10; ++j) {
            std::cout << "█";
        }
        std::cout << std::endl;
    }

    changeTextColor(Default);
}

int main() {
    std::cout << "화면에 그림을 그리는 프로그램입니다." << std::endl;
    std::cout << "학번: 202127009" << std::endl;
    std::cout << "이름: 신도훈" << std::endl;
    std::cout << "\x1b[033m" << "아름다운 색!! 우왕";


    /*
    * 흰색 블록을 그리는 키코드 : 1 (1)
    * 빨강색 블록을 그리는 키코드 : 2 (10)
    * 녹색 블록을 그리는 키코드 : 4 (100)
    * 노란색 블록을 그리는 키코드 : 8 (1000)
    * 청록색 블록을 그리는 키코드 : 16 (10000)
    * 마젠타색 블록을 그리는 키코드 : 32 (100000)
    * 프로그램 종료 : 64 (1000000)
    *
    * 프로그램을 시작하면 아래와 같이 쓰시오
    *
    *
    * 화면에 그림을 그리는 프로그램입니다.
    * 학번 : 349218347(본인학번)
    * 이름 : 본인이름
    *
    * 화면에 그릴 물체코드를 입력하세요 :
    * (반복)
    */
    std::cout << std::endl;

    int objectCode;
    while (true) {
        std::cout << "화면에 그릴 물체코드를 입력하세요: ";
        std::cin >> objectCode;

        if (objectCode == 64) {
            std::cout << "프로그램을 종료합니다." << std::endl;
            std::bitset<7> binaryCode(objectCode);
            std::cout << objectCode << "의 2진수 표현: " << binaryCode << std::endl;
            break;
        }
        else if (objectCode > 0 && objectCode <= 64) {
            std::bitset<7> binaryCode(objectCode);
            std::cout << objectCode << "의 2진수 표현: " << binaryCode << std::endl;

            int colorCode = White; 

          
            for (int i = 0; i < binaryCode.size(); ++i) {
                if (binaryCode.test(i)) {
                    switch (i) {
                    case 0:
                        colorCode = White;
                        break;
                    case 1:
                        colorCode = Red;
                        break;
                    case 2:
                        colorCode = Green;
                        break;
                    case 3:
                        colorCode = Yellow;
                        break;
                    case 4:
                        colorCode = Cyan;
                        break;
                    case 5:
                        colorCode = Magenta;
                        break;
                    default:
                        break;
                    }
                    drawRectangle(colorCode);
                }
            }
        }
        else {
            std::cout << "잘못된 입력입니다. 다시 입력해주세요." << std::endl;
        }
    }

    return 0;
}