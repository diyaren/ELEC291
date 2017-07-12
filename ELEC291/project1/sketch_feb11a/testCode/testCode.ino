#include <AFMotor.h>



//AF_DCMotor m_driver(1, MOTOR12_64KHZ); // driver-side motor
//AF_DCMotor m_passenger(2, MOTOR12_64KHZ); // passenger-side motor

pinMode(1,OUTPUT);
pinMode(2,OUTPUT);

// which way we're facing
#define NORTH (0) /* "north" (straight ahead) */
#define EAST (1) /* "east" (right) */
#define SOUTH (2) /* "south" (backward) */
#define WEST (3) /* "west" (left) */
int facing = NORTH;

// tweak these values as needed


// these are pretty close to values that produce 90-degree turns
#define velocity (2) /* how fast the wheels spin */
#define turn_time (1000) /* how long it takes to turn 90-degrees */
#define move_time (2000) /* how long it takes to move forward 1 "space" */

void turn_90_clockwise()
{
  m_driver.run(BACKWARD);
  m_passenger.run(BACKWARD);
  delay(turn_time);
}

void turn_to(int direction)
{
  while(direction != facing)
  {
    turn_90_clockwise();
    facing = (facing + 1) % 4;
  }
}

void forward_one_unit()
{
  m_driver.run(BACKWARD);
  m_passenger.run(FORWARD);
  delay(move_time);
  full_stop();
}

void full_stop()
{
  m_driver.run(RELEASE);
  m_passenger.run(RELEASE);
}

void move_north()
{
  turn_to(NORTH);
  forward_one_unit();
}

void move_east()
{
  turn_to(EAST); 
  forward_one_unit();
}

void move_south()
{
  turn_to(SOUTH); 
  forward_one_unit();
}

void move_west()
{
  turn_to(WEST); 
  forward_one_unit();
}

void test_squaredance()
{
  // simple square movement pattern
  move_north();
  move_east();
  move_south();
  move_west();
}

void setup()
{
  m_driver.setSpeed(velocity);
  m_passenger.setSpeed(velocity);
  
  // for safety, wait 10 seconds before starting
  delay(1000);
  test_squaredance();
  delay(15000);
  full_stop();
}

void loop()
{

}
