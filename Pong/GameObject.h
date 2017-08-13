#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H


class GameObject
{
    public:
        GameObject();
        virtual ~GameObject();
        float GetpositionX() { return positionX; }
        void SetpositionX(float val) { positionX = val; }
        float GetpositionY() { return positionY; }
        void SetpositionY(float val) { positionY = val; }
        float GetpositionZ() { return positionZ; }
        void SetpositionZ(float val) { positionZ = val; }
    protected:
    private:
        float positionX;
        float positionY;
        float positionZ;
};

#endif // GAMEOBJECT_H
