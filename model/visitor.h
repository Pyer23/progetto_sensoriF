#ifndef VISITOR_H
#define VISITOR_H

namespace sensor{

class accelerometer;

class humiditysensor;
class humidityRHsensor;

class temperaturesensor;
class temperatureCsensor;

class visitor
{
public:
    virtual void visit(accelerometer* accelerometer) = 0;

    virtual void visit(humiditysensor* humiditysensor) = 0;
    virtual void visit(humidityRHsensor* humidityRHsensor) = 0;

    virtual void visit(temperaturesensor* temperaturesensor) = 0;
    virtual void visit(temperatureCsensor* temperatureCsensor) = 0;
};

}

#endif // VISITOR_H
