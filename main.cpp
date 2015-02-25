#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>

//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder right_encoder(FEHIO::P0_0);
DigitalEncoder left_encoder(FEHIO::P0_1);
FEHMotor right_motor(FEHMotor::Motor0);
FEHMotor left_motor(FEHMotor::Motor1);
AnalogInputPin cds(FEHIO::P0_2);

void move_forward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(-1*percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_right(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    //hint: set right motor backwards, left motor forwards
    right_motor.SetPercent(-1*percent);
    left_motor.SetPercent(-1*percent);


    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts()+right_encoder.Counts())/2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void turn_left(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent);
    left_motor.SetPercent(percent);


    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts()+right_encoder.Counts())/2. < counts);


    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void check_x_plus(float x_coordinate) //using RPS while robot is in the +x direction
{
    //check whether the robot is within an acceptable range
    while(RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1)
    {
        LCD.WriteLine(RPS.X());
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move_forward(-50,1);
        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move_forward(50,1);
        }
        Sleep(250);
    }
}

void check_y_minus(float y_coordinate) //using RPS while robot is in the -y direction
{
    //check whether the robot is within an acceptable range
    while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
    {
        LCD.WriteLine(RPS.Y());
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move_forward(50,1);
        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move_forward(-50,1);
        }
        Sleep(250);
    }
}

void check_y_plus(float y_coordinate) //using RPS while robot is in the +y direction
{
    //check whether the robot is within an acceptable range
    while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
    {
        LCD.WriteLine(RPS.Y());
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move_forward(-50,1);
        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            move_forward(50,1);
        }
        Sleep(250);
    }
}

void check_heading(float heading) //using RPS
{
    //you will need to fill out this one yourself and take into account
    //the edge conditions (when you want the robot to go to 0 degrees
    //or close to 0 degrees)
    if(heading >= 360)
    {
        heading = heading-360;
    }
    while(RPS.Heading()< heading - 1 || RPS.Heading() > heading + 1)
    {
        LCD.WriteLine(RPS.Heading());
        if (RPS.Heading() < heading)
        {
            turn_right(50, 1);
        }
        if (RPS.Heading() > 315 && heading == 0.)
        {
            turn_right(50,1);
        }
        if (RPS.Heading() > heading)
        {
            turn_left(50, 1);
        }
        Sleep(250);
    }
}

int main(void)
{
    int motor_percent = 75; //Input power level here
    int expected_counts = 34; //Input theoretical counts here
    float initial_heading = RPS.Heading();
    if(initial_heading > 350 || initial_heading < 10)
    {
        initial_heading = 0;
    }
    else if (initial_heading < 100 && initial_heading > 80)
    {
        initial_heading = 90;
    }
    else if (initial_heading < 190 && initial_heading > 170)
    {
        initial_heading = 180;
    }
    else if (initial_heading < 280 && initial_heading > 260)
    {
        initial_heading = 270;
    }
    //Initialize the screen (GO BUCKS!)
    LCD.Clear( FEHLCD::Scarlet );
    LCD.SetFontColor( FEHLCD::Gray );
    RPS.InitializeMenu();

    LCD.WriteLine("Performance Test 1");
    //while(cds.Value () > 0.15); //Wait for light to be seen

    //check_heading(initial_heading);
    move_forward(motor_percent, 472);
    check_y_minus(16.5);
    LCD.WriteLine(RPS.Y());
    turn_left(motor_percent, 10*expected_counts);
    check_heading(initial_heading+90);
    LCD.WriteLine(RPS.Heading());
    move_forward(motor_percent, 337);
    check_x_plus(28.099);
    LCD.WriteLine(RPS.X());
    turn_left(motor_percent, 110);
    check_heading(initial_heading+180);
    LCD.WriteLine(RPS.Heading());
    move_forward(motor_percent, 135);
    check_y_plus(20.599);
    LCD.WriteLine(RPS.Y());
    //move_forward(percent,      );
    //check_y_plus(    ,    );
    //move_forward(percent,      );
    left_motor.Stop();
    right_motor.Stop();
    return 0;
}
