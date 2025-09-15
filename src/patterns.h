#ifndef CGL_PATTERNS_H
#define CGL_PATTERNS_H

#include <vector>

namespace cgl
{

class Simulation;

class Pattern
{
public:
    Pattern();
    virtual const char *name() const = 0;
    bool applyTo(Simulation *) const;
    virtual ~Pattern();

protected:
    Pattern(int reqRows, int reqCols);

private:
    int _requiredRows;
    int _requiredCols;

    virtual void markLiveCells(Simulation *) const = 0;
};

// ----------------------------------------------------------------------------

class Glider : public Pattern
{
public:
    const char *name() const override;

private:
    void markLiveCells(Simulation *) const override;
};

// ----------------------------------------------------------------------------

class Period2Oscillators : public Pattern
{
public:
    const char *name() const override;

private:
    void markLiveCells(Simulation *) const override;
};

class GosperGliderGun : public Pattern
{
public:
    GosperGliderGun();
    const char *name() const override;

private:
    void markLiveCells(Simulation *) const override;
};

// ----------------------------------------------------------------------------

class StillLifes : public Pattern
{
public:
    const char *name() const override;

private:
    void markLiveCells(Simulation *) const override;
};

// ----------------------------------------------------------------------------

class Spaceships : public Pattern
{
public:
    const char *name() const override;

private:
    void markLiveCells(Simulation *) const override;
};

// ----------------------------------------------------------------------------

class Pulsar : public Pattern
{
public:
    const char *name() const override;

private:
    void markLiveCells(Simulation *) const override;
};

// ----------------------------------------------------------------------------

class KoksGalaxy : public Pattern
{
public:
    const char *name() const override;

private:
    void markLiveCells(Simulation *) const override;
};

// ----------------------------------------------------------------------------

class PatternSelector
{
public:
    PatternSelector();
    const Pattern *selectedPattern() const;
    void moveForwards();
    void moveBackwards();
private:
    const std::vector<Pattern *> _patterns;
    const int _n;
    int _current;
};

} // namespace cgl

#endif // CGL_PATTERNS_H
