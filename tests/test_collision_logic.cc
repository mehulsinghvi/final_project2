#include <catch2/catch.hpp>

#include <collision_logic.h>
#include <paddle.h>
using glm::vec2;

TEST_CASE("test inititialization and getters") {
    vec2 loc(1, 1);
    vec2 vel(1, 1);
    finalproject::Pong_Ball ball(loc, vel);
    glm::vec2 paddle_corner = glm::vec2 (10,10);
    glm::vec2 paddle_velocity = glm::vec2 (0,10);
    glm::vec2 paddle_size = glm::vec2 (1,2);
    glm::vec2 paddle_distance = glm::vec2 (20,20);
    finalproject::Paddle paddle = finalproject::Paddle(paddle_corner, paddle_velocity, paddle_size, paddle_distance, 10);
    finalproject::CollisionLogic logic(glm::vec2(2,2),glm::vec2 (50,50), paddle);
    SECTION("test AddNewBall and GetAllBalls") {
        logic.AddNewBall(loc, vel);
        REQUIRE(logic.GetAllBalls().size() == 1);
    }
    SECTION("test GetAllBalls") {
        logic.AddNewBall(loc, vel);
        REQUIRE(logic.GetAllBalls().at(0).GetVelocity() == vel);
        REQUIRE(logic.GetAllBalls().at(0).GetPosition() == loc);
    }
    SECTION("test AddNewBalls with multiple adds") {
        logic.AddNewBall(loc, vel);
        vec2 loc1(2, 2);
        vec2 vel1(2, 1);
        logic.AddNewBall(loc1, vel1);
        REQUIRE(logic.GetAllBalls().size() == 2);
        REQUIRE(logic.GetAllBalls().at(0).GetVelocity() == vel);
        REQUIRE(logic.GetAllBalls().at(0).GetPosition() == loc);
        REQUIRE(logic.GetAllBalls().at(1).GetVelocity() == vel1);
        REQUIRE(logic.GetAllBalls().at(1).GetPosition() == loc1);
    }
}

TEST_CASE("test UpdateState") {
    vec2 loc(3, 3);
    vec2 vel(1, 1);
    vec2 loc1(6, 6);
    vec2 vel1(1, 1);
    glm::vec2 paddle_corner = glm::vec2 (10,10);
    glm::vec2 paddle_velocity = glm::vec2 (0,10);
    glm::vec2 paddle_size = glm::vec2 (1,2);
    glm::vec2 paddle_distance = glm::vec2 (20,20);
    finalproject::Paddle paddle = finalproject::Paddle(paddle_corner,paddle_velocity,
                                                       paddle_size, paddle_distance, 10);
    finalproject::CollisionLogic logic(glm::vec2(2,2),glm::vec2 (50,50), paddle);
    SECTION("test updated state with no collisions") {
        logic.AddNewBall(loc, vel);
        logic.UpdateState();
        REQUIRE(logic.GetAllBalls().at(0).GetPosition() == loc + vel);
    }
    SECTION("test updated state with multiple balls and no collisions") {
        logic.AddNewBall(loc, vel);
        logic.AddNewBall(loc1, vel1);
        logic.UpdateState();
        REQUIRE(logic.GetAllBalls().at(0).GetPosition() == loc + vel);
        REQUIRE(logic.GetAllBalls().at(1).GetPosition() == loc1 + vel1);
    }
    SECTION("test updated state with multiple balls and wall collisions") {
        vec2 loc2(4, 3);
        vec2 vel2(-2, -2);
        vec2 vel3(2, -2);
        logic.AddNewBall(loc2, vel2);
        logic.AddNewBall(loc1, vel1);
        logic.UpdateState();
        REQUIRE(logic.GetAllBalls().at(0).GetVelocity() == vel3);
        REQUIRE(logic.GetAllBalls().at(1).GetPosition() == loc1 + vel1);
    }
    SECTION("test updated state with multiple balls and ball collision") {
        vec2 loc2(2, 2);
        vec2 vel2(3, 3);
        vec2 vel3(-1, 1);
        logic.AddNewBall(loc2, vel2);
        logic.AddNewBall(loc1, vel1);
        logic.AddNewBall(loc, vel);
        logic.UpdateState();
        REQUIRE(logic.GetAllBalls().at(0).GetVelocity() == (vel3)); // problems with float and int
        REQUIRE(logic.GetAllBalls().at(1).GetPosition() == loc1 + vel1);
    }
    SECTION("test updated state with ball and paddle collision - 2") {
        vec2 loc2(2, 2);
        vec2 vel2(-2, 0);
        vec2 vel3(2, 0);
        logic.AddNewBall(loc2, vel2);
        logic.AddNewBall(loc1, vel1);
        logic.UpdateState();
        REQUIRE(logic.GetAllBalls().at(0).GetVelocity() == vel3);
        REQUIRE(logic.GetAllBalls().at(1).GetPosition() == loc1 + vel1);
    }
}