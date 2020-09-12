#include "player.h"
#include <GL/gl.h>
#include <math.h>

Player::Player()
{
	x_trans = y_trans = z_trans = 0.0f;
	acceleration = 0.003f;
	velocity_limit = 0.1f;
	velocity = 0.0f;
	velocity_x = velocity_z = 0.0f;
	breaking_accel = 0.003f;
	constant_velocity = true;
	curr_x_dir = curr_z_dir = 0;
}

void Player::move()
{
	float y_angle;

	/* calcula a velocidade */
	if(constant_velocity)
	{
		velocity_x = velocity_limit;
	}
	else
	{
		/* está em movimento no eixo x */
		if(x_action.inAction())
		{
			if(velocity_x < velocity_limit)
			{
				if(velocity_x + acceleration > velocity_limit)
					velocity_x = velocity_limit;
				else
					velocity_x += acceleration;
			}
		}
		else if(velocity_x > 0)/* está parando */
		{
			if(velocity_x - breaking_accel > 0)
				velocity_x -= breaking_accel;
			else
			{
				velocity_x = 0.0f;
				curr_x_dir = 0;
			}
		}
	}
	/* calcula a posição e move o objeto */
	y_angle = -getYAngle() - 360.0f;
	if(y_angle < 0.0f)
		y_angle = -y_angle - 360.0f;
	if(curr_x_dir == 1)
	{
		x_trans += velocity_x * cos(2 * M_PI * y_angle / 360);
		z_trans += velocity_x * sin(2 * M_PI * y_angle / 360);
	}
	else if(curr_x_dir == -1)
	{
		x_trans -= velocity_x * cos(2 * M_PI * y_angle / 360);
		z_trans -= velocity_x * sin(2 * M_PI * y_angle / 360);
	}
	glTranslatef(-x_trans, 0, -z_trans);
}

