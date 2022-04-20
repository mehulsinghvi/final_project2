#include <catch2/catch.hpp>

#include <collision_logic.h>
using glm::vec2;

TEST_CASE("test initialization and get-set for paddle") {
    glm::vec2 paddle_corner = glm::vec2 (10,10);
    glm::vec2 paddle_velocity = glm::vec2 (0,10);
    glm::vec2 paddle_size = glm::vec2 (1,2);
    glm::vec2 paddle_distance = glm::vec2 (20,20);
    finalproject::Paddle paddle = finalproject::Paddle(paddle_corner, paddle_velocity,
                                                       paddle_size, paddle_distance, 10);
    SECTION("basic") {
        REQUIRE (paddle.GetVelocity() == paddle_velocity);
        REQUIRE (paddle.GetPosition() == paddle_corner);
    }
    SECTION("test set velocity") {
        vec2 vel2(2, 1);
        paddle.SetVelocity(vel2);
        REQUIRE (paddle.GetVelocity() == vel2);
        REQUIRE (paddle.GetPosition() == paddle_corner);
    }
    SECTION("test set position") {
        vec2 loc2(2, 1);
        paddle.SetPosition(loc2);
        REQUIRE (paddle.GetVelocity() == paddle_velocity);
        REQUIRE (paddle.GetPosition() == loc2);
    }
}

TEST_CASE("test slide paddle") {
    glm::vec2 paddle_corner = glm::vec2 (10,10);
    glm::vec2 paddle_velocity = glm::vec2 (0,10);
    glm::vec2 paddle_size = glm::vec2 (1,2);
    glm::vec2 paddle_distance = glm::vec2 (20,20);
    finalproject::Paddle paddle = finalproject::Paddle(paddle_corner, paddle_velocity,
                                                       paddle_size, paddle_distance, 10);
    SECTION("slide up") {
        paddle.SlideLeftPaddle(2);
        REQUIRE(paddle.GetPosition() == paddle_corner);
    }
    SECTION("slide down") {
        paddle.SlideLeftPaddle(1);
        REQUIRE(paddle.GetPosition() == paddle_corner + paddle_velocity);
    }
    SECTION("slide up again") {
        paddle.SlideLeftPaddle(2);
        REQUIRE(paddle.GetPosition() == paddle_corner);
    }
}

TEST_CASE("test collision with paddle") {
    vec2 loc2(2, 2);
    vec2 vel2(-2, 0);
    glm::vec2 paddle_corner = glm::vec2 (10,10);
    glm::vec2 paddle_velocity = glm::vec2 (0,10);
    glm::vec2 paddle_size = glm::vec2 (1,2);
    glm::vec2 paddle_distance = glm::vec2 (20,20);
    finalproject::Paddle paddle = finalproject::Paddle(paddle_corner, paddle_velocity,
                                                       paddle_size, paddle_distance, 10);
    finalproject::CollisionLogic logic(glm::vec2(2,2),glm::vec2 (50,50), paddle);
    logic.AddNewBall(loc2, vel2);
    REQUIRE(paddle.CheckCollisionWithPaddle(logic.GetAllBalls().at(0)) == true);
}