#include "./engine/headers/entity.hpp"
#include "./engine/headers/physics.hpp"
#include "settings.hpp"

class Shape : public Entity {
    using Entity::Entity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, 120, 60 };
        DrawRectanglePro(rec, { 60, 30 }, m_angle, RED);
    }
};

class Block : public PhysicsEntity {
    using PhysicsEntity::PhysicsEntity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, 10, 10 };
        DrawRectanglePro(rec, { 5, 5 }, getBodyAngle(), RED);
    }
};

class Ground : public PhysicsEntity {
    using PhysicsEntity::PhysicsEntity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, 200, 30 };
        DrawRectanglePro(rec, { 100, 15 }, getBodyAngle(), BLACK);
    }
    void makeOpenAnimationStep() {
        m_body->SetTransform(b2Vec2(m_body->GetPosition().x + 0.01f, m_body->GetPosition().y), m_body->GetAngle());
    }
};

class Wall : public PhysicsEntity {
    using PhysicsEntity::PhysicsEntity;
public:
    void draw() {
        Rectangle rec = { m_position.x, m_position.y, 30, 200 };
        DrawRectanglePro(rec, { 15, 100 }, getBodyAngle(), BLACK);
    }
};