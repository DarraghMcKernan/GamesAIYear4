#include "NPC.h"
#include "random"

NPC::NPC(sf::Vector2f SpawnPosition, float speed, BehaviourEnum startBehaviour)
	: currentBehaviour(startBehaviour) ,speed(speed), position(SpawnPosition)
{
	init();
}

void NPC::init()
{
	NPCShape.setPointCount(3);
	NPCShape.setScale(3, 5);
	NPCShape.setFillColor(sf::Color::Red);
	NPCShape.setRadius(5);
	NPCShape.setPosition(position);
	NPCShape.setOrigin(5, 5);

	VisionCone.setPointCount(3);
	VisionCone.setScale(3.3, -5);
	VisionCone.setFillColor(sf::Color(255, 0, 0, 50));
	VisionCone.setRadius(40);
	VisionCone.setPosition(position);
	VisionCone.setOrigin(40, 0);

	if (!font.loadFromFile("Assets/Fonts/BebasNeue.otf"))
	{
		std::cout << "Error loading font\n";
	}
	NPCNametag.setFont(font);
	NPCNametag.setCharacterSize(20);

	if (!NPCTexture.loadFromFile("Assets/Images/MIG-29.png"))
	{
		std::cout << "error loading NPC sprite\n";
	}
	NPCSprite.setTexture(NPCTexture);
	NPCSprite.setPosition(position);
	NPCSprite.setScale(.03, .03);
	NPCSprite.setOrigin((NPCSprite.getTextureRect().getSize().x / 2) + 100, NPCSprite.getTextureRect().getSize().y / 2);

	if (currentBehaviour == BehaviourEnum::Seek)
	{
		NPCNametag.setString("Seek");
	}
	if (currentBehaviour == BehaviourEnum::Pursue)
	{
		NPCNametag.setString("Pursue");
	}
	if (currentBehaviour == BehaviourEnum::Arrive)
	{
		NPCNametag.setString("Arrive");
	}
	if (currentBehaviour == BehaviourEnum::ArriveSlow)
	{
		NPCNametag.setString("ArriveSlow");
	}
	if (currentBehaviour == BehaviourEnum::Wander)
	{
		NPCNametag.setString("Wander");
	}
}

float NPC::rotateToVelocity()
{
	if (velocity.x == 0 && velocity.y == 0)
	{
		return NPCShape.getRotation();
	}

	float radians = atan2(velocity.y, velocity.x);

	float angleInDegrees = radians * 180.0f / 3.14159f;

	return angleInDegrees;
}

void NPC::update(sf::Vector2f t_playerPos)
{
	playerPosition = t_playerPos;
	newPosition = position;

	if (currentBehaviour == BehaviourEnum::Seek || currentBehaviour == BehaviourEnum::Pursue)
	{
		newPosition = NPCBehaviour.vectorToTarget(position, playerPosition);
	}
	else if (currentBehaviour == BehaviourEnum::Wander)
	{
		newPosition = NPCBehaviour.wander(position);
	}
	else if (currentBehaviour == BehaviourEnum::Arrive)
	{
		newPosition = NPCBehaviour.arrive(position, playerPosition);
	}
	else if (currentBehaviour == BehaviourEnum::ArriveSlow)
	{
		newPosition = NPCBehaviour.arriveSlow(position, playerPosition);
	}
	
	velocity += newPosition * acceleration;

	float distance = sqrt(velocity.x * velocity.x + velocity.y * velocity.y);

	if (distance > 3.0f)//cap max velocity
	{
		velocity /= distance;
		velocity *= 3.0f;
	}

	velocity *= friction;

	position += velocity;

	keepNPCOnScreen();

	if (currentBehaviour == BehaviourEnum::Wander)
	{
		sf::Vector2f wanderRotate = sf::Vector2f{ position.x + (velocity.x * 10),position.y + (velocity.y * 10) };// look at a position that is ahead of where we are moving 
		NPCShape.setRotation(rotateToTarget(wanderRotate));
		VisionCone.setRotation(rotateToTarget(wanderRotate));
		NPCSprite.setRotation(rotateToTarget(wanderRotate) + 90);
	}
	else
	{
		float rotationAngle = rotateToVelocity();
		NPCShape.setRotation(rotationAngle + 90);
		VisionCone.setRotation(rotationAngle + 90);
		NPCSprite.setRotation(rotationAngle + 180);
	}

	if (currentBehaviour == BehaviourEnum::Pursue)
	{
		visionConeView(pursuitRealPlayerPos);
	}
	else visionConeView(playerPosition);

	NPCShape.setPosition(position);
	NPCSprite.setPosition(position);
	VisionCone.setPosition(position);
	NPCNametag.setPosition(position);
}

void NPC::render(sf::RenderWindow& t_window)
{
	//t_window.draw(VisionCone);
	t_window.draw(NPCSprite);
	//t_window.draw(NPCShape);
	//t_window.draw(NPCNametag);
}

void NPC::keepNPCOnScreen()
{
	if (position.x > SCREEN_SIZE.x + 10)
	{
		position.x = -10;
	}
	if (position.x < -10)
	{
		position.x = SCREEN_SIZE.x + 10;
	}

	if (position.y > SCREEN_SIZE.y + 10)
	{
		position.y = -10;
	}
	if (position.y < -10)
	{
		position.y = SCREEN_SIZE.y + 10;
	}
}

float NPC::rotateToTarget(sf::Vector2f t_target)
{
	sf::Vector2f angleToTarget = t_target - position;

	float radians = atan2(angleToTarget.y, angleToTarget.x);

	return (radians * 180 / 3.14f) + 90;
}

void NPC::visionConeView(sf::Vector2f t_target)
{
	int angleForward = normalizeAngle(NPCShape.getRotation());

	int angleToTarget = normalizeAngle(rotateToTarget(t_target));

	int left = normalizeAngle(angleForward - 30);
	int right = normalizeAngle(angleForward + 30);

	bool angleInRange = false;
	if (left < right && angleToTarget > left && angleToTarget < right)//if the angle is between 0 and 360
	{
		angleInRange = true;
	}
	else if (left > right && (angleToTarget > left || angleToTarget < right))//if the angle is lying between 330 and 30 just check if its between one of the angles as it must then be between both
	{
		angleInRange = true;
	}

	if (angleInRange == true)
	{
		sf::Vector2f vectorToPoint = t_target - position;
		float distance = sqrt((vectorToPoint.x * vectorToPoint.x) + (vectorToPoint.y * vectorToPoint.y));
		if (distance < 320)
		{
			VisionCone.setFillColor(sf::Color(0, 255, 0, 50));
		}
		else VisionCone.setFillColor(sf::Color(255, 0, 0, 50));
	}
	else VisionCone.setFillColor(sf::Color(255, 0, 0, 50));
}

void NPC::setRealPlayerPos(sf::Vector2f t_realPos)
{
	pursuitRealPlayerPos = t_realPos;//to ensure the pursuit enemy looks for player in vision cone not the predicted player
}

sf::Vector2f NPC::getPos()
{
	return position;
}

int NPC::normalizeAngle(int t_angle)
{
	t_angle = t_angle % 360;//make sure its in the range of 360

	if (t_angle < 0)//if negative make positive
	{
		t_angle += 360;
	}

	return t_angle;
}
