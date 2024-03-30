#include <kipr/wombat.h>

#define LEFT_SENSOR 0
#define RIGHT_SENSOR 1

#define THRESHOLD 4000
#define SPEED 90

void followLine(int time){
    enable_servos();
    int x = 0;
    while (x < time){
        for (int t = 0; t < 10;t++)
        {
            int left_sensor_value = analog(LEFT_SENSOR);
            int right_sensor_value = analog(RIGHT_SENSOR);

            if (left_sensor_value > THRESHOLD && right_sensor_value > THRESHOLD)
            {
                motor(1, SPEED); // Move forward
                motor(3, SPEED);
            }
            else if (left_sensor_value > THRESHOLD)
            {
                motor(1, SPEED / 2); // Turn right
                motor(3, SPEED);
            }
            else if (right_sensor_value > THRESHOLD)
            {
                motor(1, SPEED); // Turn left
                motor(3, SPEED / 2);
            }
            else
            {
                motor(1, SPEED); // Default: Move forward
                motor(3, SPEED);
            }

            msleep(100); // nothing more nothing less
        }
        x+= 2;
    }

    disable_servos();
 	   
}
void straightLine(int time){
    cmpc(1);
    cmpc(3);
    
    while(gmpc(3) < time)
    {
        motor(3, 75);
        
        if(gmpc(1) < gmpc(3))
        {
            motor(1, 100);
        }
        else
        {
            motor(1,50);
        }
     }
}
void squareUp(){
    printf("squaring up\n");
    while (digital(3) == 0 || digital(0) == 0)
    {
    	if (digital(3) == 0 && digital(0) == 1)
        {
            motor(3, -90);
            motor(1,10);
        }
        else if (digital(3)==1 && digital(0) == 0)
        {
            motor(3, 10);
            motor(1, -90);
        }
        else
        {
            motor(3, -75); motor(1 , -75);
        }
    }
}


int main()
{	
    squareUp();
	straightLine(4000);
    
    motor(3, 75); 
    motor(1, -75);
    msleep(200);
    straightLine(3000);
    motor(3, -75);
    motor(1, 75);
    msleep(100);
    followLine(14);
    motor(3, 75);
    motor(1, -75);
    msleep(900);
    straightLine(1200);
    
    ao();
    
    return 0;
    
}