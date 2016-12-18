#ifndef UTILS_H
#define UTILS_H


class Utils
{
public:
    static void sleep(int msec);
    static void initRandoms();
    static double randomFloat();
    static double randomInRange(double fMin, double fMax);
    static double randomClamped();
};

#endif // UTILS_H
