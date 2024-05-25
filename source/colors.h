#pragma once
struct Color
{
    int r;
    int g;
    int b;
    int a;
};

inline Color color(int r, int g, int b, int a)
{
    Color theme;
    theme.r = r;
    theme.g = g;
    theme.b = b;
    theme.a = a;
    return theme;
}

const Color black = color(0, 0, 0, 255);
const Color border = color(128, 128, 128, 255);

const Color boardColors[10] =
{
    // O trong
    color(165, 160, 160, 255),

    // Hinh chu I (cyan)
    color(0, 255, 255, 255),

    // Hinh chu O (yellow)
    color(255, 255, 0, 255),

    // Hinh chu J (blue)
    color(0, 0, 255, 255),

    // Hinh chu L (orange)
    color(255, 127, 0, 255),

    // Hinh chu S (green)
    color(0, 255, 0, 255),

    // Hinh chu Z (red)
    color(255, 0, 0, 255),

    // Hinh chu T (purple)
    color(128, 0, 128, 255),

    // Bien ( mau xam )
    color(128, 128, 128, 255),

    // Hang ( mau trang )
    color(255, 255, 255, 255)
};


const Color pieceColors[7] =
{
    // Hinh chu I (cyan)
    color(0, 255, 255, 255),

    // Hinh chu O (yellow)
    color(255, 255, 0, 255),

    // Hinh chu J (blue)
    color(0, 0, 255, 255),

    // Hinh chu L (orange)
    color(255, 127, 0, 255),

    // Hinh chu S (green)
    color(0, 255, 0, 255),

    // Hinh chu Z (red)
    color(255, 0, 0, 255),

    // Hinh chu T (purple)
    color(128, 0, 128, 255),
};



