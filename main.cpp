#include <FEHLCD.h>
#include <FEHIO.h>
#include <FEHUtility.h>
#include <FEHMotor.h>
#include <FEHRPS.h>
#include <FEHServo.h>

//Declarations for encoders & motors
ButtonBoard buttons(FEHIO::Bank3);
DigitalEncoder right_encoder(FEHIO::P2_2);
DigitalEncoder left_encoder(FEHIO::P2_3);
AnalogInputPin sensor(FEHIO::P2_5);
FEHMotor right_motor(FEHMotor::Motor0);
FEHMotor left_motor(FEHMotor::Motor3);
FEHServo crank(FEHServo::Servo0);
FEHServo pulley(FEHServo::Servo7);



void accel_forward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    int i;
    //Set both motors to desired percent
    for( i=5;i<=percent;i+=5){
    Sleep(25);
    right_motor.SetPercent(0.9*i);
    left_motor.SetPercent(-1.1*i);
    }
    //While the average of the left and right encoder are less than counts,
    //keep running motors

    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    for( i=percent;i>=0;i-=5){
    Sleep(25);
    right_motor.SetPercent(i);
    left_motor.SetPercent(i);
    }

}
void move_forward(int percent, int counts, double time) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
    int i=percent;
    double startTime= TimeNow();
    //Set both motors to desired percent

    right_motor.SetPercent(i/1.0394);
    left_motor.SetPercent(-1.0394*i);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    if(time==0){
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);
    }
    else{
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts && TimeNow()-startTime< time);
    }
    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void move_upramp(int percent) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    float countsPerInch= 33.74084;
    //Set both motors to desired percent
    for(int i=10;i<=percent;i+=10){
    Sleep(30);
    right_motor.SetPercent(i/1.04);
    left_motor.SetPercent(-1.04*i);
    }
    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < (18)*countsPerInch );


    //Turn off motors
    for(int i=percent;i>=0;i-=2){
    Sleep(40);
    right_motor.SetPercent(i);
    left_motor.SetPercent(-1*i);
    }
}




void move_backward(int percent, int counts, double time) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();
double startTime= TimeNow();
    //Set both motors to desired percent
    right_motor.SetPercent(-1*(percent/1.0294));
    left_motor.SetPercent(1.0294*percent);
    //While the average of the left and right encoder are less than counts,
    //keep running motors
    if(time==0){
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);
    }
    else{
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts && TimeNow()-startTime< time);
    }

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
    right_motor.SetPercent(-1*(percent*1));
    left_motor.SetPercent(-1*(percent*1));


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
    right_motor.SetPercent(percent*1);
    left_motor.SetPercent(percent*1);


    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts()+right_encoder.Counts())/2. < counts);


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
void check_backward(int percent, int counts) //using encoders
{
    //Reset encoder counts
    right_encoder.ResetCounts();
    left_encoder.ResetCounts();

    //Set both motors to desired percent
    right_motor.SetPercent(-1*percent);
    left_motor.SetPercent(percent);

    //While the average of the left and right encoder are less than counts,
    //keep running motors
    while((left_encoder.Counts() + right_encoder.Counts()) / 2. < counts);

    //Turn off motors
    right_motor.Stop();
    left_motor.Stop();
}

void check_x_plus(float x_coordinate) //using RPS while robot is in the +x direction
{
    //check whether the robot is within an acceptable range
    while(RPS.X() < x_coordinate - 1 || RPS.X() > x_coordinate + 1)
    {
         Sleep(50);
        LCD.WriteLine(RPS.X());
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            check_backward(50,1);
        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            check_forward(50,1);
        }
    }
}

void check_x_minus(float x_coordinate) //using RPS while robot is in the +x direction
{
    //check whether the robot is within an acceptable range
    while(RPS.X() < x_coordinate - 1  || RPS.X() > x_coordinate + 1)
    {
         Sleep(50);
        LCD.WriteLine(RPS.X());
        if(RPS.X() > x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            check_forward(50,1);
        }
        else if(RPS.X() < x_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            check_backward(50,1);
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
            check_backward(50,1);
            //<ADD CODE HERE>
        }
    }
}

void check_y_plus(float y_coordinate) //using RPS while robot is in the +y direction
{
    //check whether the robot is within an acceptable range
    while(RPS.Y() < y_coordinate - 1 || RPS.Y() > y_coordinate + 1)
    {
         Sleep(50);
        LCD.WriteLine(RPS.Y());
        if(RPS.Y() > y_coordinate)
        {
            //pulse the motors for a short duration in the correct direction
            check_backward(50,1);
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

void check_diagonal(float x_coordinate, float y_coordinate ) //using RPS while robot is in the +y direction
{
    float tangent = y_coordinate/x_coordinate;
    //check whether the robot is within an acceptable range
    while((RPS.Y()/RPS.X()) < tangent - 1 || (RPS.Y()/RPS.X()) > tangent + 1)
    {
         Sleep(50);
        LCD.WriteLine(RPS.Y());
        if((RPS.Y()/RPS.X()) > tangent)
        {
            //pulse the motors for a short duration in the correct direction
            check_backward(50,1);
            //<ADD CODE HERE>
        }
        else if((RPS.Y()/RPS.X()) < tangent)
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
           check_left(100, 1);
           Sleep(50);
        }
        else{
            check_right(100, 1);
            Sleep(50);
        }
        }
    }




    else{
    while(RPS.Heading()< heading - 1 || RPS.Heading() > heading + 1)
    {

        LCD.WriteLine(RPS.Heading());



        if (RPS.Heading() < heading)
        {
            check_left(100, 1);
            Sleep(50);
        }
        if (RPS.Heading() > heading)
        {
            check_right(100, 1);
            Sleep(50);
        }
        }
    }
 }

void rotate_crank(){

    move_backward(30,350,5);
    check_y_minus(54.3);
    Sleep(250);
    float color = sensor.Value();
    Sleep(250);
    LCD.WriteLine(color);
    if(color<.669)
    {
        LCD.WriteLine("Light is Red");
        crank.SetDegree(0);
        Sleep(700);
        move_backward(40,60,5);
        Sleep(500);
        move_forward(30,5,0);
        Sleep(500);
        crank.SetDegree(180);
        Sleep(1000);

        move_forward(30,45,0);
        crank.SetDegree(0);
        Sleep(700);
        move_backward(40,60,3);
        Sleep(500);
        move_forward(30,5,0);
        Sleep(500);
        crank.SetDegree(180);        
        Sleep(1000);

        move_forward(30,45,0);
        crank.SetDegree(0);
        Sleep(700);
        move_backward(40,60,3);
        Sleep(500);
        move_forward(30,5,0);
        Sleep(500);
        crank.SetDegree(160);
        Sleep(1000);
    }
    else
    {
        LCD.WriteLine("Light is Blue");
        crank.SetDegree(180);
        Sleep(700);
        move_backward(40,60,5);
        Sleep(500);
        move_forward(30,5,0);
        Sleep(500);
        crank.SetDegree(0);
        Sleep(1000);

        move_forward(30,45,0);
        crank.SetDegree(180);
        Sleep(700);
        move_backward(30,60,3);
        Sleep(500);
        move_forward(30,5,0);
        Sleep(500);
        crank.SetDegree(0);
        Sleep(1000);

        move_forward(30,45,0);
        crank.SetDegree(180);
        Sleep(700);
        move_backward(40,60,3);
        Sleep(500);
        move_forward(30,5,0);
        Sleep(500);
        crank.SetDegree(20);
        Sleep(1000);
    }


}

void push_buttons()
{
    int redorder=RPS.RedButtonOrder(), blueorder=RPS.BlueButtonOrder(), whiteorder=RPS.WhiteButtonOrder();
    int redDegree=175, whiteDegree=125,blueDegree=80;

           if(redorder==1)
           {
              pulley.SetDegree(redDegree);//move lift to red button
              Sleep(500);
              right_motor.SetPercent(30);
              left_motor.SetPercent(-30);
              while(RPS.RedButtonPressed()==0);
              right_motor.Stop();
              left_motor.Stop();
              move_backward(30,75,0);
              Sleep(500);
              if(whiteorder==2)
              {
                  pulley.SetDegree(whiteDegree);//move lift to red button
                  Sleep(500);
                  right_motor.SetPercent(30);
                  left_motor.SetPercent(-30);
                  while(RPS.WhiteButtonPressed()==0);
                  right_motor.Stop();
                  left_motor.Stop();
                  move_backward(50,50,0);
                  Sleep(500);

                  pulley.SetDegree(blueDegree);//move lift to red button
                  Sleep(500);
                  right_motor.SetPercent(30);
                  left_motor.SetPercent(-30);
                  while(RPS.BlueButtonPressed()==0);
                  right_motor.Stop();
                  left_motor.Stop();
                  move_backward(30,75,0);
                  Sleep(500);


              }
              else if(blueorder==2)
              {
                  pulley.SetDegree(blueDegree);//move lift to red button
                  Sleep(500);
                  right_motor.SetPercent(30);
                  left_motor.SetPercent(-30);
                  while(RPS.BlueButtonPressed()==0);
                  right_motor.Stop();
                  left_motor.Stop();
                  move_backward(30,75,0);
                  Sleep(500);

                  pulley.SetDegree(whiteDegree);//move lift to red button
                  Sleep(500);
                  right_motor.SetPercent(30);
                  left_motor.SetPercent(-30);
                  while(RPS.WhiteButtonPressed()==0);
                  right_motor.Stop();
                  left_motor.Stop();
                  move_backward(30,75,0);
                  Sleep(500);

            }
           }
                 else if(whiteorder==1)
                 {
                    pulley.SetDegree(whiteDegree);//move lift to red button
                    Sleep(500);
                    right_motor.SetPercent(30);
                    left_motor.SetPercent(-30);
                    while(RPS.WhiteButtonPressed()==0);
                    right_motor.Stop();
                    left_motor.Stop();
                    move_backward(30,75,0);
                    Sleep(500);
                    if(redorder==2)
                    {
                        pulley.SetDegree(redDegree);//move lift to red button
                        Sleep(500);
                        right_motor.SetPercent(30);
                        left_motor.SetPercent(-30);
                        while(RPS.RedButtonPressed()==0);
                        right_motor.Stop();
                        left_motor.Stop();
                        move_backward(30,75,0);
                        Sleep(500);

                        pulley.SetDegree(blueDegree);//move lift to red button
                        Sleep(500);
                        right_motor.SetPercent(30);
                        left_motor.SetPercent(-30);
                        while(RPS.BlueButtonPressed()==0);
                        right_motor.Stop();
                        left_motor.Stop();
                        move_backward(30,75,0);
                        Sleep(500);


                    }
                    else if(blueorder==2)
                    {
                        pulley.SetDegree(blueDegree);//move lift to red button
                        Sleep(500);
                        right_motor.SetPercent(30);
                        left_motor.SetPercent(-30);
                        while(RPS.BlueButtonPressed()==0);
                        right_motor.Stop();
                        left_motor.Stop();
                        move_backward(30,75,0);
                        Sleep(500);

                        pulley.SetDegree(redDegree);//move lift to red button
                        Sleep(500);
                        right_motor.SetPercent(30);
                        left_motor.SetPercent(-30);
                        while(RPS.RedButtonPressed()==0);
                        right_motor.Stop();
                        left_motor.Stop();
                        move_backward(30,75,0);
                        Sleep(500);

                    }
           }

                 else if(blueorder==1)
                 {
                    pulley.SetDegree(blueDegree);//move lift to red button
                    Sleep(500);
                    right_motor.SetPercent(30);
                    left_motor.SetPercent(-30);
                    while(RPS.BlueButtonPressed()==0);
                    right_motor.Stop();
                    left_motor.Stop();
                    move_backward(30,75,0);
                    Sleep(500);
                    if(redorder==2)
                    {
                        pulley.SetDegree(redDegree);//move lift to red button
                        Sleep(500);
                        right_motor.SetPercent(30);
                        left_motor.SetPercent(-30);
                        while(RPS.RedButtonPressed()==0);
                        right_motor.Stop();
                        left_motor.Stop();
                        move_backward(30,75,0);
                        Sleep(500);

                        pulley.SetDegree(whiteDegree);//move lift to red button
                        Sleep(500);
                        right_motor.SetPercent(30);
                        left_motor.SetPercent(-30);
                        while(RPS.WhiteButtonPressed()==0);
                        right_motor.Stop();
                        left_motor.Stop();
                        move_backward(30,75,0);
                        Sleep(500);


                    }
                    else if(whiteorder==2)
                    {
                        pulley.SetDegree(whiteDegree);//move lift to red button
                        Sleep(500);
                        right_motor.SetPercent(30);
                        left_motor.SetPercent(-30);
                        while(RPS.WhiteButtonPressed()==0);
                        right_motor.Stop();
                        left_motor.Stop();
                        move_backward(30,75,0);
                        Sleep(500);

                        pulley.SetDegree(redDegree);//move lift to red button
                        Sleep(500);
                        right_motor.SetPercent(30);
                        left_motor.SetPercent(-30);
                        while(RPS.RedButtonPressed()==0);
                        right_motor.Stop();
                        left_motor.Stop();
                        move_backward(30,75,0);
                        Sleep(500);

                    }



}
}

int main(void)
{

    //Initialize the screen (GO BUCKS!)
    LCD.Clear( FEHLCD::Black );
    LCD.SetFontColor( FEHLCD::Green );
    RPS.InitializeMenu();
    crank.SetMin(687);
    crank.SetMax(2311);
    crank.SetDegree(90);
    pulley.SetMin(775);
    pulley.SetMax(1776);
    pulley.SetDegree(10);
    int countsPerInch=33.7;

    while(!buttons.MiddlePressed());
    while(buttons.MiddlePressed());

    double startTime= TimeNow();
    LCD.WriteLine("Waiting for light");
    while(sensor.Value() > 0.5 && TimeNow()-startTime< 30);

    Sleep(100);
    move_forward(50, 725,0);
    check_heading(180);
    Sleep(250);
    check_y_minus(4);
Sleep(250);


    turn_left(50,100);
Sleep(250);
    check_heading(252);
Sleep(250);

    move_forward(75,(17)*countsPerInch,5);
    Sleep(750);
    move_backward(30, (2)*countsPerInch,0);
    move_forward(75,(4)*countsPerInch,5);
    pulley.SetDegree(180);


    move_backward(30, (8)*countsPerInch,0);
    Sleep(100);
    pulley.SetDegree(80);

    turn_left(25, 100);

    check_heading(300);


    move_forward(40,(14)*countsPerInch,5);

    //CHECK_MAYBE?
turn_right(20,10);
move_backward(20,15,0);

    turn_left(40, 50);
    Sleep(250);
    check_heading(0);



    move_upramp(70);
    check_heading(0);

    if(RPS.Y()<49){
        move_forward(50,175,0);
    }

    check_y_plus(55.5);

    turn_left(50,350);
    check_heading(140);


    move_backward(30,150,0);
    check_x_minus(29.8);


    turn_left(20,100);
    check_heading(180);
    crank.SetDegree(0);
    move_forward(50, 150,0);

    check_heading(180);
    rotate_crank();

    move_forward(50,200,0);
    pulley.SetDegree(90);
    check_y_minus(47);
crank.SetDegree(90);

    turn_right(50,150);

    check_heading(90);


    move_forward(20,(25)*countsPerInch,7);


    move_backward(50,125,0);

    check_x_minus(7);


    turn_right(50,75);

    check_heading(50);
    pulley.SetDegree(40);
    Sleep(250);
    move_forward(100,(6)*countsPerInch,5);
    Sleep(250);
    move_backward(50,(7)*countsPerInch,0);
    pulley.SetDegree(180);


    turn_right(50,180);

    check_heading(320);


    move_forward(30,(8.5)*countsPerInch,0);
    check_x_plus(22.5);
    turn_left(50,150);


    check_heading(45);


    push_buttons();

move_backward(30,(4)*countsPerInch,5);
pulley.SetDegree(180);

check_x_minus(14.4);

turn_left(50,100);

check_heading(132);


move_forward(50,(12)*countsPerInch,5);

check_x_minus(3.3);


turn_left(50,30);

check_heading(180);


move_forward(50,(35)*countsPerInch,0);

check_y_minus(21);



}
