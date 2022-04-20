#include <catch2/catch.hpp>

#include <collision_logic.h>
using glm::vec2;

TEST_CASE("test initialization and get-set") {
    vec2 loc(1, 1);
    vec2 vel(1, 1);
    finalproject::Pong_Ball ball(loc, vel);
    SECTION("basic") {
        REQUIRE (ball.GetVelocity() == vel);
        REQUIRE (ball.GetPosition() == loc);
    }
    SECTION("test set velocity") {
        vec2 vel2(2, 1);
        ball.SetVelocity(vel2);
        REQUIRE (ball.GetVelocity() == vel2);
        REQUIRE (ball.GetPosition() == loc);
    }
    SECTION("test set postion") {
        vec2 loc2(2, 1);
        ball.SetPosition(loc2);
        REQUIRE (ball.GetVelocity() == vel);
        REQUIRE (ball.GetPosition() == loc2);
    }
}

TEST_CASE("test update after collision function") {
    vec2 loc(1, 1);
    vec2 vel(1, 1);
    finalproject::Pong_Ball ball(loc, vel);
    SECTION("test for update after collision with ball") {
        vec2 loc1(4, 4);
        vec2 vel1(4, 4);
        finalproject::Pong_Ball ball2(loc1, vel1);
        ball.UpdateAfterCollision(ball2, 0);
        REQUIRE((int) ball.GetVelocity().x == 4); //hand-calculated values
    }
    SECTION("test for update after collision with x wall") {
        ball.UpdateAfterCollision(ball, 1);
        vec2 vel_neg(-1, 1);
        REQUIRE(vel_neg == ball.GetVelocity());
    }
    SECTION("test for update after collision with y wall") {
        ball.UpdateAfterCollision(ball, 2);
        vec2 vel_neg(1, -1);
        REQUIRE(vel_neg == ball.GetVelocity());
    }
}