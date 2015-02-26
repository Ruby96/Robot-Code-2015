#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>

//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder right_encoder(FEHIO::P0_6);
DigitalEncoder left_encoder(FEHIO::P0_7);
AnalogInputPin sensor(FEHIO::P1_0);
FEHMotor right_motor(FEHMotor::Motor0);
FEHMotor left_motor(FEHMotor::Motor1);


void move_forward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    int i;
    //Set both motors to desired percent
    for( i=10;i<=percent;i+=10){
    Sleep(50);
    right_motor.SetPercent(i);
    left_motor.SetPercent(-1*i);
    }
    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void check_forward(int percent, int counts) //using encoders
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
    right_motor.SetPercent(-1*(percent));
    left_motor.SetPercent(-1*(percent));


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


void check_right(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    //hint: set right motor backwards, left motor forwards
    right_motor.SetPercent(-1*(percent*1.2));
    left_motor.SetPercent(-1*(percent*.8));


    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts()+right_encoder.Counts())/2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void check_left(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(percent*.8);
    left_motor.SetPercent(percent*1.2);


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
         Sleep(100);
        LCD.WriteLine(RPS.X());
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            check_forward(-50,1);
        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            check_forward(50,1);
        }
    }
}

void check_y_minus(float y_coordinate) //using RPS while robot is in the -y direction
{
    //check whether the robot is within an acceptable range
    while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)

    {
        Sleep(100);

        LCD.WriteLine(RPS.Y());
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            check_forward(50,1);
            //<ADD CODE HERE>
        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            check_forward(-50,1);
            //<ADD CODE HERE>
        }
    }
}

void check_y_plus(float y_coordinate) //using RPS while robot is in the +y direction
{
    //check whether the robot is within an acceptable range
    while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
    {
         Sleep(100);
        LCD.WriteLine(RPS.Y());
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            check_forward(-50,1);
            //<ADD CODE HERE>
        }
        else if(RPS.Y() < y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            check_forward(50,1);
            //<ADD CODE HERE>
        }
    }
}

void check_heading(float heading) //using RPS
{
    //you will need to fill out this one yourself and take into account
    //the edge conditions (when you want the robot to go to 0 degrees
    //or close to 0 degrees)


    if (heading == 0){

        while(!(RPS.Heading()>=359) && !(RPS.Heading()<=1))
        {
            LCD.WriteLine(RPS.Heading());
        if(RPS.Heading()>180){
           check_left(50, 1);
           Sleep(100);
        }
        else{
            check_right(50, 1);
            Sleep(100);
        }
        }
    }




    else{
    while(RPS.Heading()< heading - 1 || RPS.Heading() > heading + 1)
    {

        LCD.WriteLine(RPS.Heading());



        if (RPS.Heading() < heading)
        {
            check_left(50, 1);
            Sleep(100);
        }
        if (RPS.Heading() > heading)
        {
            check_right(50, 1);
            Sleep(100);
        }
        }
    }
 }


int main(void)
{
    LCD.Write("print");
    int motor_percent = 50;
    float countsPerInch= 33.74084;
    float offset= 2.7126;
    float initial_heading = RPS.Heading();

    //Initialize the screen (GO BUCKS!)
    LCD.Clear( FEHLCD::Scarlet );
    LCD.SetFontColor( FEHLCD::Gray );
    RPS.InitializeMenu();

    //LCD.WriteLine("Waiting for button to be pressed");
    //while(!buttons.MiddlePressed());
    //while(buttons.MiddlePressed());

    LCD.WriteLine("Waiting for light");
    while(sensor.Value() > 0.5);

    Sleep(100);
    move_forward(motor_percent, (12.5-offset)*countsPerInch);
    Sleep(250);
    check_y_minus(17);
    Sleep(250);


    turn_left(50,200);
    Sleep(250);
    check_heading(270);
    Sleep(250);

    move_forward(motor_percent,(12-offset)*countsPerInch);
    Sleep(250);
    check_x_plus(32.5);
    Sleep(250);


    turn_left(50, 200);
    Sleep(250);
    check_heading(0);
    Sleep(250);

    move_forward(75,(24-offset)*countsPerInch);
    Sleep(250);
    check_y_plus(48.8);
    Sleep(250);
    check_heading(0);

    move_forward(motor_percent,(11-offset)*countsPerInch );
    Sleep(250);
    check_y_plus(61);
    Sleep(250);




}
