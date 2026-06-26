#pragma once

class Input {
public:
    static bool teclaW;
    static bool teclaA;
    static bool teclaS;
    static bool teclaD;
    static bool teclaEspaco;
    static bool teclaR;
    static float anguloTorreta;

    static void handleKeyboard(unsigned char tecla, int x, int y);
    static void handleKeyboardUp(unsigned char tecla, int x, int y);
    static void handleSpecialKeys(int tecla, int x, int y);
};