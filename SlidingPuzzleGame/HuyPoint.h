#pragma once
class HuyPoint
{
    public:
        int X;
        int Y;

        HuyPoint() : HuyPoint(0, 0) {
        }

        HuyPoint(int x, int y) {
            this->X = x;
            this->Y = y;
        }
};

